#include <stdio.h>

int main()
{

    int arr[12] = {0};
    int i = 2;
    int a = 5;
    int b = 10;
    int c = 25;
    b = b++ + c++;
    c = ++b + ++c;

    
    arr[i] = i++;
    a = a++;
    for(i = 0; i< 12; ++i)
    {
        printf("\t%d\t", arr[i]);
    }
    printf("\n%d\n", a);
    printf("\n%d %d\n", b,c);


    return 0;
}