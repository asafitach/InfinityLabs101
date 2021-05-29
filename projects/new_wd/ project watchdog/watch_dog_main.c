#include "watch_dog_lib.h"

pid_t user_proc_pid;
void Revive(char *name_of_exe, char *argv[]);

int main(int argc, char *argv[])
{
    int scheduler_exit_status = 0;
    scheduler_t *scheduler = NULL;
    sem_t *sem = NULL;
    
    user_proc_pid = getppid();
    if ((sem = sem_open("/watch_dog", O_CREAT, 0644, 0)) == SEM_FAILED)
    {
        #ifndef NDEBUG
        PrintError(SEM);
        #endif

        return (1);
    }

    scheduler = InitScheduler(user_proc_pid);
    if (NULL == scheduler)
    {
        #ifndef NDEBUG
        PrintError(SCHEDULER);
        #endif

        return (1);
    }

    #ifndef NDEBUG
    printf("watch dog begin\n");
    #endif

    sem_post(sem);

    scheduler_exit_status = SchedulerRun(scheduler);

    if (scheduler_exit_status == 2)
    {
        WdStartUp(argv, WD_PROCESS);
    }

    kill(getpid(), SIGKILL);

    return (0);
}

void Revive(char *name_of_exe, char *argv[])
{
    pid_t new_user_proc = 0;

    new_user_proc = fork();

    if (-1 == new_user_proc)
    {
        #ifndef NDEBUG
        PrintError(FORK);
        #endif

        return ;
    }

    if (0 == new_user_proc)
    {
        #ifndef NDEBUG
        printf("now a.out begin again\n");
        #endif

        if ( 0 != execve(name_of_exe, argv, NULL))
        {
            #ifndef NDEBUG
            PrintError(EXEC);
            #endif

            return ;
        }
    }

    kill(getpid(), SIGQUIT);
}
