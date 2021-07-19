#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/signalfd.h>

siginfo_t sig_info_g;

void SignalHendler2(int pid, siginfo_t *siginfo, void *param)
{
    sig_info_g = *siginfo;

    write(STDOUT_FILENO, "Ping\n", 6);
}


int main(int argc, char *argv[])
{
    struct sigaction ping;

    ping.sa_sigaction = SignalHendler2;
    ping.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &ping, NULL);
    
    while (1)
    {
        pause();
        kill(sig_info_g.si_pid, SIGUSR2);
    }

    return 0;
}
  