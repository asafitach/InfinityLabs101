#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <unistd.h>/* sleep */
#include "scheduler.h"
#include "pqueue.h"
#include "task.h"


/*****************************************************************************/

struct scheduler
{
    pq_t *tasks;
    task_t *current_task;
    int remove_curr_task;
    int to_stop;
};

/*****************************************************************************/

scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scheduler = malloc(sizeof(scheduler_t));
	if (NULL == scheduler)
	{
		return (NULL);
	}
	
	scheduler->tasks = PQCreate((pq_cmp_t)TaskIsBefore);
	if (NULL == scheduler->tasks)
	{
		free(scheduler);
		scheduler = NULL;	
		return (NULL);
	}
	
	scheduler->current_task = NULL;
	scheduler->remove_curr_task = 0;
	scheduler->to_stop = 0;
	
	return (scheduler);
}

/*****************************************************************************/

void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	SchedulerClear(scheduler);
	PQDestroy(scheduler->tasks);
	
	free(scheduler);
	scheduler = NULL;
}

/*****************************************************************************/

ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, operation_func_t operation_func, 
destroy_func_t destroy_func, size_t interval, void *param)
{
	task_t *task = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != operation_func);
	assert(NULL != destroy_func);
	
	task = TaskCreate(operation_func, destroy_func, interval, param);
	if (NULL == task)
	{
		return (GetBadUid());
	}

	if (1 == PQEnqueue(scheduler->tasks, task))
	{
		TaskDestroy(task);
		
		return (GetBadUid());
	}
	
	return (TaskGetUid(task));	
}

/*****************************************************************************/
int WrapTaskIsMatch(void *task1, void *task2)
{
	assert(NULL != task1);
	assert(NULL != task2);
	
	return (TaskIsMatch((const task_t *)task1, *((ilrd_uid_t *)task2)));
}

int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t task_id)
{
	task_t *task = NULL;
	
	assert(scheduler);
	
	task = (task_t *)PQErase(scheduler->tasks, WrapTaskIsMatch, (void *)&task_id);	
	if (NULL == task)
	{
		return (1);
	}
	
	TaskDestroy(task);
	
	return (0);
}

/*****************************************************************************/

void SchedulerClear(scheduler_t *scheduler)
{
	task_t *task = NULL;
	
	assert(NULL != scheduler);
	
	scheduler->remove_curr_task = 1;
	
	while (0 == PQIsEmpty(scheduler->tasks))
	{
		task = (task_t *)PQDequeue(scheduler->tasks);
		TaskDestroy(task);
	}
}

/*****************************************************************************/

size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (PQCount(scheduler->tasks) + (NULL != scheduler->current_task));
}

/*****************************************************************************/

int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (PQIsEmpty(scheduler->tasks) && !(scheduler->current_task));
}

/*****************************************************************************/
void TimeToRun(task_t *task)
{
	if(TaskGetTimeToRun(task) > time(NULL))
	{
		sleep(TaskGetTimeToRun(task) - time(NULL));
	}
}

sch_status_t SchedulerRun(scheduler_t *scheduler)
{
	task_status_t status = 0;
	int res = 0;
	
	assert(NULL != scheduler);
	
	scheduler->remove_curr_task = 0;
	scheduler->to_stop = 0;
	
	while (0 == PQIsEmpty(scheduler->tasks) && 0 == scheduler->to_stop)
	{
		scheduler->current_task = (task_t *)PQDequeue(scheduler->tasks);
		TimeToRun(scheduler->current_task);
		status = TaskRun(scheduler->current_task);
		
		if (scheduler->remove_curr_task == 1)
		{
			TaskDestroy(scheduler->current_task);
			scheduler->current_task = NULL;
			return (EMPTY);
		}
		
		else if (REPEAT == status && scheduler->to_stop == 0)
		{
			TaskUpdateTimeToRun(scheduler->current_task);
			res = PQEnqueue(scheduler->tasks, scheduler->current_task);
			if (1 == res)
			{
				TaskDestroy(scheduler->current_task);
				scheduler->to_stop = 1;			
			}
		}
		
		else
		{
			TaskDestroy(scheduler->current_task);
		}
	}	
	
	scheduler->current_task = NULL;
	return (scheduler->to_stop);	
}

/*****************************************************************************/

void SchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	scheduler->to_stop = 2;
}


/*****************************************************************************/

