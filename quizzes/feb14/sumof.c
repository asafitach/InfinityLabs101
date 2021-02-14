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
			return(last*100000+first);
		}
	}

	return (0);
}

