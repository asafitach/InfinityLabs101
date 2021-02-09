#include <stdio.h>
int StrCmp (char a1[], char b1[]);
int StrLen (char a[]);


int main()
{
    char array_a[] = {'a', 'b', 'c', 'd', 'e', 'f', 'f','\0'};
    char array_b[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', '\0'};
    size_t i= StrLen (array_a);
    size_t j= StrCmp (array_a, array_b);
    
    return (0);
}

int StrLen (char a[])
{
    size_t count=0;
    while(a[count])
    {
     count++;   
    }
return(count);
}

int StrCmp (char a1[], char b1[])
{
    int i=0;
    while (a1[i] || b1[i])
    {
        if((a1[i]>b1[i]) || (a1[i]<b1[i]))
        {
            return (a1[i]-b1[i]);
        }
        i++;
    }
return (0);
    
}
