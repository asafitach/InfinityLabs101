

#include "task.h"



task_func_t SendSignal(void *param)
{
    kill();
    return(0);
}

task_func_t CheckFlag(void *param)
{
    return(0);
}

