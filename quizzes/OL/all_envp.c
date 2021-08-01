#include <stdio.h>

int main(int argc,char *argv[], char *envp[])
{
    while (NULL != *envp)
    {
        printf("%s\n", *envp);
        envp++;
    }

    return (0);
}