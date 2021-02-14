#include<stdio.h>
#include<stdlib.h>
#include"Josephus.h"



int main()
{


int num = 0;
int* arr;

printf("please insert the number of soldiers: \n");
scanf("%d", &num);


arr = (int*)malloc(num * sizeof(int));

AllAlive(arr, num);
KillToSurvive(arr, num);
PrintTheLast(arr, num);

free(arr);


return (0);
}
