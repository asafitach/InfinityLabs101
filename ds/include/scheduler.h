/*****************************************************************************/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

/*****************************************************************************/

#include <stddef.h> /* size_t */

#include "uid.h"

typedef enum 
{
	EMPTY = 0,
	MEMORY_FAIL = 1,
	STOPPED = 2
} sch_status_t;

typedef struct scheduler scheduler_t;
typedef int(*operation_func_t)(void *param); /* 0 = REPEAT , 1 = DONT_REPEAT */
typedef void(*destroy_func_t)(ilrd_uid_t uid, void *param);


/*****************************************************************************/

/*
Description: The function creates a new Scheduler.
@return: The function returns a pointer to the new Scheduler.
@errors: Returns NULL if malloc fails.
*/
scheduler_t *SchedulerCreate();

/*****************************************************************************/

/*
@Description: The function destroy the Scheduler.
@params: The function gets a pointer to the Scheduler.
*/
void SchedulerDestroy(scheduler_t *scheduler);


/*****************************************************************************/

/*
Description: The function add task to the scheduler.
@params: The function gets a pointer to the scheduler, operation_func, interval 
and param.
@return: UID. (task id)
@errors: Returns BadUid.
*/
ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, operation_func_t operation_func, destroy_func_t destroy_func, size_t interval, void *param);

/*****************************************************************************/

/*
Description: The function remove task from scheduler.
@params: The function gets a pointer to the scheduler and task id.
*/
int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t task_id);

/*****************************************************************************/

/*
Description: The function remove all tasks from the scheduler.

*/
void SchedulerClear(scheduler_t *scheduler);

/*****************************************************************************/

/*
Description: The function return the number of tasks in the scheduler.
@params: The function gets a pointer to the scheduler.
@return: size_t.
*/
size_t SchedulerSize(const scheduler_t *scheduler);

/*****************************************************************************/

/*
Description: The function checks if the scheduler is empty. 
@params: pointer to scheduler.
@return: 1 for TRUE, 0 for FALSE
*/
int SchedulerIsEmpty(const scheduler_t *scheduler);

/*****************************************************************************/

/*
Description: The function run all the tasks function in the scheduler.
@params: The function gets a pointer to the scheduler
@return: sch_status_t
*/
sch_status_t SchedulerRun(scheduler_t *scheduler);

/*****************************************************************************/

/*
Description: The function stop the scheduler.
@params: The function gets a pointer to the scheduler.
*/
void SchedulerStop(scheduler_t *scheduler);

#endif /* __SCHEDULER_H__ */

/*****************************************************************************/
