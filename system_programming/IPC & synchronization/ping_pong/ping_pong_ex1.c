/* #define _POSIX_SOURCE
 */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/signalfd.h>


void SignalHendler(int pid)
{
    write(STDOUT_FILENO, "Ping\n", 6);
}

void SignalHendler2(int pid)
{
    write(STDOUT_FILENO, "Pong\n", 6);
}

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    struct sigaction child;
    struct sigaction parrent;

    child.sa_handler = SignalHendler;
    parrent.sa_handler = SignalHendler2;

    sigaction(SIGUSR1, &child, NULL);
    sigaction(SIGUSR2, &parrent, NULL);
    while (1)
    {
        if (0 == pid)
        {
            kill(getppid(), SIGUSR2);
            pause();
        }
        else
        {
            pause();
            kill(pid, SIGUSR1);
        }
    }

return 0;
}
  