#include<stdio.h>
#include"sumof.h"


int main()
{
	int arr[]= {1,3,4,6,7,11,18,20,29,33,56,63,85,90};
	int size=14;
	int sum=32;
	int ans;

	ans= IsSumFound(arr, sum, size);

	if(ans)
	{
		printf("the first index is %d and the other is %d\n", *(arr), *(arr+1));
	}

	else
	{
		printf("No sum found");
	}

	return 0;
}

