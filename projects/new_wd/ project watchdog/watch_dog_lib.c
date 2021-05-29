#include "watch_dog_lib.h"

#define SEND_SIG_INTERVAL 1
#define CHECK_FLAG_INTERVAL 3

typedef enum flag_status
{
    DEAD = 0,
    ALIVE = 1,
    USER_STOPED = 2
} flag_status_t;

static atomic_int g_flag = DEAD;


scheduler_t * InitScheduler(pid_t pid_to_monitor)
{
    ilrd_uid_t send_signal_task;
    ilrd_uid_t check_flag_task;

    scheduler_t *scheduler = SchedulerCreate();
    if (NULL == scheduler)
    {
        #ifndef NDEBUG
        PrintError(SCHEDULER);
        #endif
        
        return (NULL);
    }

    send_signal_task = SchedulerAddTask(scheduler, SendSignal, CleanTaskStub, SEND_SIG_INTERVAL, *(void **)&pid_to_monitor);
    if (1 == UidIsSame(send_signal_task, GetBadUid()))
    {
        #ifndef NDEBUG
        PrintError(TASK);
        #endif

        SchedulerDestroy(scheduler);
        return (NULL);
    }
    
    check_flag_task = SchedulerAddTask(scheduler, CheckFlag, CleanTaskStub, CHECK_FLAG_INTERVAL, (void *)scheduler);
    if (1 == UidIsSame(check_flag_task, GetBadUid()))
    {
        #ifndef NDEBUG
        PrintError(TASK);
        #endif

        SchedulerDestroy(scheduler);
        return (NULL);
    }


    return (scheduler);
}

int SendSignal(void *param)
{
    kill(*(pid_t *)&param, SIGUSR1);

    #ifndef NDEBUG
    printf("send signal from pid: %d\n", getpid());
    #endif

    return(0);
}


int CheckFlag(void *param)
{
    switch (g_flag)
    {
        case DEAD:
            SchedulerStop((scheduler_t *)param);
            break;

        case USER_STOPED:
            SchedulerClear((scheduler_t *)param);
            break;

        case ALIVE:
            g_flag = DEAD;
            break;
    }

    #ifndef NDEBUG
    printf("check flag from pid: %d\n", getpid());
    #endif

    return(0);
}

void CleanTaskStub(ilrd_uid_t uid, void*param)
{
    uid = uid;
    param = param;
}

void CangeFlag(int pid)
{
    pid = pid;
    __sync_bool_compare_and_swap(&g_flag, DEAD , ALIVE);
}

void EndScheduler(int pid)
{
    pid = pid;
    g_flag = USER_STOPED;
}

#ifndef NDEBUG

void PrintError(int error)
{
    switch (error)
    {
        case SCHEDULER:
            printf("\nSchedulerCreate failed.\n");
            break;
        case TASK:
            printf("\nSchedulerAddTask failed.\n");
            break;
        case SEM:
            printf("\nsem_open failed.\n");
            break;
        case FORK:
            printf("\nfork failed.\n");
            break;
        case EXEC:
            printf("\nexec failed.\n");
            break;
        case THREAD:
            printf("\npthread_create failed.\n");
            break;
    }

    return ;
}

#endif





