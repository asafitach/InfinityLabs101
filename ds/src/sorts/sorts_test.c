#include <stdio.h> /*printf*/
#include <stdlib.h>/*rand*/
#include <time.h>/*time*/

#include "sorts.h"

#define RED "\033[5;91m"           /* print in red          */
#define GREEN "\033[1;38;5;47m"    /* print in green        */
#define MAGEN "\033[1;38;5;183m"   /* print in magenta      */
#define MAGENUL "\033[4;38;5;183m"   /* print in magenta      */
#define MAGENUL1 "\033[24;38;5;183m"   /* print in magenta      */
#define YELLOW "\033[1;38;5;220m"  /* print in light yellow */
#define CYAN "\033[0;96m"          /* print in cyan         */
#define LIGHT "\033[2;37m"         /* print in gray         */
#define PURPLE "\033[1;4;38;5;224m"/* print in purple       */
#define RESET "\033[1;0m"          /* reset print color     */


#define SIZE 5000
/*****************************************************************************/

#define TEST(name, actual, expected)\
    				printf("%s: %s\n\n", name, actual == expected ?\
     				GREEN"Pass"RESET : RED"Fail"RESET)

#define NOT_TEST(name, actual, expected)\
    				printf("%s: %s\n\n", name, actual != expected ?\
     				GREEN"Pass"RESET : RED"Fail"RESET)
/******************************************************************************/

void GetRandomArray(int *arr, size_t size);
static int IntCmpFunc(const void *data, const void *param);
static int ArrayCompare(int *arr1, int *arr2, size_t size);
static void ArrayCopy(int *arr1, int *arr2, size_t size);

/******************************************************************************/

void TestSort(void(*func)(int *, size_t), int *arr1, int *arr2, char *str)	
{
	float s_time =0;
	float qs_time = 0;
	clock_t before = 0;
	clock_t after = 0;
	
	GetRandomArray(arr1, SIZE);
	ArrayCopy(arr2, arr1, SIZE);
	
	before = clock();
	func(arr1, SIZE);
	after = clock();
	s_time = (float)(after - before) / CLOCKS_PER_SEC;
	
	before = clock();
	qsort(arr2, SIZE, sizeof(int), IntCmpFunc);
	after = clock();
	qs_time = (float)(after - before) / CLOCKS_PER_SEC;
	
	if (ArrayCompare(arr1, arr2, SIZE))
	{
		printf(RED"sort function is incorrect!\n"RESET);
	}
		
	printf(MAGEN"qsort faster then " MAGENUL "%s" MAGENUL1 " sort by:\t\t%f\n\n"RESET, str, s_time - qs_time);
}	
/******************************************************************************/
  				
int main()
{
	int arr1[SIZE] = {0};
	int arr2[SIZE] = {0};

	TestSort(BubbleSort, arr1, arr2, "bubble");
	
	TestSort(InsertionSort, arr1, arr2, "insertion");
	
	TestSort(SelectionSort, arr1, arr2, "selction");

	
	return 0;
}

/******************************************************************************/

void GetRandomArray(int *arr, size_t size)
{
	size_t i = 0;
	srand(time(0));
	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 100;
	}
}



/******************************************************************************/

static int IntCmpFunc(const void *data, const void *param)
{
    return (*(int*)data - *(int*)param);
}


/******************************************************************************/

static int ArrayCompare(int *arr1, int *arr2, size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			return 1;
		}
	}
	return 0;
}

/******************************************************************************/

static void ArrayCopy(int *arr1, int *arr2, size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		arr1[i] = arr2[i];
		
	}
	
}
