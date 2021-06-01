#include <stdlib.h>   /* malloc free NULL */
#include <assert.h>   /* assert */
#include <unistd.h> /* sleep */


#include "pqueue.h"
#include "task.h"
#include "scheduler.h"

#define TASK_DESTROY_AND_NULL TaskDestroy(scheduler->current_task);\
							  scheduler->current_task = NULL;

#define TASKS scheduler->tasks
							  
#define CURRENT_TASK scheduler->current_task

#define REMOVE_CURRENT_TASK scheduler->remove_current_task

#define TO_STOP scheduler->to_stop							  

/********************* management struct of scheduler ***************************/

struct scheduler
{
    pq_t *tasks;
    task_t *current_task;
    int remove_current_task;	
    int to_stop;
};

static int WrapperIsMatch(void * data, void *param);
static void CheckIfNeedSleep(scheduler_t * scheduler);

/************************ SchedulerCreate **********************************/

scheduler_t *SchedulerCreate()
{
	scheduler_t *scheduler = malloc(1 * sizeof(scheduler_t));
	if (NULL == scheduler)
	{
		return (NULL);
	}
	
	TASKS = PQCreate(TaskIsBefore);
	if (NULL == TASKS)
	{
		free(scheduler);
		scheduler = NULL;
		
		return (NULL);
	}
	
	CURRENT_TASK = NULL;
	REMOVE_CURRENT_TASK = 0;
	TO_STOP = 0;
	
	return (scheduler);
}

/************************ SchedulerDestroy **********************************/

void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	SchedulerClear(scheduler);
	
	PQDestroy(TASKS);
	
	free(scheduler);
	scheduler = NULL;
	
	return ;
}

/************************ SchedulerAddTask **********************************/

ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, operation_func_t operation_func, destroy_func_t destroy_func, size_t interval, void *param)
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
	
	if (1 == PQEnqueue(TASKS, task))
	{
		TaskDestroy(task);
		
		return (GetBadUid());
	}
	
	return (TaskGetUid(task));
}

/************************ SchedulerRemoveTask **********************************/

int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t task_id)
{
	task_t * task = NULL;
	
	assert(NULL != scheduler);
	
	task = PQErase(TASKS, WrapperIsMatch, &task_id);
	if (NULL == task)
	{
		return (1);
	}
	
	TaskDestroy(task);
	
	return (0);
}

/************************ SchedulerClear **********************************/

void SchedulerClear(scheduler_t *scheduler)
{
	task_t *task_ptr = NULL;
	
	assert(NULL != scheduler);
	
	if (NULL != CURRENT_TASK)
	{
		REMOVE_CURRENT_TASK = 1;
		
		while (SchedulerSize(scheduler) > 1)
		{
			task_ptr = PQDequeue(TASKS);
			
			TaskDestroy(task_ptr);
		}
	}
	else
	{
		while (0 == SchedulerIsEmpty(scheduler))
		{
			task_ptr = PQDequeue(TASKS);
			
			TaskDestroy(task_ptr);
		}
	}
	
	return ;
}

/************************ SchedulerSize **********************************/

size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (NULL == CURRENT_TASK ? PQCount(TASKS) : PQCount(TASKS) + 1);
}

/************************ TaskCreate **********************************/

int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (NULL == CURRENT_TASK ? PQIsEmpty(TASKS) : 0);
}

/************************ SchedulerRun **********************************/

sch_status_t SchedulerRun(scheduler_t *scheduler)
{
	task_status_t task_status = REPEAT;
	
	assert(NULL != scheduler);

	CURRENT_TASK = NULL;
	
	REMOVE_CURRENT_TASK = 0;
	
	TO_STOP = 0;
	
	while ((1 != TO_STOP) && (1 != SchedulerIsEmpty(scheduler)))
	{
		CURRENT_TASK = PQDequeue(TASKS);
		
		CheckIfNeedSleep(scheduler);
		
		task_status = TaskRun(CURRENT_TASK);
		
		if (1 == REMOVE_CURRENT_TASK)
		{
			TASK_DESTROY_AND_NULL
			
			return (EMPTY);
			
		} else if (REPEAT == task_status){
		
			TaskUpdateTimeToRun(CURRENT_TASK);
			
			if (1 == PQEnqueue(TASKS, CURRENT_TASK))
			{
				return (MEMORY_FAIL);
			}
		}
		else 
		{
			TASK_DESTROY_AND_NULL
		}
	}
	
	return (1 == TO_STOP ? STOPPED : EMPTY); 	
}

/************************ SchedulerStop **********************************/

void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler);
	
	TO_STOP  = 1;
	
	return ;
}

/************************ WrapperIsMatch **********************************/

static int WrapperIsMatch(void * data, void *param)
{
	return (TaskIsMatch((const task_t *)data, *(ilrd_uid_t *)param));
}


static void CheckIfNeedSleep(scheduler_t * scheduler)
{
	while (TaskGetTimeToRun(CURRENT_TASK) - time(NULL) > 0)
		{
			sleep(TaskGetTimeToRun(CURRENT_TASK) - time(NULL));
		}
	
	return ;
}

/************************ END *********************************/
