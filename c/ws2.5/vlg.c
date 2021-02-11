#include<stdlib.h>
#include<stdio.h>

int main()
{
int num;
int * int_arr=NULL;
char *ptr =(char *)malloc(2*sizeof(char));

int_arr=(int *)malloc(10*sizeof(int));
printf("%d \n", int_arr[11]);
num=int_arr[11];
printf("%d \n", num);
free(ptr);
printf("%c \n", ptr);

return 0;
}
