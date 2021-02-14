#include<stdio.h>
#include<stdlib.h>
#include"if_else.h"

int main(int argc char **argv)
{

void (**fun_arr)()[256];
int size = 256;
int i=1;

Initialize(fun_arr, size);

if(

while(*(argv+i))
{
*(fun_arr+atoi(*(argv+i)))();
i++;
}

return(0);
}

