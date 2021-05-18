#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/signalfd.h>
#include <string.h>

void SignalHendler2(int pid)
{
    sleep(2);
    write(STDOUT_FILENO, "Pong\n", 6);
}

int main(int argc, char *argv[])
{
    pid_t pid = 0;
    struct sigaction parrent;
    memset(&parrent, 0, sizeof(struct sigaction));

    parrent.sa_handler = SignalHendler2;

    sigaction(SIGUSR2, &parrent, NULL);

    pid = fork();

    if (pid == 0)
    {
        printf("\nparent is loading child process:\n");
        printf("status of loading: %d\n", execve("./ex2_pong.out", argv, NULL));
        sleep(1);
    } 
    else if (0 > pid)
    {
        printf("\nFork failed\n");
        return (1);
    }
    else
    {
        printf("I'm the child\n\n");
    }

    while (1)
    {
        pause();
        kill(pid, SIGUSR1);
    }

return 0;
}
  