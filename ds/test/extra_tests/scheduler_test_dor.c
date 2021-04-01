/*****************************************************************************/

#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

/*****************************************************************************/

#include "scheduler.h"

/*****************************************************************************/

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define WHITE "\033[0m"

#define TEST_ARE_EQUAL(name, actual, expected)\
     printf("%s\n%s\n\n", name, actual == expected ? GREEN"PASSED"WHITE : RED"FAILED"WHITE)
     
#define TEST_ARE_NOT_EQUAL(name, actual, expected)\
     printf("%s\n%s\n\n", name, actual != expected ? GREEN"PASSED"WHITE : RED"FAILED"WHITE)
     
#define TEST_IS_LESS_THAN(name, actual, expected)\
     printf("%s\n%s\n\n", name, actual < expected ? GREEN"PASSED"WHITE : RED"FAILED"WHITE)

/*****************************************************************************/

void TestSchedulerCreate(void);

void TestSchedulerAddTask(void);

void TestSchedulerRemoveTask(void);

void TestSchedulerClear(void); 

void TestSchedulerSize(void);

void TestSchedulerIsEmpty(void);

void TestSchedulerRun(void);

void TestSchedulerStop(void);

int OperationFuncPrint1(void *param);

int OperationFuncPrint2(void *param);

int OperationFuncClear(void *param);

void DestroyFunc(ilrd_uid_t uid, void *param);

static int counter_print1 = 0;
static int counter_print2 = 0;

/*****************************************************************************/

int main()
{
    TestSchedulerCreate();

    TestSchedulerAddTask();

    TestSchedulerRemoveTask();

    TestSchedulerClear();

    TestSchedulerSize();

    TestSchedulerIsEmpty();

    TestSchedulerRun();

    return (0);
}

/*****************************************************************************/

void TestSchedulerCreate()
{
	scheduler_t *scheduler = SchedulerCreate();
	
	TEST_ARE_NOT_EQUAL("TestSchedulerCreate", scheduler, NULL);
	
	SchedulerDestroy(scheduler);
}

/*****************************************************************************/

void TestSchedulerAddTask()
{
	scheduler_t *scheduler = SchedulerCreate();
	ilrd_uid_t uid = {0};
	
	size_t interval = 5;
	char *param = "Hello";
	
	uid = SchedulerAddTask(scheduler, OperationFuncPrint1, DestroyFunc, interval, (void *)param);
	
	TEST_ARE_EQUAL("TestSchedulerAddTask1", UidIsSame(uid, GetBadUid()), 0);
	TEST_ARE_EQUAL("TestSchedulerAddTask2", SchedulerSize(scheduler), 1);
	
	SchedulerDestroy(scheduler);
}

/*****************************************************************************/

void TestSchedulerRemoveTask()
{	
	scheduler_t *scheduler = SchedulerCreate();	
	ilrd_uid_t uid = {0};
	size_t interval = 5;
	char *param = "Hello";
	
	uid = SchedulerAddTask(scheduler, OperationFuncPrint1, DestroyFunc, interval, (void *)param);
	SchedulerRemoveTask(scheduler, uid);
	
	TEST_ARE_EQUAL("TestSchedulerRemoveTask", SchedulerIsEmpty(scheduler), 1);
	
	SchedulerDestroy(scheduler);
}

/*****************************************************************************/

void TestSchedulerClear()
{
	scheduler_t *scheduler = SchedulerCreate();
	size_t interval = 5;
	char *param = "Hello";
	
	SchedulerAddTask(scheduler, OperationFuncPrint1, DestroyFunc, interval, (void *)param);
	SchedulerClear(scheduler);
	
	TEST_ARE_EQUAL("TestSchedulerClear", SchedulerIsEmpty(scheduler), 1);
	
	SchedulerDestroy(scheduler);
}

/*****************************************************************************/

void TestSchedulerSize()
{
	scheduler_t *scheduler = SchedulerCreate();
	
	TEST_ARE_EQUAL("TestSchedulerSize", SchedulerSize(scheduler), 0);
	
	SchedulerDestroy(scheduler);
}

/*****************************************************************************/

void TestSchedulerIsEmpty()
{
	scheduler_t *scheduler = SchedulerCreate();
	
	TEST_ARE_EQUAL("TestSchedulerIsEmpty", SchedulerIsEmpty(scheduler), 1);
	
	SchedulerDestroy(scheduler);
}

/*****************************************************************************/

void TestSchedulerRun()
{
	scheduler_t *scheduler = SchedulerCreate();
	char *param1 = "Hello";
	char *param2 = "World";
	
	counter_print1 = 0;
	counter_print2 = 0;
	
	SchedulerAddTask(scheduler, OperationFuncPrint1, DestroyFunc, 1, (void *)param1);
	SchedulerAddTask(scheduler, OperationFuncPrint2, DestroyFunc, 3, (void *)param2);
	SchedulerAddTask(scheduler, OperationFuncClear, DestroyFunc, 8, (void *)scheduler);
	
	TEST_ARE_EQUAL("TestSchedulerRun1", SchedulerRun(scheduler), EMPTY);
	TEST_IS_LESS_THAN("TestSchedulerRun2", counter_print1, 10);	
	TEST_IS_LESS_THAN("TestSchedulerRun3", counter_print2, 10);	
	
	SchedulerAddTask(scheduler, OperationFuncPrint1, DestroyFunc, 2, (void *)param1);
	SchedulerAddTask(scheduler, OperationFuncPrint2, DestroyFunc, 3, (void *)param2);
	SchedulerAddTask(scheduler, OperationFuncClear, DestroyFunc, 1, (void *)scheduler);
	
	TEST_ARE_EQUAL("TestSchedulerRun4 after reinserting", SchedulerRun(scheduler), EMPTY);
	
	SchedulerDestroy(scheduler);
}

/*****************************************************************************/

int OperationFuncPrint1(void *param)
{
	printf("%s\n", (char *)param);
	counter_print1++;
		
	return (counter_print1 == 10);
}

/*****************************************************************************/

int OperationFuncPrint2(void *param)
{
	printf("%s\n", (char *)param);
	counter_print2++;
		
	return (counter_print2 == 10);
}

/*****************************************************************************/

int OperationFuncClear(void *param)
{
	SchedulerClear((scheduler_t *)param);
	
	return (0);
}

/*****************************************************************************/

void DestroyFunc(ilrd_uid_t uid, void *param)
{
	uid = uid;
	param = param;
}

/*****************************************************************************/
