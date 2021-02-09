#include <stdio.h>	/* printf */
#include "ex4.h"	/* HelloWorld */

/*print hello world by using hex chars*/
void HelloWorld()
{
    char hello_world[] = {0x22, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 
	0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21, 0x22};
    int n = 14;
    int i = 0;
    
    for (i = 0; i < n; i++)
    {
        printf("%c",hello_world[i]);
    }
}


