#include <assert.h> /* assert */
#include <stdlib.h>/*malloc calloc*/
#include <stdio.h> /*printf*/
#include <utility.h> /* GetRandomArray, Pow, Swap ...*/

#include "sorts.h"

#define BASE 10
/**************************** side functions ***********************************/
int MaxDIgitsInArray(int arr[], int size, int *min_val)
{
	int index = 0;
	int max = *arr;
	int min = *arr;
	
	for (index = 0; index < size; ++index)
	{
		max = (max < arr[index]) ? arr[index] : max;
		min = (min > arr[index]) ? arr[index] : min;
	}
	
	*min_val = min;
	return (CountDigits(max));
}
/******************************************************************************/

int RangeOfArr(int arr[], int size, int *min_val)
{
	int max = *arr;
	int min = *arr;
	int index = 0;
	int tmp = 0;
	
	for (index = 0; index < size; ++index)
	{
		tmp = arr[index];
		if (min > tmp)
		{
			min = tmp;
		}
		else if (max < tmp)
		{
			max = tmp;
		}
	}
	*min_val = min;
	return (max - min);
}

/**************************** comparision sorts *******************************/
/*****************************  Bubble Sort  **********************************/

void BubbleSort(int *arr, size_t size)
{
	int stop_flag = 1;
	size_t index = 0;
	
	assert(NULL != arr);

	while (0 != stop_flag)
	{
		stop_flag = 0;
	
		for (index = 0; index < size - 1; index++)
		{
			if (arr[index + 1] < arr[index])
			{
				stop_flag = 1;
				Swap(arr + index, arr + index + 1);
			}
		}
	}	
	
	return ;
}

/****************************** insertion Sort ********************************/

void InsertionSort(int *arr, size_t size)
{	
	size_t index = 0;
	size_t inner_index = 0;
	
	assert(NULL != arr);
	
	for (index = 1; index < size; index++)
	{
		inner_index = index;
		
		while (inner_index > 0 && arr[inner_index] < arr[inner_index - 1])
		{
			Swap(arr + inner_index, arr + inner_index - 1);
			inner_index--;
		}				
	}
}

/**************************** Selection Sort **********************************/

void SelectionSort(int *arr, size_t size)
{
    size_t curr_min = 0;
    size_t index = 0;
    size_t inner_index = 0;

    
    assert(NULL != arr);
    
    for (index = 0; index < size; index++)
    {
        curr_min = index;
        
        for (inner_index = index + 1; inner_index < size; inner_index++)
        {
            if (arr[curr_min] > arr[inner_index])
            {
                curr_min = inner_index;
            }
        }
        
		Swap(arr + index, arr + curr_min);
    }
}

/************************** Counting Sorts ************************************/
/************************** Counting Sort *************************************/

void CountingSort(int *arr, size_t size)
{
	size_t index = 0;
	int tmp = 0;
	int min = 0;
	size_t range = (size_t)RangeOfArr(arr, (int)size, &min);
	int *count_array = calloc(sizeof(int), range + 1);
	int *output = (int *)malloc(size * sizeof(int));
	if (NULL == count_array || NULL == output)
	{
		printf("Allocation Failed\n");
		return;
	}
	
	for (index = 0; index < size; ++index)
	{
		count_array[arr[index] - min] += 1;
	}
	
	for (index = 1; index <= range; ++index)
	{
		count_array[index] += count_array[index - 1];
	}
	
	 for (index = 0; index < size; ++index)
	 {
	 	tmp = arr[index] - min;
	 	output[count_array[tmp] - 1] = tmp + min;
	 	count_array[tmp] -=1;
	 }
	 
	 ArrCpy(arr, output, size);
	 
	 free(count_array);
	 free(output);
}
/******************************************************************************/

void SortDigit(int *arr, size_t size, int digit_num, int min)
{
	int index = 0;
	int *output = NULL; 
	int exp = 1;
	int tmp = 0;
	int count_array [BASE]= {0};
	
	output = (int *)malloc(sizeof(int) * size);
	exp = Pow(BASE, digit_num - 1, 1);
			
	for (index = 0; index < (int)size; ++index)
	{
		count_array[((arr[index] - min) / exp) % BASE] += 1;
	}
	
	for (index = 0; index < BASE - 1; ++index)
	{
		 count_array[index + 1] += count_array[index];
	}
	

	
	for (index = size - 1; index >= 0; --index)
	{
		tmp = arr[index] - min;
		output[count_array[(tmp / exp) % BASE] - 1] = tmp + min;
		count_array[(tmp / exp) % BASE] -= 1;
	}

	
	ArrCpy(arr, output, size);
	
	free(output);
}

/************************** Radix Sort ****************************************/

void RadixSort(int *arr, size_t size)
{
	int index = 0;
	int min = 0;
	int count_max_digit = MaxDIgitsInArray(arr, size, &min);
	assert (NULL != arr);
	
	for (index = 1; index <= count_max_digit; ++index)
	{
		SortDigit(arr, size, index, min);
	}
	
}


/***********************************E.O.F.*************************************/

