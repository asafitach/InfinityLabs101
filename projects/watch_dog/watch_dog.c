#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "scheduler.h"
#include "watch_dog.h"
#include "watch_dog_lib.h"


static pid_t wd_proc_pid = -1;

void SetFlag(int pid);

void *StartUpThread(void *param);

void *WdStartUp(void *param)
{
    pthread_t tr;

    sem_unlink("/watch_dog");
    
    pthread_create(&tr, NULL, StartUpThread, param);

    while (-1 == wd_proc_pid)
    {
        wd_proc_pid = fork();
    }

    if (0 == wd_proc_pid)
    {
        while (0 != execve("./watch_dog_main.out", (char **)param, NULL))
        {
            ;
        }
    }

    return ((param));
}


void *StartUpThread(void *param)
{
    scheduler_t *scheduler = NULL;
    int sched_exit_stat = 0;
    sem_t *sem = NULL;
    


    
    while (NULL == scheduler)
    {
        scheduler = InitScheduler(wd_proc_pid);
    }

    sem = sem_open("/watch_dog", O_CREAT, 0664, 0);
    sem_wait(sem);
    
    sched_exit_stat = SchedulerRun(scheduler);

    SchedulerDestroy(scheduler);

    if (sched_exit_stat != 2)
    {
        return (WdStartUp(param));
    }
    
    return (NULL);
}

/* void SetFlag(int pid)
{
    __sync_val_compare_and_swap(&flag, 0, 1);
}
 */

void Empty(int param)
{
    param = param;

    return;
}


int WatchDogStart(char *argv[])
{
    struct sigaction ignor = {0};

    ignor.sa_handler = Empty;
    sigaction(SIGUSR1, &ignor, NULL);

    WdStartUp(argv);
    

    return (0);
}


void WatchDogStop()
{
    kill(getpid(), SIGUSR2);
    kill(wd_proc_pid, SIGUSR2);
}