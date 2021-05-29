#ifndef __WATCH_DOG_LIB_H__
#define __WATCH_DOG_LIB_H__

#define _DEFAULT_SOURCE
#define _POSIX_SOURCE


#include <fcntl.h> /* O_CREATE */
#include <pthread.h> /* pthread_create */
#include <semaphore.h> /* sem_open, sem_unlink, sem_post, sem_wait */
#include <stdatomic.h>   /* atomic_t */
#include <signal.h> /* kill, sigaction */
#include <stdlib.h>    /* setenv */
#include <unistd.h> /* sleep */
#include <sys/types.h>
#include "scheduler.h"
#include "task.h"
#include "uid.h"

#ifndef NDEBUG

#include <stdio.h>

#endif


#define USER_PROCESS 1
#define WD_PROCESS 0

/* initiat watch dog function */
void EmptyStub(int param);

void *WdStartUp(void *param, int caller);

void *StartUpThread(void *param);

void ChangeEnvironmentVar(char *change_to);

/* initiat scheduler */
scheduler_t *InitScheduler(pid_t pid_to_monitor);

/* scheduler tasks */
int SendSignal(void *param);

int CheckFlag(void *param);

void CleanTaskStub(ilrd_uid_t uid, void *param);

/* signal handler */

void CangeFlag(int pid);

void EndScheduler(int pid);

/* debug section */
#ifndef NDEBUG

typedef enum error
{
    SCHEDULER = 0,
    TASK = 1,
    SEM = 2,
    FORK = 3,
    EXEC = 4,
    THREAD = 5 
} error_t;

void PrintError(int error);

#endif


#endif /* __WATCH_DOG_LIB_H__ */

