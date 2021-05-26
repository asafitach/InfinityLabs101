#define _POSIX_SOURCE

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>        /* printf */  
#include <signal.h>       /* sigaction */
#include <bits/sigaction.h>
#include <stdatomic.h>   /* comment */

void SignalActionFunction(int sig_num, siginfo_t *siginfo, void *flag);

int main()
{  
    atomic_int flag = 0;

    siginfo_t sig_info_g;

    struct sigaction signal_action; 

    signal_action.sa_sigaction = SignalActionFunction;

    signal_action.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &signal_action, &flag);
    
    return 0;
}

void SignalActionFunction(int sig_num, siginfo_t *siginfo, void *flag)
{
    __sync_val_compare_and_swap(&flag, 0, 1);

    return;
}








