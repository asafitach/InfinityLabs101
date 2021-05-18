#include <stdio.h>
#include <stddef.h>

int main(int argc, char *argv[], char *envp[])
{
    while (NULL != envp)
    {
        printf("%s\n", *envp);
        ++envp;
    }

    return 0;
}