/*this is utility file include lots of handy function*/

#ifndef __utility_H__
#define __utility_H__

#include <stddef.h>/* size_t */
#include <stdlib.h>/* rand */


#define RANGE 1000000
#define ASCII 256
#define WORD 8
#define BYTE 1

typedef enum status
{
	SUCCSESS = 0,
	MALLOC_FAILED = 1,
	FAIL = 2,
	STOP = 3,
	REMOVE = 4,
	NOT_FOUND = 5,
	TRUE = 6,
	FALSE = 7
}status_t;


/***************************** tools ******************************************/

void Swap(int *x, int *y);

int IntCmpFunc(const void *data1, const void *data2, const void *param);

/************************ mathematics functions *******************************/

int SumDigits(int num);

int CountDigits(int num);

int Pow(int x, int y, int ans);

/******************************* array functions ******************************/

void GetRandomArray(int *arr, size_t size, int range);

int ArrCmp(int *arr1, int *arr2, size_t size);

void ArrCpy(int arr1[], int arr2[], size_t size);

void PrintArr(int arr[], size_t size);

#endif
/*************************************E.O.F.***********************************/
