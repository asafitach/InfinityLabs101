#include<stdio.h>/*printf, scanf*/
#include<stdlib.h>/*malloc, free*/
#include"Josephus.h"



int main()
{


	int num = 0;
	int* arr = NULL;

	printf("please insert the number of soldiers: \n");
	scanf("%d", &num);


	arr = (int*)malloc(num * sizeof(int));
	if(arr == 0)
	{
		printf("allocation eror\n");
		free(arr);
		exit(1);
	}

	AllAlive(arr, num);
	KillToSurvive(arr, num);
	PrintTheLast(arr, num);

	free(arr);


	return (0);
}
