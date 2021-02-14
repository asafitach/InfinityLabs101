#include"sumof.h"
int IsSumFound (int* sorted_arr, int sum, int size)
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
			*(sorted_arr) = first;
			*(sorted_arr + 1) = last;
			return(1);
		}
	}

	return (0);
}

