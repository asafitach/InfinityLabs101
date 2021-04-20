#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 100

int RangeOfArr(int arr[], int size)
{
	int max = -0xffffffff;
	int min = 0xffffffff;
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
	return (max - min);
}

void ArrCpy(int arr1[], int arr2[], int size)
{
	while (size)
	{
		arr1[size - 1] = arr2[size - 1];
		--size;
	}
}

void CountingSort(int arr[], int size)
{
	int index = 0;
	int tmp = 0;
	int range = RangeOfArr(arr, size);
	int *count_array = calloc(sizeof(int), range + 1);
	int *output = (int *)malloc(size * sizeof(int));
	if (NULL == count_array || NULL == output)
	{
		printf("Allocation Failed\n");
		return;
	}
	
	for (index = 0; index < size; ++index)
	{
		count_array[arr[index]] += 1;
	}
	
	for (index = 1; index <= range; ++index)
	{
		count_array[index] += count_array[index - 1];
	}
	
	 for (index = 0; index < size; ++index)
	 {
	 	tmp = arr[index];
	 	output[count_array[tmp] - 1] = tmp;
	 	count_array[tmp] -=1;
	 }
	 
	 ArrCpy(arr, output, size);
	 
	 free(count_array);
	 free(output);
}

/*size_t GetDigit(int num)*/
/*{*/
/*	size_t count = 0;*/
/*	*/
/*	while (num)*/
/*	{*/
/*		++count;*/
/*		num /= 10;*/
/*	}*/
/*	return (count);*/
/*}*/

/*void RadixSort(int arr[], int size)*/
/*{*/
/*	int index = 0;*/
/*	int tmp = 0;*/
/*	int range = GetDigit(RangeOfArr(arr, size));*/
/*	int *count_array = calloc(sizeof(int), range);*/
/*	int *output = (int *)malloc(size * sizeof(int));*/
/*	if (NULL == count_array || NULL == output)*/
/*	{*/
/*		printf("Allocation Failed\n");*/
/*		return;*/
/*	}*/
/*	*/
/*	for (index = 0; index < size; ++index)*/
/*	{*/
/*		tmp = arr[index] */
/*		count_array[arr[index]] += 1;*/
/*	}*/
/*	*/
/*	for (index = 1; index <= range; ++index)*/
/*	{*/
/*		count_array[index] += count_array[index - 1];*/
/*	}*/
/*	*/
/*	 for (index = size - 1; index >= 0; --index)*/
/*	 {*/
/*	 	tmp = arr[index];*/
/*	 	output[count_array[tmp] - 1] = tmp;*/
/*	 	count_array[tmp] -=1;*/
/*	 }*/
/*	 */
/*	 for (index = 0; index < size; ++index)*/
/*	 {*/
/*	 	arr[index] = output[index];*/
/*	 }*/
/*	 */
/*	 free(count_array);*/
/*	 free(output);*/
/*}*/



void GetRandomArray(int *arr, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		arr[i] = rand();
	}
}


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
	
	
int MaxDIgitsInArray(int arr[], int size)
{
	int index = 0;
	int max = 0;
	
	for (index = 0; index < size; ++index)
	{
		max = (max < arr[index]) ? arr[index] : max;
	}
	
	index = 0;
	while (max)
	{
		++index;
		max /=10;
	}
	
	return (index);
}




void SortDigit(int *arr, size_t size, int digit_num)
{
	int index = 0;
	int *output = NULL; 
	int exp = 1;
	int tmp = 0;
	int count_array [10]= {0};
	
	output = (int *)malloc(sizeof(int) * size);
	exp = Pow(10, digit_num - 1, 1);
			
	for (index = 0; index < (int)size; ++index)
	{
		count_array[(arr[index] / exp) % 10] += 1;
	}
	
	for (index = 0; index < 9; ++index)
	{
		 count_array[index + 1] += count_array[index];
	}
	

	
	for (index = size - 1; index >= 0; --index)
	{
		tmp = arr[index];
		output[count_array[(tmp / exp) % 10] - 1] = tmp;
		count_array[(tmp / exp) % 10] -= 1;
	}

	
	ArrCpy(arr, output, size);
	
	free(output);
}

/*****************************************************************************/

void RadixSort(int *arr, size_t size)
{
	int index = 0;
	int count_max_digit = MaxDIgitsInArray(arr, size);
	assert (NULL != arr);
	
	for (index = 1; index <= count_max_digit; ++index)
	{
		SortDigit(arr, size, index);
	}
	
}

int main()	
{
	int arr[SIZE] = {0};
	int index = 0;
	
	GetRandomArray(arr, SIZE);
	RadixSort(arr, SIZE);
	
	printf("\n\n");
	
	for (index = 0; index < SIZE - 1; ++index)
	{
		if (arr[index] > arr[index + 1])
		{
			printf("%d\t", arr[index]);
		}
	}

	return 0;
}
