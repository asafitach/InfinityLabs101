#include <unistd.h>   /* execlp */
#include <sys/wait.h>   /* waitpid */
#include <stdio.h>   /* printf */

int main(int argc, char *argv[])
{
    int wait_status = 0;
    pid_t child_pid = 0;

    if (argc < 3)
    {
        printf("\nNot enough arguments");
        return (1);
    }
    
    while (++count)
    {
        child_pid = fork();

        if (child_pid == 0)
        {
            printf("\nparent is loading child process:\n");
            execve(argv[1], argv, NULL);

        } else if (child_pid > 0)
        {
            waitpid(child_pid, &wait_status, 0);
            printf("\n%d\n", wait_status);
        }
        else
        {
            printf("\nFork failed\n");
            return (1);
        }   
    }

    return (0);
}