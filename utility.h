/*this is utility file include lots of handy function*/

#ifndef __utility_H__
#define __utility_H__

#include <stddef.h>/* size_t */
#include <stdlib.h>/* rand */


#define RANGE 1000000
#define ASCII 256
#define WORD 8
#define BYTE 1
#define BUFF_SIZE 256

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) (MAX(MAX((a), (b)), (c)))

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MIN3(a, b, c) (MIN(MIN((a), (b)), (c)))

typedef enum status
{
	SUCCESS = 0,
	MALLOC_FAILED = 1,
	FAIL = 2,
	STOP = 3,
	REMOVE = 4,
	NOT_FOUND = 5,
	TRUE = 6,
	FALSE = 7
}status_t;

/*********************** color macros for printf *********************************/

#define RED "\033[1;31m"  

#define GREEN "\033[1;5;32m"	

#define BLUE "\033[1;34m"  

#define YELLOW "\033[1;4:1;33m" 

#define PURPLE "\033[1;35m" 

#define CYAN "\033[1;3;36m"

#define RESET "\033[0m" 

/***************************** tools ******************************************/

void Swap(int *x, int *y);

int IntCmpFunc(const void *data1, const void *data2);

int IntCmpFuncParam(const void *data1, const void *data2, const void *param);

int PrintInt(void *data, void *param);

void SwapMem(void* data1, void* data2, int size);

/************************ mathematics functions *******************************/

int SumDigits(int num);

int CountDigits(int num);

int Pow(int x, int y, int ans);

double DPower(double x, double y);

/******************************* array functions ******************************/

void GetRandomArray(int *arr, size_t size, int range);

int ArrCmp(int *arr1, int *arr2, size_t size);

void ArrCpy(int arr1[], int arr2[], size_t size);

void PrintArr(int arr[], size_t size);

#endif
/*************************************E.O.F.***********************************/
