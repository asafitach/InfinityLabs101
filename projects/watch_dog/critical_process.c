#include <unistd.h>   /* sleep */
#include <stdio.h>   /* printf */
#include <time.h>
#include "watch_dog.h"

int main(int argc, char *argv[])
{
    char *a = "a";
    long sa = 1;
    time_t remain = 10;

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

    printf("critic begin it's pid is: %d\n\n", getpid());


    sleep(3);
    while (sa< 9999999999999)
    {
        sa *=2;
    }
    WatchDogStart();

    while (remain)
    {
        remain = sleep(remain);
    }

    printf("%ld", sa);
    sleep(2);
/*     WatchDogStop();
 */

    return (0);
}
/*להכניס את pthread_join */
/* insert more checks */