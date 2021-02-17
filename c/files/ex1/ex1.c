#include<stdio.h>
#include"ex1.h"

/************************************************/
void Init(struct print_me *array ,int size)
{
	int index;

	for(index=0; index<size;index++)
	{
		array[index].var= index;
		array[index].ptr=&Print;
	}

	return;
}

/************************************************/

void Print(int num)
{
	printf("The number is: %d\n", num);
	return;
}

/**********************EOF***********************/
