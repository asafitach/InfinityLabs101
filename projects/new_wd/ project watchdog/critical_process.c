#include <unistd.h>   /* sleep */
#include <stdio.h>   /* printf */
#include "watch_dog.h"

int main(int argc, char *argv[])
{
    char *a = "a";
    long sa = 1;

    if (NULL != argv)
    {
        printf("argc = %d\n", argc);
        while (NULL != *argv)
        {
            printf("%s\n", *argv);
            ++argv;
        }
    }
    argv -= argc;

    printf("critic begin\n\n");
    WatchDogStart();

    sleep(3);

    while (sa< 9999999999999)
    {
        sa *=2;
    }

    printf("%ld", sa);
    sleep(2);
    /* WatchDogStop(); */


    return (0);
}
