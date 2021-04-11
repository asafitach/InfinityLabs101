#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <unistd.h> /* sleep */
#include <string.h> /* strcpy */

#include "scheduler.h"

/*********************************Test Macros**********************************/

#define TEST(name, real, expected) \
		printf(CYAN"%s %s\n", name, real == expected ? \
		GREEN"SUCCESS"RESET : RED"FAIL"RESET)
		
#define TEST_NOT(name, real, expected) \
		printf(CYAN"%s %s\n", name, real != expected ? \
		GREEN"SUCCESS"RESET : RED"FAIL"RESET)
		
/******************************Color definitions*******************************/

#define RED "\033[5;91m"           /* print in red          */
#define GREEN "\033[1;38;5;47m"    /* print in green        */
#define MAGEN "\033[0;38;5;183m"   /* print in magenta      */
#define YELLOW "\033[1;38;5;220m"  /* print in light yellow */
#define CYAN "\033[0;96m"          /* print in cyan         */
#define LIGHT "\033[2;37m"         /* print in gray         */
#define PURPLE "\033[1;4;38;5;224m"/* print in purple       */
#define RESET "\033[1;0m"          /* reset print color     */

/******************************************************************************/

#define SIZE_OF_ARRAY (5)

char *array[SIZE_OF_ARRAY] = {NULL};

/******************************************************************************/

static scheduler_t *TestCreate();
static void TestIsEmpty(scheduler_t *scheduler, int expected);
static ilrd_uid_t TestAddTask(scheduler_t *scheduler, 
operation_func_t operation_func, destroy_func_t destroy_func, 
size_t interval, void *param);
static void TestRemove(scheduler_t *scheduler, ilrd_uid_t task_uid);
static void TestClear(scheduler_t *scheduler);


static void TestDestroyFunc(scheduler_t *scheduler);
static void TestAddClearFromTask(scheduler_t *scheduler, char *string);
static void TestRunStop(scheduler_t *scheduler, char *string);
static void TestAddClear(scheduler_t *scheduler, char *string);
static void TestAddRemove(scheduler_t *scheduler, char *string);

void DestroyNone(ilrd_uid_t uid, void *param);
int PrintChar(void *param);
int StopScheduler(void *param);
int PrintSizeAndIsEmpty(void *param);
int ClearScheduler(void *param);
int PrintString(void *param);
void DestroyArray(ilrd_uid_t uid, void *param);
	
/*************************************Main*************************************/

int main()
{
	char *string = "Hello World!";
	scheduler_t *scheduler = NULL;
	
	printf(YELLOW"\n**********Testing Scheduler**********\n\n"RESET);
	printf(MAGEN"--Creating a scheduler & testing IsEmpty--\n\n"RESET);
	scheduler = TestCreate();
	TestIsEmpty(scheduler, 1);
	
	TestAddRemove(scheduler, string);
	TestAddClear(scheduler, string);
	TestRunStop(scheduler, string);
	TestAddClearFromTask(scheduler, string);
	TestDestroyFunc(scheduler);
	
	SchedulerDestroy(scheduler);
	
	printf(YELLOW"\n**********End Of Test**********\n\n"RESET);
	return (0);
}

/******************************************************************************/


static void TestAddRemove(scheduler_t *scheduler, char *string)
{
	ilrd_uid_t uid = GetBadUid();
	
	printf(PURPLE"\n\n------Test1: Add->Remove------\n"RESET);
	printf(MAGEN"\n--Adding & removing 1 task--\n"RESET);
	uid = TestAddTask(scheduler, PrintChar, DestroyNone, 1, string);
	TestRemove(scheduler, uid);
	TestIsEmpty(scheduler, 1);
}


static void TestAddClear(scheduler_t *scheduler, char *string)
{
	printf(PURPLE"\n\n------Test2: Add x3 ->Clear------\n"RESET);
	printf(MAGEN"\n--Adding 3 task, testing size & clear--\n"RESET);
	TestAddTask(scheduler, PrintChar, DestroyNone, 2, string);
	TestAddTask(scheduler, PrintChar, DestroyNone, 1, string);
	TestAddTask(scheduler, PrintChar, DestroyNone, 3, string);
	
	TEST("SchedulerSize      ", SchedulerSize(scheduler), 3);
	TestClear(scheduler);
	TestIsEmpty(scheduler, 1);
}


static void TestRunStop(scheduler_t *scheduler, char *string)
{
	sch_status_t status = EMPTY;
	printf(PURPLE"\n\n------Test3: Add x3 ->Run->Stop->Run------\n"RESET);
	printf(MAGEN"\n--Adding"YELLOW" StopScheduler "MAGEN"task, once at 6 sec--\n"RESET);
	TestAddTask(scheduler, StopScheduler, DestroyNone, 6, scheduler);
	
	printf(MAGEN"\n--Adding"YELLOW" PrintSizeAndIsEmpty "MAGEN"task, once at 15 seconds--\n"RESET);
	TestAddTask(scheduler, PrintSizeAndIsEmpty, DestroyNone, 15, scheduler);
	
	printf(MAGEN"\n--Adding"YELLOW" PrintChar "MAGEN"task, interval 1 sec--\n"RESET);
	TestAddTask(scheduler, PrintChar, DestroyNone, 1, string);
	
	printf(MAGEN"\n--Running scheduler (expecting stopped return value)--\n"RESET);
	printf("\n-Expected: Printing H e l l o , then stopped!-\n");
	status = SchedulerRun(scheduler);
	TEST("SchedulerRun       ", STOPPED, status);
	
	printf(MAGEN"\n--Continuing run after scheduler stopped (running until empty)--\n"RESET);
	printf("\n-Expected: Printing W o r l d !, then Size and IsEmpty-\n");
	status = SchedulerRun(scheduler);
	TEST("SchedulerRun       ", EMPTY, status);
	TestIsEmpty(scheduler, 1);
}



