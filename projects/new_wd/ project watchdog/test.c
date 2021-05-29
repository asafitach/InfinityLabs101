#define _POSIX_SOURCE

#define _POSIX_C_SOURCE 199309L

/* #define _POSIX_C_SOURCE 199309L */

#include <stdio.h>   /* printf */
#include <unistd.h>   /* comment */
#include <signal.h>   /* kill */
#include <stdatomic.h>   /* atomic_t */
#include <sys/types.h>   /* pid_t */
#include <bits/sigaction.h>

#include "scheduler.h"


void SignalActionFunction(int sig_num, siginfo_t *siginfo, void *flag);
int SendSignal(void *param);
void SendSignalDestroy(ilrd_uid_t uid, void*param);
int CheckFlag(void *param);
void CheckFlagDestroy(ilrd_uid_t uid, void*param);
scheduler_t * InitScheduler(pid_t pid_to_send, char *exec);
atomic_int flag = 0;

int g_counter = 0;


int main()
{
    pid_t pid_to_send = 0;

    char *exec = "a.out";

    scheduler_t *scheduler = InitScheduler(pid_to_send, exec);
    if (NULL != scheduler)
    {
      printf("\nSUCCESS\n");
    }
    else
    {
      printf("\nFAILURE\n");
    }

    return (0);
}


scheduler_t * InitScheduler(pid_t pid_to_send, char *exec)
{
    ilrd_uid_t send_signal_task;
    ilrd_uid_t check_flag_task;

    scheduler_t *scheduler = SchedulerCreate();
    if (NULL == scheduler)
    {
        return (NULL);
    }

    send_signal_task = SchedulerAddTask(scheduler, SendSignal, SendSignalDestroy, 1, *(void **)&pid_to_send);
    if (1 == UidIsSame(send_signal_task, GetBadUid()))
    {
        SchedulerDestroy(scheduler);
        return (NULL);
    }
    
    check_flag_task = SchedulerAddTask(scheduler, CheckFlag, CheckFlagDestroy, 1, *(void **)&pid_to_send);
    if (1 == UidIsSame(send_signal_task, GetBadUid()))
    {
        SchedulerDestroy(scheduler);
        return (NULL);
    }

    return (scheduler);
}

int SendSignal(void *param)
{
    kill(*(pid_t *)&param, SIGUSR1);

    return(0);
}

void SendSignalDestroy(ilrd_uid_t uid, void*param)
{
    uid = uid;
    param = param;
}

int CheckFlag(void *param)
{
    if (0 == __sync_val_compare_and_swap(&flag, 1, 0))
    {
        /* return (Revive((char *)param)); */
        return (1);
    }

    return(0);
}

void CheckFlagDestroy(ilrd_uid_t uid, void*param)
{
    uid = uid;
    param = param;
}

void SignalActionFunction(int sig_num, siginfo_t *siginfo, void *flag)
{
    __sync_val_compare_and_swap(&flag, 0, 1);

    return ;
}


