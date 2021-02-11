#include<stdio.h>
#include "Josephus.h"


void AllAlive( int *arr, int num)
{
	int i = 0;
	for(i = 0; i < num; i++)
	{
		*(arr + i) = 1;
	}
	return;
}

/**********************************************/

void KillToSurvive(int *arr, int num)
{
int i = 0;
int count = 0;
int flag = 0;

while( count < num-1 )
{
	if( arr[i%num] == 1 && flag == 0)
	{
		flag = 1;
	}
	else if( arr[i % num] == 1 && flag == 1)
	{
		arr[i % num] = 0;
		flag = 0;
		count++;
	}
	i++;
}
return;
}

/**********************************************/

void PrintTheLast (int *arr, int num)
{
	int i;
	
	for(i = 0; i < num; i++)
	{
		if(*(arr + i))
		{
			i++;
			printf("the last one is number %d", i);
		}
	}
	return;
}

/************************EOF*******************/