static void TestAddClearFromTask(scheduler_t *scheduler, char *string)
{
	sch_status_t status = EMPTY;
	printf(PURPLE"\n\n------Test4: Add->Add(clear)->Run------\n"RESET);
	printf(MAGEN"\n--Adding"YELLOW" PrintChar "MAGEN"task, interval 1 sec--\n"RESET);
	TestAddTask(scheduler, PrintChar, DestroyNone, 1, string);
	
	printf(MAGEN"\n--Adding"YELLOW" ClearScheduler "MAGEN"task, once at 5 sec--\n"RESET);
	TestAddTask(scheduler, ClearScheduler, DestroyNone, 5, scheduler);
	
	printf(MAGEN"\n--Running scheduler (expecting empty return value)--\n"RESET);
	printf("\n-Expected: Printing H e l l, then cleared!-\n");
	status = SchedulerRun(scheduler);
	TEST("SchedulerRun       ", EMPTY, status);
	TestIsEmpty(scheduler, 1);
}


static void TestDestroyFunc(scheduler_t *scheduler)
{
	sch_status_t status = EMPTY;
	printf(PURPLE"\n\n------Test5: Add->Run **task function with malloc**------\n"RESET);
	TestAddTask(scheduler, PrintString, DestroyArray, 1, NULL);
	
	printf(MAGEN"\n--Running scheduler (expecting empty return value)--\n"RESET);
	printf("\n-Expected: Printing SUCCESS x 5-\n");
	status = SchedulerRun(scheduler);
	TEST("SchedulerRun       ", EMPTY, status);
	TestIsEmpty(scheduler, 1);
}





static scheduler_t *TestCreate()
{
	scheduler_t *scheduler = SchedulerCreate();
	
	TEST_NOT("SchedulerCreate    ", scheduler, NULL);
	
	return (scheduler);
}

static void TestIsEmpty(scheduler_t *scheduler, int expected)
{
	int is_empty = SchedulerIsEmpty(scheduler);
	
	TEST("SchedulerIsEmpty   ", is_empty, expected);
	if (1 == is_empty)
	{
		printf(LIGHT"Scheduler is empty\n"RESET);
	}
	else
	{
		printf("Scheduler is not empty\n");		
	}
}


static ilrd_uid_t TestAddTask(scheduler_t *scheduler, 
operation_func_t operation_func, destroy_func_t destroy_func, 
size_t interval, void *param)
{
	size_t size = SchedulerSize(scheduler);
	
	ilrd_uid_t new_uid = SchedulerAddTask(scheduler, operation_func, destroy_func, interval, param);
	
	TEST("SchedulerAddTask   ", size + 1, SchedulerSize(scheduler));
	return (new_uid);
}


static void TestRemove(scheduler_t *scheduler, ilrd_uid_t task_uid)
{
	size_t size = SchedulerSize(scheduler);
	int result = SchedulerRemoveTask(scheduler, task_uid);
	
	printf("Testing by return value:\n");
	TEST("SchedulerRemoveTask", 0, result);
	
	printf("Testing by size of scheduler:\n");
	TEST("SchedulerRemoveTask", size - 1, SchedulerSize(scheduler));
	
}

static void TestClear(scheduler_t *scheduler)
{
	SchedulerClear(scheduler);
	TEST("SchedulerClear     ", 0, SchedulerSize(scheduler));
	
}

/******************************************************************************/


int PrintChar(void *param)
{
	static size_t i = 0;
	char *string = (char *)param;
	
	while ('\0' != *(string + i))
	{
		printf("%c ", *(string + i));
		fflush(stdout);
		++i;
		return (0);
	}
	printf("\n");
	i = 0;
	return(1);
}

int PrintString(void *param)
{
	static size_t i = 0;
	param = param;
	
	while (SIZE_OF_ARRAY > i)
	{
		array[i] = malloc(sizeof(char) * 8);
		strcpy(array[i], "SUCCESS");
		printf("%s\n", array[i]);
		++i;
		return (0);
	}
	i = 0;
	return(1);
}


int PrintSizeAndIsEmpty(void *param)
{
	printf("Size of scheduler:   %lu\n", SchedulerSize((scheduler_t *)param));
	printf("Is scheduler empty?: %d\n", SchedulerIsEmpty((scheduler_t *)param));
	return(1);
}


int StopScheduler(void *param)
{
	printf("Stopped!\n");
	SchedulerStop((scheduler_t *)param);
	return(1);
}


int ClearScheduler(void *param)
{
	printf("Cleared!\n");
	SchedulerClear((scheduler_t *)param);
	return(1);
}


void DestroyNone(ilrd_uid_t uid, void *param)
{
	uid = uid;
	param = param;
	
}


void DestroyArray(ilrd_uid_t uid, void *param)
{
	size_t i = 0;
	uid = uid;
	param = param;
	
	while (SIZE_OF_ARRAY > i)
	{
		free(array[i]);
		++i;
	}
	
}
