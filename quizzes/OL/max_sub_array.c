#include <stdio.h>

#define SIZE 8
int MaxSubArray1(int arr[], int size, int *begin, int *end);
int MaxSubArray(int array[], int size);

int main()
{
	int array[SIZE] = {2, 3, 6, -5, 3, -40, 50, -8};
	int begin_index = 0;
	int end_index = 0;
	int res = 0;
	
	res = MaxSubArray(array, SIZE);
	
	printf("max sum of sub array is: %d start at index %d and end at index %d\n"
	, res, begin_index, end_index);
	
	return (0);
}

int MaxSubArray1(int arr[], int size, int *begin, int *end)
{
	int p_sum = 0;
	int n_sum = 0;
	int t_sum = 0;
	int begin_ = 0;
	int end_ = 0;
	int index = 0;

	
	for (index = 0; index < size; index++)
	{		
		while (0 > *arr && index < size)
		{
			n_sum += *arr;
			index++;
			arr++;
		}
			printf("%d\t", n_sum);
		printf(" negagive\n");
		
		while (0 <= *arr && index < size)
		{
			p_sum += *arr;
			index++;
			arr++;
		}
			printf("%d\t", p_sum);
		printf(" posetive\n");
				
		if (p_sum > -n_sum)
		{
			t_sum += (p_sum + n_sum);
			p_sum = 0;
			n_sum = 0;
			
		}
		
		else
		{
			p_sum = 0;
			n_sum = 0;
		}
		index--;
	}
	
	return (t_sum);
}

int MaxSubArray(int array[], int size)
{
	int index = 0;
	int max = 0; 
	int total_max = 0;
	
	for (index = 0; index < size; ++index)
	{
		max += array[index];
		if (max < array[index])
		max = array[index];
		if (max > total_max)
		{
			total_max = max;
		}
		
	}
	
	return ((max > total_max) ? max: total_max);
}
