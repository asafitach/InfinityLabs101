#include <stdio.h>


int IsSumFound (int* sorted_arr, int sum, int size, int *first_ans, int *last_ans)
{
	int first, last;
	for(first=0, last=size-1;first<last;)
	{
		if(*(sorted_arr+first)+*(sorted_arr+last)<sum)
		{
			first++;
		}
		else if(*(sorted_arr+first)+*(sorted_arr+last)>sum)
		{
			last--;
		}
		if (*(sorted_arr+first)+*(sorted_arr+last)==sum)
		{
			*first_ans = first;
			*last_ans = last;
			return(1);
		}
	}

	return (0);
}



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

