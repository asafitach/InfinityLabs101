
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/signalfd.h>
#include <string.h>


void SignalHendler(int pid)
{
    sleep(2);
    write(STDOUT_FILENO, "Ping\n", 6);
}


int main(int argc, char *argv[])
{
    pid_t ppid = getppid();
    struct sigaction child;
    memset(&child, 0, sizeof(struct sigaction));
    

    child.sa_handler = SignalHendler;


    while (1)
    {
        sigaction(SIGUSR1, &child, NULL);
        kill(ppid, SIGUSR2);
        pause();
    }

    return (0);
}