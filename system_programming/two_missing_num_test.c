#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/


#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void Test(); 
void PrintMissingNumInArray(int arr[], int N);
void PrintMissingNumInArrayMath(int arr[], int N);

int main()
{
    system("clear");
    
    Test(); 
    
    return 0; 
}

void Test()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 12};
	
    printf(CYAN"\tTest \n\n"WHITE); 

	PrintMissingNumInArray(arr, 12);
	PrintMissingNumInArrayMath(arr, 12);
	    
    printf(CYAN"\tEnd Test \n\n"WHITE); 
}

/*
void PrintNaeivly(int arr[], int N)
{
	int index = 0;
	int val = 1
	while (val <= N)
	{
		while (val != arr[index] && index < N)
		{
			++index;
		}
		if (val == arr[index]
	*/	
void PrintMissingNumInArray(int arr[], int N)
{
	int index = 0;
	int *lut = (int *)malloc((N + 2) * sizeof(int))	;
	/*int flag = 0;*/
	for (index = 1; index <= N; ++index)
	{
		lut[index] = index;
	}
	
	for (index = 0; index < N - 2; ++index)
	{
		lut[arr[index]] ^= arr[index];
	}
	
	for (index = 1; index <= N; ++index)
	{
		if (0 != lut[index])
		{
			printf("Missing number is: %d\n", index);
			/*
			++flag;
			if (2 == flag)
			{
				breake;
			}
			*/
		}
	}
	free(lut);
}

void PrintMissingNumInArrayMath(int arr[], int N)
{
	register int sum = 0;
	register int pro = 1;
	int index = 0;
	
	for (index = 1; index <= N; ++index)
	{
		sum += index;
		pro *= index;
	}
	
	for (index = 0; index < N - 2; ++index)
	{
		sum -= arr[index];
		pro /= arr[index];
	}
	
	index = 1;
	while (pro != index * (sum - index))
	{
		++index;
	}
	
	printf("Missing number is: %d\n", index);
	printf("Missing number is: %d\n", sum - index);
}
