#include <stdio.h>
#include <ctype.h>



int Atoi(const char *input)
{
    int num = 0;
    int flag = 1;

    if ('-' == *input)
    {
        flag = -1;
        ++input;
    }

    while ('\0' != *input && ' ' != *input)
    {
        if (1 == isdigit(*input))
        {
            num *= 10;
            num += (*input - '0');
        }
        else
        {
            return (0);
        }
        ++input;
    }

    return (num * flag);
}

int main()
{
    char buff[] = "23";

    printf("%d\n", Atoi(buff));
    printf("%d\n",Atoi("-34"));
    printf("%d\n",Atoi("5h"));
    printf("%d\n",Atoi("^"));



    return (0);
}
