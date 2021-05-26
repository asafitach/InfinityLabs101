#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <semaphore.h>
#include <fcntl.h>
#include "scheduler.h"
#include "task.h"
#include "uid.h"
#include "watch_dog.h"
#include"watch_dog_lib.h"


pid_t wd_proc_pid = -1;
scheduler_t *scheduler = NULL;

void *WdStartUp(void *param)
{
    pid_t user_pid = getpid();

    while (-1 == wd_proc_pid)
    {
        wd_proc_pid = fork();
    }

    if (0 == wd_proc_pid)
    {
        while (0 != execve("./watch_dog.out", (char **)param, NULL))
        {
            ;
        }
    }

    return (StartUpThread(param));
}


void *StartUpThread(void *param)
{
    struct sigaction watch_dog_thread;
    int sched_exit_stat = 0;
    sem_t *sem = NULL;
    
    watch_dog_thread.sa_handler = SetFlag;
    sigaction(SIGUSR1, &watch_dog_thread, NULL);

    
    while (NULL == scheduler)
    {
        scheduler = InitSceduler(wd_proc_pid);
    }

    sem = sem_open("/watch_dog", O_CREAT, 0664, 0);
    sem_wait(sem);
    
    sched_exit_stat = WdSchedRun();

    SchedulerDestroy(scheduler);

    if (sched_exit_stat != 2)
    {
        return (WdStartUp(param));
    }
    
    return (NULL);
}

void SetFlag(int pid)
{
    __sync_val_compare_and_swap(&flag, 0, 1);
}

int WatchDogStart(char *argv[])
{
    pthread_t thread = 0;

    while (0 != pthread_create(&thread, NULL, WdStartUp,NULL))
    {
        ;/* busy wait */
    }

    return (0);
}


void WatchDogStop()
{

}