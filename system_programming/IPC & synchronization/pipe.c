#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define _GNU_SOURCE 


#define BUFF_SIZE 100

int main()
{
    pid_t child = 0;
    int parrent_write[2];
    int child_write[2];
    char buf[BUFF_SIZE] = {0};
    ssize_t nbytes;


    if (-1 == pipe(child_write) || -1 == pipe(parrent_write)) 
    {
        perror("failed to create pipe\n");
    }

    child = fork();
    printf("%d\n", getpid());
    
    switch (child) 
    {
        case -1: 
            perror("failed to create child process\n");
            break;

        case 0:
            close(parrent_write[1]);
            close(child_write[0]);
            for (int i = 0; i < 5; ++i)
            {
                sleep(1);
                nbytes = read(parrent_write[0], buf, BUFF_SIZE);

                printf("%s", buf);

                write(child_write[1], "Hello from child\n\0", 19);
            }
                close(child_write[1]);
                close(parrent_write[0]);
            break;

        default:
                close(parrent_write[0]);
                close(child_write[1]);
            for (int i = 0; i < 5; ++i)
            {
                sleep(1);

                write(parrent_write[1], "Hello from pap's\n\0", 19);

                nbytes = read(child_write[0], buf, BUFF_SIZE);

                printf("%s", buf);
            }
                close(child_write[0]);
                close(parrent_write[1]);

    }

    return 0;
}