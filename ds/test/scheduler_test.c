#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include <string.h>
#include <unistd.h>/* sleep */

#include "libmylib.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define D "\033[1;33m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", D name WHITE, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void TestSimple(); 
void TestMedium();

char **arr = NULL;
	
int main()
{
    system("clear");
    
    TestSimple(); 
    TestMedium();
    
    return 0; 
}

void TestSimple()
{
	scheduler_t *sched = NULL;
	
    printf(CYAN"\tTest simple \n\n"WHITE); 
    
    sched = SchedulerCreate();
    TEST("create ", (NULL != sched), 1); 
    
    TEST("is empty  ", SchedulerIsEmpty(sched) , 1); 
    
    TEST("size ", SchedulerSize(sched) , 0); 
    
    SchedulerDestroy(sched);
}

/******************************************************************************/

int MallocFunc(void *counter)
{
	if (*(size_t *)counter == 3)
	{
		return (1);
	}
	*((arr) + *(size_t *)counter) = (char *)malloc(sizeof(char) * 12);
	strncpy(*(arr + *(size_t *)counter), "hello world", 12);
	(*(size_t *)counter)++;
	
	
	return (0);
}


void FreeFunc(ilrd_uid_t uid, void *counter)
{
	uid = uid;
	while (1)
	{
		if (*(size_t *)counter == 0)
		{
			free(arr);
			return;
		}
		free(*(arr + *(size_t *)counter));
		(*(size_t *)counter)--;
	}
	free(arr);
}

int Stop(void *param)
{
	sleep(3);
	SchedulerStop(*(scheduler_t **)param);
	return (1);
}

int PrintVal(void *param)
{
	printf("%s\n", (char *)param);
	return (1);
}
void DestroyEmpty(ilrd_uid_t uid, void *param)
{
	uid = uid;
	param = param;
}

void TestMedium()
{
	scheduler_t *sched = NULL;
	ilrd_uid_t uid;
	static size_t counter = 0;
	char *str = "hello world";
	arr = (char **)malloc(sizeof(char *) * 4);
	
    printf(CYAN"\tTest medium \n\n"WHITE); 
    
    sched = SchedulerCreate();
    TEST("create ", (NULL != sched), 1); 
    
    TEST("is empty  ", SchedulerIsEmpty(sched) , 1); 
    
    uid = SchedulerAddTask(sched, MallocFunc, FreeFunc, 3, (void *)&counter);
    uid = SchedulerAddTask(sched, PrintVal, DestroyEmpty, 1, (void *)str);    
	uid = SchedulerAddTask(sched, Stop, DestroyEmpty, 2, (void *)&sched);    
	uid = SchedulerAddTask(sched, PrintVal, DestroyEmpty, 8, (void *)str);    
	
	SchedulerRemoveTask(sched, uid);
    
    TEST("size + remove ", SchedulerSize(sched) , 3); 
    
	TEST("is empty when full ", SchedulerIsEmpty(sched) , 0); 
	
	TEST("run ", SchedulerRun(sched) , 2); 
	
	TEST("size ", SchedulerSize(sched) , 1); 

	SchedulerClear(sched);
    
    TEST("is empty  ", SchedulerIsEmpty(sched) , 1); 
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 
    SchedulerDestroy(sched);
}
/*
void Test()
{
    printf(CYAN"\tTest \n\n"WHITE); 
    
    TEST("  ", 1 , 1); 
    
    TEST("  ", 1 , 1); 
    
    TEST("  ", 1 , 1); 
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 
}

void Test()
{
    printf(CYAN"\tTest \n\n"WHITE); 
    
    TEST("  ", 1 , 1); 
    
    TEST("  ", 1 , 1); 
    
    TEST("  ", 1 , 1); 
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 
}*/
