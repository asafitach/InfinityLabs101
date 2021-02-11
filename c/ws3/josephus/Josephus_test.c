#include<stdio.h>
#include<stdlib.h>
#include"Josephus.h"



int main( int argc, char** argv)
{


int num=0;
int* arr;

if(argc<2)
{
printf("Please insert number while entering the file");
}

num=atoi(argv[1]);
arr= (int*)malloc(num*sizeof(int));

AllAlive(arr, num);
KillToSurvive(arr, num);
PrintTheLast(arr, num);


return (0);
}
