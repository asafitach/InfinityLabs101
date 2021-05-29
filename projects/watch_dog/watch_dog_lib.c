#define _POSIX_SOURCE

/* #define _POSIX_C_SOURCE 199309L */

#include <signal.h>   /* kill */
#include <pthread.h>   /* comment */
#include <stdio.h>
#include "task.h"
#include "watch_dog_lib.h"

static atomic_int g_flag = 0;



scheduler_t * InitScheduler(pid_t pid_to_monitor)
{
    scheduler_t *scheduler = NULL;
    ilrd_uid_t send_signal_task;
    ilrd_uid_t check_flag_task;
    struct sigaction new_sig_quit = {0};
    struct sigaction change_flag = {0};

    scheduler = SchedulerCreate();
    if (NULL == scheduler)
    {
        return (NULL);
    }
    

    new_sig_quit.sa_handler = EndScheduler;
    sigaction(SIGUSR2, &new_sig_quit, NULL);

    change_flag.sa_handler = CangeFlag;
    send_signal_task = SchedulerAddTask(scheduler, ReImplementSigaction, CleanTask, 1, (void *)&change_flag);
    if (1 == UidIsSame(send_signal_task, GetBadUid()))
    {
        SchedulerDestroy(scheduler);
        return (NULL);
    }

    send_signal_task = SchedulerAddTask(scheduler, SendSignal, CleanTask, 1, *(void **)&pid_to_monitor);
    if (1 == UidIsSame(send_signal_task, GetBadUid()))
    {
        SchedulerDestroy(scheduler);
        return (NULL);
    }
    
    check_flag_task = SchedulerAddTask(scheduler, CheckFlag, CleanTask, 1, (void *)scheduler);
    if (1 == UidIsSame(check_flag_task, GetBadUid()))
    {
        SchedulerDestroy(scheduler);
        return (NULL);
    }

    

    return (scheduler);
}

int SendSignal(void *param)
{
    printf("hello from sender pid num: %d\n", *(pid_t *)&param);
    
    kill(*(pid_t *)&param, SIGUSR1);

    return(0);
}

int ReImplementSigaction(void *handler)
{
    sigaction(SIGUSR1, (struct sigaction *)handler, NULL);

    return (1);
}

int CheckFlag(void *param)
{
/*     if (0 == __sync_val_compare_and_swap(&g_flag, 1, 0))
 */    if (0 == g_flag)
    {
        SchedulerStop((scheduler_t *)param);
    }

    if (2 == g_flag)
    {
        SchedulerClear((scheduler_t *)param);
        
    }

    printf("hello from reciver\n");

    return(0);
}

void CleanTask(ilrd_uid_t uid, void*param)
{
    uid = uid;
    param = param;
}

void CangeFlag(int pid)
{
    pid = pid;
    __sync_bool_compare_and_swap(&g_flag, 0 , 1);
}


void EndScheduler(int pid)
{
    pid = pid;
    g_flag = 2;
}




