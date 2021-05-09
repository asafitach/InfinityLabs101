#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "utility.h"



/***************************** tools ******************************************/

void Swap(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

/**************************************************/

int IntCmpFuncParam(const void *data1, const void *data2, const void *param)
{
	int res = *((int *)data1) - *((int *)data2);
	int flag = (res > 0) ? 1 : -1;
	res = (res > 0) ? res : -res;
	 
	if (res < *(int *)param)
	{
		return (0);
	}
	
	return (flag);
}

int IntCmpFunc(const void *data1, const void *data2)
{
	return (*((int *)data1) - *((int *)data2));
}


int PrintInt(void *data, void *param)
{
	param = param;
	printf("%d\t", *(int *)data);
	return (0);
}

void SwapMem(void* data1, void* data2, int size)
{
	char *buffer = (char *)malloc((size_t)size);
	if (NULL == buffer)
	{
		return;
	}

	memcpy(buffer, data1, size);
	memcpy(data1, data2, size);
	memcpy(data2, buffer, size);

	free(buffer);
}

/************************ mathematics functions *******************************/

int SumDigits(int num)
{
	int sum = 0;
	while (num)
	{
		sum += num / 10;
		num /= 10;
	}
	
	return (sum);
}
/**************************************************/

int CountDigits(int num)
{
	int count = 0;
	while (num)
	{
		++count;
		num /= 10;
	}
	
	return (count);
}
/**************************************************/

int Pow(int x, int y, int ans)		
{	
	if (0 ==y)
	{
		return (1);
	}
	
	if (y > 1)
	{
		ans = Pow(x, y - 1, ans);
	}
	
	return (ans * x);
}

double DPower(double x, double y)
{
	double res = 1;

	assert(0 != x);
	assert(y == (double)((int)y));

	if (y < 0)
	{
		y *= -1;
		x = 1 / x;
	}

	while (y)
	{
		res *= x;
		--y;
	}

	return (res);
}
/******************************* array functions ******************************/

void GetRandomArray(int *arr, size_t size, int range)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		arr[i] = (rand() % range) /*- range / 2 for negetive numbers */;
	}
}

/****************************************************/


int ArrCmp(int *arr1, int *arr2, size_t size)
{
	size_t index = 0;
	for (index = 0; index < size; ++index)
	{
		if (arr1[index] != arr2[index])
		{
			return 1;
		}
	}
	return 0;
}
/**************************************************/

void ArrCpy(int arr1[], int arr2[], size_t size)
{
	while (size)
	{
		arr1[size - 1] = arr2[size - 1];
		--size;
	}
}

/**************************************************/

void PrintArr(int arr[], size_t size)
{
	printf("print array:\n");
	while (size)
	{
		printf("%d\t", *arr);
		++arr;
		--size;
	}
	printf("\n");
}

/*************************************E.O.F.***********************************/
