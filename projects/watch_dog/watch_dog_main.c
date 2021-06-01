#include "watch_dog_lib.h"

pid_t user_proc_pid;
void Revive(char *name_of_exe, char *argv[]);

int main(int argc, char *argv[])
{
    int scheduler_exit_status = 0;
    scheduler_t *scheduler = NULL;
    sem_t *sem = NULL;
/*     
    struct sigaction change_flag = {0};
    struct sigaction end_scheduler = {0}; */

/* 
    end_scheduler.sa_handler = EndScheduler;
    sigaction(SIGUSR2, &end_scheduler, NULL);

    change_flag.sa_handler = CangeFlag;
    sigaction(SIGUSR1, &change_flag, NULL); */

    user_proc_pid = getppid();
    if ((sem = sem_open("/watch_dog", O_CREAT, 0644, 0)) == SEM_FAILED)
    {
        #ifndef NDEBUG
        PrintError(SEM);
        #endif

        return (1);
    }
/* 
    if (NULL != argv)
    {
        printf("argc = %d\n", argc);
        while (NULL != *argv)
        {
            printf("%s\n", *argv);
            ++argv;
        }
    }
    argv -= argc; */
    argc = argc;
    argv = argv;

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


