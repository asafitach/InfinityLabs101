#include <stdlib.h>/*malloc free*/
#include <assert.h>/*assert*/
#include <unistd.h> /*sleep*/
#include "scheduler.h"
#include "pqueue.h"
#include "task.h"

struct scheduler
{
    pq_t *tasks;
    task_t *current_task;	
    int to_stop;
    int remove_current_task;
};

static int Rapper(void *task, void *uid);

scheduler_t *SchedulerCreate()
{
	scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == scheduler)
	{
		return NULL;
	}
	
	scheduler->tasks = PQCreate((pq_cmp_t)TaskIsBefore);
    if (NULL == scheduler->tasks)
    {
    	free(scheduler);
    	scheduler = NULL;
        return NULL;
    }
	   
    scheduler->current_task = NULL;	
    scheduler->to_stop = 0;
	scheduler->remove_current_task = 0;
	
    return scheduler;
}

void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	SchedulerClear(scheduler);
	PQDestroy(scheduler->tasks);
	free(scheduler);
	scheduler = NULL;
}

size_t SchedulerSize(const scheduler_t *scheduler)
{
	size_t is_current = 0;
	assert(NULL != scheduler);
	
	if (NULL != scheduler->current_task)
	{
		is_current = 1;
	}
	
	return (PQCount(scheduler->tasks) + is_current);
}

int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (0 == SchedulerSize(scheduler));
}

void SchedulerClear(scheduler_t *scheduler)
{
	task_t *task = NULL;
	assert(NULL != scheduler);
		
	scheduler->remove_current_task = 1;
	
	while (0 == PQIsEmpty(scheduler->tasks))
	{
		task = (task_t *)PQDequeue(scheduler->tasks);
		TaskDestroy(task);
	}	
}

ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, operation_func_t operation_func, destroy_func_t destroy_func, size_t interval, void *param)
{
	int status = 0;
	task_t *task = NULL;;
	assert(NULL != scheduler);	
	
	task = TaskCreate(operation_func, destroy_func, interval, param);
	if (NULL == task)
	{
		return GetBadUid();
	}
	
	status = PQEnqueue(scheduler->tasks, task);
	
	if (1 == status)
	{
		TaskDestroy(task);
		return GetBadUid();
	}
	
	return TaskGetUid(task);	
}

int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t task_id)
{
	task_t *task = NULL;
	assert(NULL != scheduler);	
	
	if (1 == SchedulerIsEmpty(scheduler))
	{
		return 1;
	}
	
	task = (task_t *)PQErase(scheduler->tasks, Rapper, &task_id);
	
	if (NULL == task)
	{
		return 1;
	}
	
	TaskDestroy(task);
	
	return 0;
}

sch_status_t SchedulerRun(scheduler_t *scheduler)
{
	task_status_t status = REPEAT;
	int insert_status = 0;
	assert(NULL != scheduler);
		
	scheduler->to_stop = 0;
	scheduler->remove_current_task = 0;
	
	
	while (0 == SchedulerIsEmpty(scheduler) && 0 == scheduler->to_stop)
	{
		scheduler->current_task = (task_t *)PQDequeue(scheduler->tasks);
		if (NULL == scheduler->current_task)
		{
			return (EMPTY);
		}

	    if (difftime(TaskGetTimeToRun(scheduler->current_task), time(NULL) > 0))
    	{
        	sleep(difftime(TaskGetTimeToRun(scheduler->current_task), time(NULL)));
		}
		
		status = TaskRun(scheduler->current_task);	
		if (REPEAT == status && 0 == scheduler->remove_current_task)
		{
			TaskUpdateTimeToRun(scheduler->current_task);
			insert_status = PQEnqueue(scheduler->tasks, scheduler->current_task);
			
			if (1 == insert_status)
			{
				return (MEMORY_FAIL);
			}
		}
		
		else
		{
			TaskDestroy(scheduler->current_task);
		}
		
		scheduler->current_task = NULL;
	}
	
	return (1 == SchedulerIsEmpty(scheduler) ? EMPTY : STOPPED);
}

void SchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);	
	
	scheduler->to_stop = 1;
}

static int Rapper(void *task, void *uid)
{
	return TaskIsMatch((task_t*)task, *(ilrd_uid_t *)uid);
}
