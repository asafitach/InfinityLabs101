#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include "scheduler.h"
#include "watch_dog.h"
#include "watch_dog_lib.h"


pid_t g_user_proc_pid;

void Revive(char *name_of_exe, char *argv[]);
void EndScheduler(int pid);
void *EmptySchrduler(void *param);


int main(int argc, char *argv[])
{
    scheduler_t *scheduler = NULL;
    char * user_proc_name = "./a.out";
    int sched_exit_stat = 0;
    sem_t *sem = NULL;
    
    g_user_proc_pid = getppid();
    sem = sem_open("/watch_dog", O_CREAT, 0664, 0);



    while (NULL == scheduler)
    {
        scheduler = InitScheduler(g_user_proc_pid);
    }

    printf("watch dog begin\n");
    sem_post(sem);

    sched_exit_stat = SchedulerRun(scheduler);

    if (sched_exit_stat == 0)
    {
        SchedulerDestroy(scheduler);
    }

    else
    {
        Revive(user_proc_name, argv);
    }

    return (0);
}

void Revive(char *name_of_exe, char *argv[])
{
    pid_t new_user_proc = 0;

    new_user_proc = fork();

    while (-1 == new_user_proc)
    {
        new_user_proc = fork();
    }

    if (0 == new_user_proc)
    {
        printf("now a.out begin again\n");
        execve("./a.out", argv, NULL);
    }

    kill(getpid(), SIGQUIT);
}
