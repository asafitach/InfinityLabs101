#include <stdio.h> /*printf*/
#include <stdlib.h>/*rand*/
#include <time.h>/*time*/
#include "utility.h"

#include "sorts.h"

#define MAGEN "\033[1;38;5;183m"   /* print in magenta      */
#define MAGENUL "\033[4;38;5;183m"   /* print in magenta      */
#define MAGENUL1 "\033[24;38;5;183m"   /* print in magenta      */
#define LIGHT "\033[2;37m"         /* print in gray         */


#define SIZE 30
/*****************************************************************************/

#define TEST(name, actual, expected)\
    				printf("%s: %s\n\n", name, actual == expected ?\
     				GREEN"Pass"RESET : RED"Fail"RESET)

#define NOT_TEST(name, actual, expected)\
    				printf("%s: %s\n\n", name, actual != expected ?\
     				GREEN"Pass"RESET : RED"Fail"RESET)
/******************************************************************************/

static int IntCmpFunc1(const void *data, const void *param);

/******************************************************************************/

void TestSort(void(*func)(int *, size_t), int *arr1, int *arr2, char *str)	
{
	float s_time =0;
	float qs_time = 0;
	clock_t before = 0;
	clock_t after = 0;
	
	GetRandomArray(arr1, SIZE, 1000);
	ArrCpy(arr2, arr1, SIZE);

	before = clock();
	func(arr1, SIZE);
	after = clock();
	s_time = (float)(after - before) / CLOCKS_PER_SEC;
	
	before = clock();
	qsort(arr2, SIZE, sizeof(int), IntCmpFunc1);
	after = clock();
	qs_time = (float)(after - before) / CLOCKS_PER_SEC;

	if (ArrCmp(arr1, arr2, SIZE))
	{
		printf(RED"%s sort function is incorrect!\n\n"RESET, str);
		return;
	}
		
	printf(MAGEN"qsort faster then " MAGENUL "%s" MAGENUL1 " sort by:\t\t%f\n\n"RESET, str, s_time - qs_time);
}	

void TestQSort(int *arr1, int *arr2, char *str)	
{
	GetRandomArray(arr1, SIZE, 1000);
	ArrCpy(arr2, arr1, SIZE);


	Qsort((void *)arr1, SIZE, sizeof(int), IntCmpFunc);
	
	qsort(arr2, SIZE, sizeof(int), IntCmpFunc1);

	if (ArrCmp(arr1, arr2, SIZE))
	{
		printf(RED"%s sort function is incorrect!\n\n"RESET, str);
		return;
	}
		
	printf(MAGENUL "%s success!\n\n"RESET, str);
}

void TestSearch(int*(*func)(int *, int, int), int *arr, char *str)
{
	int index = 0;
	int *ans = NULL;

	for (index = 0; index < SIZE; ++index)
	{
		arr[index] = index;
	}

	ans = func(arr, SIZE, SIZE / 3);
	printf(MAGEN"%s the number %d in array? %d (success)\n"RESET, str, SIZE / 3, *ans);

	ans = func(arr, SIZE, SIZE * 2);
	printf(MAGEN"%s the number %d in array? %d (1 for success)\n"RESET, str, SIZE * 2, (ans == NULL));
}
/******************************************************************************/
  				
int main()
{
	int arr1[SIZE] = {0};
	int arr2[SIZE] = {0};

	TestQSort(arr1, arr2, "quick sort");

/*	TestSort(BubbleSort, arr1, arr2, "bubble");
	
	TestSort(InsertionSort, arr1, arr2, "insertion");
	
	TestSort(SelectionSort, arr1, arr2, "selction");
	
	TestSort(CountingSort, arr1, arr2, "counting");
	
	TestSort(RadixSort, arr1, arr2, "radix");

	TestSort(MergeSort, arr1, arr2, "merge");

	TestSearch(BinarySearch, arr1, "binary search");

	TestSearch(RecursiveBinarySearch, arr1, "recuraive binary search");
*/
	return 0;
}

/******************************************************************************/

static int IntCmpFunc1(const void *data, const void *param)
{
    return (*(int*)data - *(int*)param);
}


/*************************** E. O. F. *****************************************/
