#include <unistd.h>   /* execlp */
#include <stdlib.h>   /* comment */
#include <stdio.h>   /* printf */

int main(int argc, char *argv[])
{
    char *a = "a";

    if (argc < 2)
    {
        printf("\nNot enough arguments");

        return (1);
    }

    switch (*argv[1])
    {
        case '1':
        
            printf("\nhello from child\n");
        
            sleep(3);

            break;
        
        case '2':

            sleep(3);

            *a = 'b';

            break;
        case '3':
        
            sleep(3);

            exit(1);

            break;
    }

    return (0);
}
