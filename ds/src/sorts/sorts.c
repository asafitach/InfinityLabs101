#include <assert.h> /* assert */

#include "sorts.h"


void Swap(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

/******************************************************************************/

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

/******************************************************************************/

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

/******************************************************************************/

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

/***********************************E.O.F.*************************************/

