#include <stdlib.h>   /* malloc free NULL */
#include <assert.h>   /* assert */

#include "task.h"

/********************* management struct of task ***************************/

struct task
{
    ilrd_uid_t uid;
    task_func_t task_func; 
    task_destroy_func_t destroy_func;
    size_t interval;
    time_t time_to_run;
    void * param;
};

/************************ TaskCreate **********************************/

task_t *TaskCreate(task_func_t task_func, task_destroy_func_t destroy_func, size_t interval, void *param)
{
	task_t *task = NULL;
	
	assert(NULL != task_func);
	assert(NULL != destroy_func);
	
	task = malloc(1 * sizeof(task_t));
	if (NULL == task)
	{
		return (NULL);
	}
	
	task->uid = UidCreate();
	task->task_func = task_func;
	task->destroy_func = destroy_func;
	task->interval = interval;
	task->time_to_run = time(NULL) + (time_t)interval;
	task->param = param;
	
	return (task);
}

/************************ TaskDestroy **********************************/

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	task->destroy_func(task->uid, task->param);
	
	free(task);
	task = NULL;
	
	return ;
}

/************************ TaskGetTimeToRun **********************************/

time_t TaskGetTimeToRun(task_t *task)
{
	assert(NULL != task);
	
	return (task->time_to_run);
}

/************************ TaskRun **********************************/

task_status_t TaskRun(task_t *task)
{
	assert(NULL != task);
	
	return (task->task_func(task->param) ? DONT_REPEAT : REPEAT);
}

/************************ TaskIsMatch **********************************/
int TaskIsMatch(const task_t *task, ilrd_uid_t task_id)
{
	assert(NULL != task);
	
	return (UidIsSame(task->uid, task_id));
}

/************************ TaskGetUid **********************************/

ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(NULL != task);
	
	return (task->uid);
}

/************************ TaskUpdateTimeToRun **********************************/

void TaskUpdateTimeToRun(task_t *task)
{
	assert(NULL != task);
	
	task->time_to_run = time(NULL) + (time_t)task->interval;
	
	return ;
}

/************************ TaskIsBefore **********************************/

int TaskIsBefore(void *task1, void *task2)
{
	time_t time1 = 0;
	time_t time2 = 0;
	
	assert(NULL != task1);
	assert(NULL != task2);
	
	time1 = TaskGetTimeToRun((task_t *)task1);
	time2 = TaskGetTimeToRun((task_t *)task2);
	
	return ((time1 - time2 <= 0) ? 1 : 0);
}

/************************ END *********************************/
