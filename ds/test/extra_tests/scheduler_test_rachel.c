#include <stdlib.h> /* system */
#include <stdio.h> /* printf */

#include "scheduler.h"

#define RED "\033[1;31m" 
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"
#define PURPLE "\033[1;35m"
#define RESET "\033[0m" 


#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)

typedef enum
{
	SUCCESS = 0,
	CREATE_FAIL = 1,
	ADD_TASK_FAIL = 2
} test_status_t;


static test_status_t Test();  
  
int main()
{
	int status = SUCCESS;
	
    system("clear");
    
    status = Test();

    return (status); 
}

int IntPrint(void *param);
int PrintHello(void *param);
int ToStop(void *param);
void DestroyDummy(ilrd_uid_t uid, void *param);

static test_status_t Test()
{
	int param1 = 3;
	ilrd_uid_t task_id1 = {0};
	ilrd_uid_t task_id2 = {0};
	ilrd_uid_t task_id3 = {0};
	ilrd_uid_t bad_uid = GetBadUid();
	scheduler_t *scheduler = SchedulerCreate(); 
       
    if (NULL == scheduler)
    {
    	return (CREATE_FAIL);
    } 
    
    printf(PURPLE"\tScheduler Test\n\n"WHITE);
    
    TEST("SchedulerCreate", (scheduler == NULL), 0);
	TEST("SchedulerIsEmpty", SchedulerIsEmpty(scheduler), 1);
    
    task_id1 = SchedulerAddTask(scheduler, IntPrint, DestroyDummy, 5 , &param1);
    if (1 == UidIsSame(task_id1, bad_uid))
    {
    	SchedulerDestroy(scheduler);
    	return (ADD_TASK_FAIL);
    }
    
    TEST("SchedulerAddTask", UidIsSame(task_id1, bad_uid), 0);

	TEST("SchedulerIsEmpty", SchedulerIsEmpty(scheduler), 0);
	TEST("SchedulerSize", SchedulerSize(scheduler), 1);
	
	TEST("SchedulerRemoveTask", SchedulerRemoveTask(scheduler, task_id1), 0);
	TEST("SchedulerSize", SchedulerSize(scheduler), 0);
	
	task_id1 = SchedulerAddTask(scheduler, IntPrint, DestroyDummy, 5 , &param1);
    if (1 == UidIsSame(task_id1, bad_uid))
    {
    	SchedulerDestroy(scheduler);
    	return (ADD_TASK_FAIL);
    }
    
    task_id2 = SchedulerAddTask(scheduler, PrintHello, DestroyDummy, 3 , NULL);
    if (1 == UidIsSame(task_id2, bad_uid))
    {
    	SchedulerDestroy(scheduler);
    	return (ADD_TASK_FAIL);
    }

	SchedulerClear(scheduler);
	TEST("SchedulerClear", SchedulerIsEmpty(scheduler), 1);
	
	task_id1 = SchedulerAddTask(scheduler, IntPrint, DestroyDummy, 3 , &param1);
    if (1 == UidIsSame(task_id1, bad_uid))
    {
    	SchedulerDestroy(scheduler);
    	return (ADD_TASK_FAIL);
    }
    
    task_id2 = SchedulerAddTask(scheduler, PrintHello, DestroyDummy, 5 , NULL);
    if (1 == UidIsSame(task_id2, bad_uid))
    {
    	SchedulerDestroy(scheduler);
    	return (ADD_TASK_FAIL);
    }
    
    task_id3 = SchedulerAddTask(scheduler, ToStop, DestroyDummy, 1 , scheduler);
    if (1 == UidIsSame(task_id3, bad_uid))
    {
    	SchedulerDestroy(scheduler);
    	return (ADD_TASK_FAIL);
    }
    
    TEST("SchedulerStop", SchedulerRun(scheduler), 2);
    
    printf(CYAN"-----------SchedulerRun-----------\n"WHITE);

	TEST("SchedulerRun", SchedulerRun(scheduler), 0);
	
    SchedulerDestroy(scheduler);
    
    printf(PURPLE"\tEnd Test\n\n"WHITE);
    
    return (SUCCESS);
}

/****************************Tasks********************************************/

int IntPrint(void *param)
{
	static int count = 0;
	int a = *(int *)param;

	count++;

	printf("%d\n" ,a);

	if (3 == count)
	{
		return (1);
	}
		
	return (0);
}

int PrintHello(void *param)
{
	static int count = 0;

	(void)param;
	count++;

	printf("Hello!\n");

	if (2 == count)
	{
		return (1);
	}
		
	return (0);
}

int ToStop(void *param)
{
	SchedulerStop((scheduler_t*)param);
		
	return (1);
}

void DestroyDummy(ilrd_uid_t uid, void *param)
{
	uid = uid;
	param = param;
}

