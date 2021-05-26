#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "scheduler.h"
#include "task.h"
#include "uid.h"
#include "watch_dog.h"
#include"watch_dog_lib.h"

void *WdStartUp(void *param)
{
    pid_t user_pid = getpid();
    pid_t wd_proc_pid = -1;

    while (-1 == wd_proc_pid)
    {
        wd_proc_pid = fork();
    }

    if (0 == wd_proc_pid)
    {
        while (0 != execl("./watch_dog.out", *(char **)&user_pid))
        {
            ;
        }
    }

    StartUpThread("./a.out", wd_proc_pid);

    return (NULL);
}

int WatchDogStart()
{
    pthread_t thread = 0;

    while (0 != pthread_create(&thread, NULL, WdStartUp,NULL))
    {
        ;
    }

    return (0);
}

int main()
{
    pthread_t thread = 0;

    while (0 != pthread_create(&thread, NULL, WdStartUp,NULL))
    {
        ;
    }




}