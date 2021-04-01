#include <stdio.h> /*printf*/

#include "scheduler.h"


#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST_ARE_EQUAL(name, expected, actual)\
	 printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
#define TEST_ARE_NOT_EQUAL(name, expected, actual)\
	  printf("%s: %s\n\n", name, actual != expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)



void TestSchedulerGeneral(void);

void destroy_func(ilrd_uid_t uid, void *param); 
int operation_func1(void *x); 
int operation_func2(void *x); 
int operation_func(void *x); 
int OperationFuncClear(void *param); 

int main()
{
	TestSchedulerGeneral();

	return 0; 
}


void TestSchedulerGeneral()
{
	scheduler_t *scheduler = SchedulerCreate(); 

	int one = 1; 
	int two = 2; 
	int three = 3; 
	
	ilrd_uid_t uid1, uid2, uid3; 
	
	printf(CYAN"\t scheduler Test\n\n"WHITE); 
	
	TEST_ARE_EQUAL("SchedulerCreate Test", (scheduler ? 1:0), 1); 
	TEST_ARE_EQUAL("SchedulerSize Test", SchedulerSize(scheduler), 0); 
	TEST_ARE_EQUAL("SchedulerIsEmpty Test", SchedulerIsEmpty(scheduler), 1); 
	
	uid1 = SchedulerAddTask(scheduler, operation_func, destroy_func, 1, &one); 
	uid2 = SchedulerAddTask(scheduler, operation_func, destroy_func, 4, &two); 
	uid3 = SchedulerAddTask(scheduler, operation_func2, destroy_func, 2, &three); 
	
	TEST_ARE_EQUAL("AddTask Test1 - check the UID", UidIsSame(uid1, uid2), 0); 
	TEST_ARE_EQUAL("AddTask Test2 - check the UID", UidIsSame(uid1, uid3), 0); 
	
	TEST_ARE_EQUAL("SchedulerSize Test", SchedulerSize(scheduler), 3); 
	TEST_ARE_EQUAL("SchedulerIsEmpty Test", SchedulerIsEmpty(scheduler), 0); 
	
	TEST_ARE_EQUAL("SchedulerRemoveTask Test1", SchedulerRemoveTask(scheduler, uid1), 0); 

	TEST_ARE_EQUAL("SchedulerRemoveTask + Size Test", SchedulerSize(scheduler), 2);
	
	TEST_ARE_EQUAL("SchedulerRUNTask Test", SchedulerRun(scheduler), 0);
	
	uid1 = SchedulerAddTask(scheduler, operation_func, destroy_func, 5, &one); 
	uid2 = SchedulerAddTask(scheduler, operation_func1, destroy_func, 1, scheduler); 
	uid3 = SchedulerAddTask(scheduler, operation_func2, destroy_func, 3, &three); 
	
	TEST_ARE_EQUAL("SchedulerRUNTask with stop Test", SchedulerRun(scheduler), 2);
	
	TEST_ARE_EQUAL("Size Test after run with stop", SchedulerSize(scheduler), 2);
	
	uid2 = SchedulerAddTask(scheduler, OperationFuncClear, destroy_func, 0, scheduler);
	
	SchedulerRun(scheduler); 
	
	TEST_ARE_EQUAL("Size Test after run with clear", SchedulerSize(scheduler), 0);
	
	SchedulerDestroy(scheduler); 
}

/*********************************Operation Funcs ********************************/

int OperationFuncClear(void *param)
{
	SchedulerClear((scheduler_t *)param);
	
	return (0);
}

int operation_func(void *x)
{
	printf("data = %d \n", *(int *)x);

	return (1); 
}

int operation_func2(void *x)
{
	static int status = 0; 
	
	while (status < 6)
	{
		printf("%d -->\n", *(int *)x);
		status++;
		return (0); 
	}
	return(1); 
}

int operation_func1(void *x)
{
	printf("to stop \n");
	SchedulerStop((scheduler_t *)x); 
	return(1); 
}


/*********************************Destroy Func ********************************/

void destroy_func(ilrd_uid_t uid, void *param)
{
	uid = uid; 
	param = param; 
	return; 
}


