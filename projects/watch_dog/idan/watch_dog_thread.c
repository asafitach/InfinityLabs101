#define _POSIX_SOURCE

/* #define _POSIX_C_SOURCE 199309L */

#include <signal.h>   /* kill */
#include <stdatomic.h>   /* atomic_t */
#include <pthread.h>   /* comment */
#include "scheduler.h"
#include "task.h"
#include "uid.h"
#include "watch_dog_lib.h"


scheduler_t * InitScheduler(pid_t pid_to_monitor)
{
    ilrd_uid_t send_signal_task;
    ilrd_uid_t check_flag_task;
    struct sigaction change_flag;

    scheduler_t *scheduler = SchedulerCreate();
    if (NULL == scheduler)
    {
        return (NULL);
    }

    send_signal_task = SchedulerAddTask(scheduler, SendSignal, CleanTask, 1, *(void **)&pid_to_monitor);
    if (1 == UidIsSame(send_signal_task, GetBadUid()))
    {
        SchedulerDestroy(scheduler);
        return (NULL);
    }
    
    check_flag_task = SchedulerAddTask(scheduler, CheckFlag, CleanTask, 5, (void *)scheduler);
    if (1 == UidIsSame(send_signal_task, GetBadUid()))
    {
        SchedulerDestroy(scheduler);
        return (NULL);
    }

    /* happend in init sched */
    change_flag.sa_handler = CangeFlag;
    sigaction(SIGUSR1, &change_flag, NULL);

    return (scheduler);
}

int SendSignal(void *param)
{
    kill(*(pid_t *)&param, SIGUSR1);

    return(0);
}

int CheckFlag(void *param)
{
/*     if (0 == __sync_val_compare_and_swap(&g_flag, 1, 0))
 */    if (0 == g_flag)
    {
        SchedulerStop((scheduler_t *)param);
    }

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
    g_flag = 1;
}






