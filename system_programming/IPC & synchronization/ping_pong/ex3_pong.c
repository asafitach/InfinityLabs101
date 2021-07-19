
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/signalfd.h>


void SignalHendler(int pid)
{
    write(STDOUT_FILENO, "Pong\n", 6);
}


int main(int argc, char *argv[])
{
    pid_t ping_pid = atoi(argv[1]);
    struct sigaction child;
    memset(&child, 0, sizeof(struct sigaction));

    child.sa_handler = SignalHendler;



        sigaction(SIGUSR2, &child, NULL);
    while (1)
    {
        kill(ping_pid, SIGUSR1);
        pause();
    }

    return (0);
}