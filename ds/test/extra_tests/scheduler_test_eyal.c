#include <stdio.h> /*printf*/
#include <time.h> /*time_t*/
#include <stdlib.h>/*malloc, free*/

#include "scheduler.h"

#define TEST_NOT(str, real, expected) (real != expected ?\
							 	  printf(GREEN"\n%sSUCCESS\n"RESET, str) :\
							 	  printf(RED"\n%sFAIL\n"RESET, str))

#define TEST(str, real, expected) (real == expected ?\
							 	  printf(GREEN"\n%sSUCCESS\n"RESET, str) :\
							 	  printf(RED"\n%sFAIL\n"RESET, str))

#define RED "\033[1;31m"  /* print in red */
#define GREEN "\033[1;32m"    /* print in green */
#define BLUE "\033[1;34m"  /* print in blue */
#define YELLOW "\033[1;33m" /* print in yellow  */
#define PURPLE "\033[1;35m" /* print in purple */
#define RESET "\033[0m" /* reset print color  */

void Test(void);
void DestroyNothing(ilrd_uid_t uid, void *param);
static int Print1st(void *param);
static int Print2nd(void *param);
static int Print3rd(void *param);
static int Print4th(void *param);
static int Clear(void *param);
static int Stop(void *param);
static void AddTasks(scheduler_t *scheduler);
static void PrintStopStatus(sch_status_t status);
static int Count(void *param);

/*****************************************************************************/

int main()
{
	Test();
	return 0;
}

/******************************************************************************/

void Test(void)
{
	ilrd_uid_t task_id = {0,0,0};
	sch_status_t stop_status = 0;
	scheduler_t *sched = SchedulerCreate();
	printf(PURPLE"\n*****Create Task*****\n"RESET);
	TEST_NOT("\nTest if scheduler is NULL ---> ", sched, NULL);	
	TEST("Test Size when empty --->", SchedulerSize(sched), 0);
	TEST("Test Is Empty when empty --->", SchedulerIsEmpty(sched), 1);
	SchedulerClear(sched);
	AddTasks(sched);
	TEST("Test Is Empty when full --->", SchedulerIsEmpty(sched), 0);
	TEST("Test Size when full --->", SchedulerSize(sched), 4);
	
	printf(PURPLE"\n***Add 4 Tasks and Run untill empty***\n");
	SchedulerAddTask(sched, Count, DestroyNothing, 0, sched);
	stop_status = SchedulerRun(sched);
	PrintStopStatus(stop_status);
	AddTasks(sched);
	
	printf(PURPLE"\n***Add 4 Tasks and Run untill stopped***\n");
	SchedulerAddTask(sched, Stop, DestroyNothing, 5, sched);
	stop_status = SchedulerRun(sched);
	PrintStopStatus(stop_status);
	
	printf(PURPLE"\n***Add 4 Tasks and Run untill cleared***\n");
	SchedulerAddTask(sched, Clear, DestroyNothing, 3, sched);
	stop_status = SchedulerRun(sched);
	PrintStopStatus(stop_status);
	TEST("Test Is Empty after Clear --->", SchedulerIsEmpty(sched), 1);
	
	AddTasks(sched);
	task_id = SchedulerAddTask(sched, Clear, DestroyNothing, 2, sched);
	printf(BLUE"\n\nSize after refill : %ld", SchedulerSize(sched));
	SchedulerRemoveTask(sched, task_id);
	printf(BLUE"\n\nSize after one removal : %ld", SchedulerSize(sched));
	TEST("--->", SchedulerSize(sched), 4);
	TEST("Try to remove missing--->",SchedulerRemoveTask(sched, task_id), 1);
	
	SchedulerDestroy(sched);
	printf(PURPLE"\n*****End of Test*****\n"RESET);
}
	

/******************************************************************************/
static void AddTasks(scheduler_t *scheduler)
{
	SchedulerAddTask(scheduler, Print1st, DestroyNothing, 1, NULL);
	SchedulerAddTask(scheduler, Print3rd, DestroyNothing, 3, NULL);
	SchedulerAddTask(scheduler, Print4th, DestroyNothing, 4, NULL);
	SchedulerAddTask(scheduler, Print2nd, DestroyNothing, 2, NULL);	
}

/******************************************************************************/

static int Print1st(void *param)
{
	static int count = 0;
	param = param;
	printf(YELLOW"Me 1st\n"RESET);
	++count;
	if (4 == count || 10 == count)
	{
		return 1;
	}
	
	return 0;
}

/******************************************************************************/

static int Print2nd(void *param)
{
	static int count = 0;
	param = param;
	printf(YELLOW"Me 2nd\n"RESET);
	++count;
	if (3 == count || 8 == count)
	{
		return 1;
	}
	return 0;
}

/******************************************************************************/

static int Print3rd(void *param)
{
	static int count = 0;
	param = param;
	printf(YELLOW"Me 3rd\n"RESET);
	++count;
	if (2 == count || 6 == count)
	{
		return 1;
	}
	return 0;
}

/******************************************************************************/

static int Print4th(void *param)
{
	static int count = 0;
	param = param;
	printf(YELLOW"Me 4th\n"RESET);
	++count;
	if (1 == count || 2 == count)
	{
		return 1;
	}
	return 0;
}

/******************************************************************************/

static int Clear(void *param)
{
	printf(GREEN"Me clearing\n"RESET);
	SchedulerClear(param);
	return 0;
}

/******************************************************************************/

static int Stop(void *param)
{
	printf(GREEN"Me stopping\n"RESET);
	SchedulerStop(param);
	return 0;
}


/******************************************************************************/
static int Count(void *param)
{
	printf(GREEN"%ld tasks counted in scheduler\n"RESET, SchedulerSize(param));
	return 1;
}


/******************************************************************************/

void DestroyNothing(ilrd_uid_t uid, void *param)
{
	uid = uid;
	param = param;
}

/******************************************************************************/

static void PrintStopStatus(sch_status_t status)
{
	if (EMPTY == status)
	{	
		printf(RED"Stop Status : EMPTY\n\n"RESET);
	}
	if (MEMORY_FAIL == status)
	{	
		printf(RED"Stop Status : MEMORY_FAIL\n\n"RESET);
	}
	if (STOPPED == status)
	{	
		printf(RED"Stop Status : STOPPED\n\n"RESET);
	}
}

