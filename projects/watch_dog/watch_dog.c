#include "watch_dog_lib.h"
#include "watch_dog.h"

static pid_t g_wd_proc_pid = -1;



int WatchDogStart(char *argv[])
{
    struct sigaction ignor = {0};
    char create[] = "1";

/*     ignor.sa_handler = EmptyStub;
    sigaction(SIGUSR1, &ignor, NULL); */

    if (NULL == WdStartUp(argv, FIRST_CALL))
    {
        return (1);
    }
    ChangeEnvironmentVar(create);


    return (0);
}

void WatchDogStop(void)
{
    char stop_wd[] = "0";
    ChangeEnvironmentVar(stop_wd);

    kill(getpid(), SIGUSR2);

    kill(g_wd_proc_pid, SIGUSR2);
}

void *WdStartUp(void *param, int caller)
{
    pthread_t wd_thread = 0;
/*     struct sigaction change_flag = {0};
    struct sigaction end_scheduler = {0}; */
    sem_t *sem = NULL;

    sem_unlink("/watch_dog");

/*     end_scheduler.sa_handler = EndScheduler;
    sigaction(SIGUSR2, &end_scheduler, NULL);

    change_flag.sa_handler = CangeFlag;
    sigaction(SIGUSR1, &change_flag, NULL); */

    g_wd_proc_pid = -1;

    g_wd_proc_pid = fork();

    if (-1 == g_wd_proc_pid)
    {
        #ifndef NDEBUG
        PrintError(FORK);
        #endif

        return (NULL);
    }

    if (WD_PROCESS == caller)
    {
        if (0 == g_wd_proc_pid)
        {
            if (-1 == execve("./a.out", (char **)param, NULL))
            {
                #ifndef NDEBUG
                PrintError(EXEC);
                #endif
                return (NULL);
            }
        }
        else
        {
            kill(getpid(), SIGKILL);
        }
    }

    /* caller == USER_PROCESS / FIRST_CALL*/
    if (0 == g_wd_proc_pid)
    {
        if (-1 == execve("./watch_dog_main.out", (char **)param, NULL))
        {
            #ifndef NDEBUG
            PrintError(EXEC);
            #endif
            return (NULL);
        }
    }


    if (FIRST_CALL == caller && 0 != pthread_create(&wd_thread, NULL, StartUpThread, param))
    {
        #ifndef NDEBUG
        PrintError(THREAD);
        #endif
        return (NULL);
    }


    return (param);
}

void *StartUpThread(void *param)
{
    scheduler_t *scheduler = NULL;
    int scheduler_exit_status = 0;
    sem_t *sem = NULL;
    
    scheduler = InitScheduler(g_wd_proc_pid);
    if (NULL == scheduler)
    {
        #ifndef NDEBUG
        PrintError(SCHEDULER);
        #endif

        return (NULL);
    }

    if ((sem = sem_open("/watch_dog", O_CREAT, 0644, 0)) == SEM_FAILED)
    {
        #ifndef NDEBUG
        PrintError(SEM);
        #endif

        return (NULL);
    }

    sem_wait(sem);
    while (1)
    {
    
        scheduler_exit_status = SchedulerRun(scheduler);

        SchedulerDestroy(scheduler);

        if (STOPPED == scheduler_exit_status)
        {
            WdStartUp(param, USER_PROCESS);
        }

        else
        {
            break;
        }
    }
    
    return (NULL);
}

void EmptyStub(int param)
{
    param = param;
    return;
}


void ChangeEnvironmentVar(char *change_to)
{
    printf("Setting env var WATCHDOG to %s\n", change_to);

    if (0 != setenv("WATCHDOG", change_to, 1))
    {
        printf("setenv error\n");
    }
    printf("Checking env var WATCHDOG is: %s\n", getenv("WATCHDOG"));
}