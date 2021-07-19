#include <unistd.h>   /* execlp */
#include <stdlib.h>  /* system */
#include <sys/wait.h>   /* waitpid */
#include <stdio.h>   /* printf */
#include <string.h>

int main(int argc, char *argv[])
{
    char buff[100] = {0};
    size_t len = 0;
    int stat = 0;

    if (argc < 2)
    {
        printf("\nNot enough arguments");
        return (1);
    }
    printf("%s\n", argv[1]);
    sleep(2);

    len = strlen(argv[1]);
    strcpy(buff, argv[1]);
    buff[len] = ' ';
    strcpy(buff + len + 1, argv[2]);
    buff[len + 1 + strlen(argv[2])] = '\0';
    
    while (1)
    {
        stat = system(buff);
        printf("\ncritic process exit with %d status\n", stat);
    }

    return (0);
}