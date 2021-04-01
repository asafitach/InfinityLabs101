#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include <unistd.h>

#include "task.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void TestOneTask(); 
void Test2Tasks();

int main()
{
    system("clear");
	printf(CYAN"\tTest \n\n"WHITE); 

    TestOneTask(); 
    Test2Tasks();
	
	printf(CYAN"\tEnd Test \n\n"WHITE); 
    return 0; 
}


int PrintVal(void *param)
{
	printf("%s\n", (char *)param);
	return (DONT_REPEAT);
}
void DestroyEmpty(ilrd_uid_t uid, void *param)
{
	uid = uid;
	param = param;
}

void TestOneTask()
{
	task_t *task1 = NULL;
	time_t time_to_run = 0;
	size_t interval = 0;
	char *str = "hello world";
	
	task1 = TaskCreate(PrintVal, DestroyEmpty, interval, (void *)str);
	TEST("create ", (task1 != NULL) , 1); 
	time_to_run = TaskGetTimeToRun(task1);
	TEST("time to run ", !(time_to_run) , 0); 
	TEST("run ", TaskRun(task1) , 1); 
	TaskDestroy(task1);

}

void Test2Tasks()
{
	task_t *task1 = NULL;
	task_t *task2 = NULL;
	size_t interval = 5;
	char *str = "hello world";
	
	task1 = TaskCreate(PrintVal, DestroyEmpty, interval, (void *)str);
	task2 = TaskCreate(PrintVal, DestroyEmpty, interval, (void *)str);
	TEST("is match + get uid  ", (TaskIsMatch(task1, TaskGetUid(task1))) , 1); 
	TEST("is before  ", TaskIsBefore(task1, task2) , 1); 
	sleep(5);
	TaskUpdateTimeToRun(task1);
	TEST("is before  ", TaskIsBefore(task1, task2) , 0); 
	
	TaskDestroy(task1);
	TaskDestroy(task2);

}

/*
task_t *task1 = NULL;
task_t *task1_dup = NULL;
task_t *task2 = NULL;

time_t time_to_run = 0;
ilrd_uid_t uid = NULL;
size_t interval = 0;

task_t *TaskCreate(task_func_t task_func, task_destroy_func_t destroy_func, size_t interval, void *param);
void TaskDestroy(task_t *task);
time_t TaskGetTimeToRun(task_t *task);
task_status_t TaskRun(task_t *task);
int TaskIsMatch(const task_t *task, ilrd_uid_t task_id); 
ilrd_uid_t TaskGetUid(const task_t *task);
void TaskUpdateTimeToRun(task_t *task);
int TaskIsBefore(const void *task1, const void *task2);

*/
/*****************************************************************************/
