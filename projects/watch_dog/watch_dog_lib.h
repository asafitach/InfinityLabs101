#ifndef __WATCH_DOG_LIB_H__
#define __WATCH_DOG_LIB_H__

#include <stddef.h>  /* size_t */
#include <stdatomic.h>
#include "scheduler.h"
#include "uid.h"



atomic_int g_flag = 0;

/* initiat scheduler */

scheduler_t * InitScheduler(pid_t pid_to_monitor);

/* scheduler tasks */

int SendSignal(void *param);

int CheckFlag(void *param);

void CleanTask(ilrd_uid_t uid, void*param);

/* signal handler */

void CangeFlag(int pid);




#endif /* __WATCH_DOG_LIB_H__ */
