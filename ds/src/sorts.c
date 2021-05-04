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



/*************************** Binary Search ************************************/

int *BinarySearch(int *arr, int array_size, int num)
{
	int from = 0;
	int cur_size = array_size;
	int cur_value = 0;

	assert(NULL != arr);

	cur_value = arr[cur_size / 2];
	while (cur_value != num && cur_size > 0 && cur_size <= array_size)
	{
		if (cur_value < num)
		{
			from += cur_size / 2;
		}
			cur_size /= 2;
		cur_value = arr[from + (cur_size / 2)];
	}

	if (cur_value == num)
	{
		return (arr + from + (cur_size / 2));
	}
	return (NULL);
}

/******************** Recursive Binary Search *********************************/

int *RecursiveBinarySearch(int *arr, int array_size, int num)
{
	if (num == *(arr + array_size / 2))
	{
		return (arr + array_size / 2);
	}
	if (array_size <= 1)
	{
		return (NULL);
	}
	else if (num < *(arr + array_size / 2))
	{
		return (RecursiveBinarySearch(arr, array_size / 2, num));
	}
	else /*if (num > *(arr + array_size / 2))*/
	{
		return (RecursiveBinarySearch(arr + array_size / 2, array_size / 2, num));
	}
}


/*************************** Merge Sort ***************************************/

/*
static void Merge(int *arr, int *left, int *middle, int *right, int *help_arr)
{
	int help_index = left - arr;
	int *runner = middle;

	if (left == middle)
	{
		if (*left > runner)
		{

		}
	} || runner == right)
	{
		if (left != middle)
		{
			if (*left < *middle)
			{

			}
			help_arr[help_index] = 
		}
		help_arr[help_index] = MIN3(*left, *right, *runner);
		if (*left > *right)
		{
			help_arr[help_index] = *right;
			++help_index;
			help_arr[help_index] = *left;
		}
		return;
	}
	do
	{
		if (*left < *runner)
		{
			help_arr[help_index] = *left;
			++left;
		}
		else
		{
			help_arr[help_index] = *(runner);
			++runner;
		}
		++help_index;
	}
	while (left != middle && runner != right);
		if (*left < *runner && left != middle)
		{
			help_arr[help_index] = *left;
			++left;
		}
		else if (*runner < *left && runner != right)
		{
			help_arr[help_index] = *(runner);
			++runner;
		}
		++help_index;

		while (runner != right)
		{
			help_arr[help_index] = *runner;
			++runner;
			++help_index;
		}


		while (left != middle)
		{
			help_arr[help_index] = *left;
			++left;
			++help_index;
		}		
	
	
}

static void RecursiveMergeSort(int *arr, int *left, int *right, int *help_arr)
{
	int *middle = (int *)(((right - left) / 2) + left);

	if (left == right)
	{
		return;
	}

	RecursiveMergeSort(arr, left, middle, help_arr);
	RecursiveMergeSort(arr, middle + 1, right, help_arr);

	Merge(arr, left, middle, right, help_arr);
}

void MergeSort(int *arr_to_sort, size_t num_elements)
{
	int *help_arr = (int *)malloc(sizeof(int) * num_elements);
	if (NULL == help_arr)
	{
		return;
	}

	RecursiveMergeSort(arr_to_sort, arr_to_sort, arr_to_sort + num_elements - 1, help_arr);
	ArrCpy(arr_to_sort, help_arr, num_elements);
	free(help_arr);
}
*/
void Merge(int *left_arr, int left_len, int *right_arr, int right_len)
{
	int left_runner = 0;
	int right_runner = 0;
	int *tmp_index = NULL;

	assert(NULL != left_arr);
	assert(NULL != right_arr);

	int *tmp_arr = (int *)malloc(sizeof(int) * (left_len + right_len));
	if (NULL == tmp_arr)
	{
		return;
	}
	tmp_index = tmp_arr;

	while (left_runner < left_len && right_runner < right_len)
	{
		if (left_arr[left_runner] <= right_arr[right_runner])
		{
			*tmp_index = left_arr[left_runner];
			++left_runner;
		}
		else
		{
			*tmp_index = right_arr[right_runner];
			++right_runner;
		}
		++tmp_index;
	}

	while (left_runner < left_len)
	{
		*tmp_index = left_arr[left_runner];
		++left_runner;
		++tmp_index;
	}
	while (right_runner < right_len)
	{
		*tmp_index = right_arr[right_runner];
		++right_runner;
		++tmp_index;
	}

	ArrCpy(left_arr, tmp_arr, left_len + right_len);
	free(tmp_arr);
}

void MergeSort(int *arr, size_t size)
{
	if (size < 2)
	{
		return;
	}
	MergeSort(arr, size / 2);
	MergeSort(arr + (size / 2), size - (size / 2));

	Merge(arr ,size / 2, arr + (size / 2), size - (size / 2));
}

/*************************** Quick Sort ***************************************/
void Qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))
{
	char *left = (char *)base + size;
	char *right = (char *)base + (nitems - 1) * size;

	if (2 > nitems)
	{
		return;
	}

	while (left != right)
	{
		while (0 >= compar(left, base) && left != right)
		{
			left += size;
		}
		while (0 < compar(right, base) && left != right)
		{
			right -= size;
		}
		SwapMem(left, right, size);
	}

		SwapMem(right - size, base, size);
	


	Qsort(base, (((char *)right - (char *)base) / size), size, compar);
	Qsort((void *)(right), nitems - (((char *)right - (char *)base) / size), size, compar);


}





/***********************************E.O.F.*************************************/