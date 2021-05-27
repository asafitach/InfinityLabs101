#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "scheduler.h"
#include "watch_dog.h"
#include "watch_dog_lib.h"


pid_t wd_proc_pid = -1;

void SetFlag(int pid);

void *StartUpThread(void *param);

void *WdStartUp(void *param)
{
    pthread_t tr;
    
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
    struct sigaction watch_dog_thread;
    int sched_exit_stat = 0;
    sem_t *sem = NULL;
    
/*     watch_dog_thread.sa_handler = SetFlag;
    sigaction(SIGUSR1, &watch_dog_thread, NULL);
 */
    
    while (NULL == scheduler)
    {
        scheduler = InitScheduler(wd_proc_pid);
    }
    sem_unlink("/watch_dog");

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
    pthread_t thread = 0;
    struct sigaction ignor;

    ignor.sa_handler = Empty;
    sigaction(SIGUSR1, &ignor, NULL);

    while (0 != pthread_create(&thread, NULL, WdStartUp,NULL))
    {
        ;/* busy wait */
    }

    pthread_join(thread, NULL);
    

    return (0);
}


void WatchDogStop()
{
    kill(getpid(), SIGQUIT);
    kill(wd_proc_pid, SIGQUIT);
}