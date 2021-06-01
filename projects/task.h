/*****************************************************************************/

#ifndef __TASK_H__
#define __TASK_H__

/*****************************************************************************/

#include <time.h> /* time_t */

#include "uid.h" 

typedef struct task task_t;
typedef int(*task_func_t)(void *param); /* 0 = REPEAT , 1 = DONT_REPEAT */
typedef void(*task_destroy_func_t)(ilrd_uid_t uid, void *param);

typedef enum
{
	REPEAT = 0,
	DONT_REPEAT = 1
} task_status_t;


/*****************************************************************************/

/*
@Description: The function creates a new task.
@return: The function returns a pointer to the new task.
@errors: Returns NULL if malloc fails.
*/
task_t *TaskCreate(task_func_t task_func, task_destroy_func_t destroy_func, size_t interval, void *param);

/*****************************************************************************/

/*
Description: The function frees the task.
@params: The function gets a pointer to the task.
*/
void TaskDestroy(task_t *task);

/*****************************************************************************/

/*
Description: The function return time to run of the task.
@params: The function gets a pointer to the task.
@return: time_t time_to_run.
*/
time_t TaskGetTimeToRun(task_t *task);

/*****************************************************************************/

/*
Description: The function run the task function.
@params: The function gets a pointer to the task.
@return: REPEAT / DONT_REPEAT
*/
task_status_t TaskRun(task_t *task);

/*****************************************************************************/

/*
Description: The function check if two tasks are the same.
@params: The function gets a pointers to 2 tasks.
@return: 1 for TRUE, 0 for FALSE.
*/
int TaskIsMatch(const task_t *task, ilrd_uid_t task_id); 

/*****************************************************************************/

/*
Description: The function return uid of the task.
@params: The function gets a pointer to the task.
@return: ilrd_uid_t
*/
ilrd_uid_t TaskGetUid(const task_t *task);

/*****************************************************************************/

/*
Description: The function update the time_to_run of the task.
@params: The function gets a pointer to the task.
*/
void TaskUpdateTimeToRun(task_t *task);

/*****************************************************************************/

/*
Description: The function compare time to run of two tasks and check if task1
run before task2.
@params: The function gets a pointers to 2 tasks.
@return: 1 for TRUE, 0 for FALSE.
*/
int TaskIsBefore(void *task1, void *task2);



#endif /* __TASK_H__ */

/*****************************************************************************/
