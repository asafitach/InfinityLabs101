#include <unistd.h>   /* execlp */
#include <stdlib.h>   /* comment */
#include <stdio.h>   /* printf */
#include "watch_dog.h"

int main(int argc, char *argv[])
{
    char *a = "a";
    long sa = 1;

    printf("critic begin\n\n");
    WatchDogStart();

    while (sa< 9999999999999)
    {
        sa *=2;
    }

    printf("%ld", sa);
    sleep(4);
/*     WatchDogStop();
 */      

/*             *a = 'b';
 */


    return (0);
}
