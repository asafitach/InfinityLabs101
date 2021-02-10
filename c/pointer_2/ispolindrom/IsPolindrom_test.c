#include<stdio.h>
#include"IsPolindrom.h"

int main()
{
char polindrom[] = "abba";
char polindrom2[] = "abbjbba";
char polindrom3[] = "abaa";
int ans=0;

ans=IsPolindrom(polindrom);
printf("%s is polindrom? %d \n", polindrom, ans);
ans=IsPolindrom(polindrom2);
printf("%s is polindrom? %d \n", polindrom2, ans);
ans=IsPolindrom(polindrom3);
printf("%s is polindrom? %d \n", polindrom3, ans);

return (0);
}


