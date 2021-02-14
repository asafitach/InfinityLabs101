#include<stdio.h>/*printf*/
#include<stddef.h>/*size_t*/
#include"datatype.h"


void Match(char **name, size_t *size)
	{
	int i=0;
	for(i=0;i<16;i++)
	{
		*(size+i)=sizeof(*(name+i));
	}

	return;
}



void print(char **name, size_t *size)
{
	int i=0;
	for(i=0;i<16;i++)
	{
		printf("The data type name's is %s \nit's size is %lu \n", *(name+i), *(size+i));
	}
	return;
}


