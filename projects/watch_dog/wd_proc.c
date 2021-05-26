#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include "scheduler.h"
#include "task.h"
#include "uid.h"
#include "watch_dog.h"
#include "watch_dog_lib.h"


pid_t user_proc_pid;

int main(int argc, char *argv[])
{
    char * user_proc_name = "./a.out";
    struct sigaction change_flag;
/*     struct sigaction new_sig_quit;
 */    int sched_exit_stat = 0;
    scheduler_t *scheduler = NULL;
    sem_t *sem = NULL;
    
    user_proc_pid = getppid();
    sem = sem_open("/watch_dog", O_CREAT, 0664, 0);


    while (NULL == scheduler)
    {
        scheduler = InitSceduler(user_proc_pid);
    }

    sem_post(sem);

    sched_exit_stat = SchedulerRun(scheduler);
/* 
    if (sched_exit_stat == 0)
    {
        kill(getpid(), SIGQUIT);
    }
 */

    Revive(user_proc_name, argv);

    kill(getpid(), SIGQUIT);

    return (0);
}

void Revive(char *name_of_exe, char *argv[])
{
    pid_t new_user_proc = 0;

    new_user_proc = fork();

    while (-1 == new_user_proc)
    {
        new_user_proc = fork();
    }

    if (0 == new_user_proc)
    {
        execve("./a.out", argv, NULL);
    }

    kill(getpid(), SIGQUIT);
}
