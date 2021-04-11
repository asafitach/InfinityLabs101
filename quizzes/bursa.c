#include<stdio.h>

#define SIZE 12

int BestProfit( int *arr, int *buy_price, int *sell_price, int size);

int main()
{
int bursa_price[SIZE]={5,43,2,56,4,7,3,6,7,9,3,7};
/*int bursa_price[SIZE]={6,12,3,5,1,4,5,2};*/
int buy = 0;
int sell = 0;
int profit = 0;

	

profit = BestProfit(bursa_price, &buy, &sell, SIZE);

printf("The best profit is %d buy on %d indexed %d and"
" sell on %d indexed %d \n", profit, bursa_price[buy], buy, bursa_price[sell], sell);

return (0);
}

int BestProfit( int *arr, int *buy_price, int *sell_price, int size)
{
	int index = 0;
	int max_price = *arr;
	int max_index = 0;
	int min_price = *arr;
	int min_index = 0;
	
	struct {
	int profit;
	int b_index;
	int s_index;
	}sum;
	
	sum.profit = 0;
	sum.b_index = 0;
	sum.s_index = 0;
	

	for( index = 1; index < size; index++)
	{
		if(*(arr + index) > max_price)
		{
			max_price = *(arr + index);
			max_index = index;
		}
		else if( *(arr+index) < min_price)
		{
			if ( sum.profit < max_price - min_price)
			{
				 sum.profit = max_price - min_price;
				 sum.s_index = max_index;
				 sum.b_index = min_index;
			}
				max_price = *(arr + index);
				min_price = *(arr + index);
				max_index = index;
				min_index = index;
			
		}
	}

	if ( sum.profit < max_price - min_price)
	{

		 sum.profit = max_price - min_price;
		 sum.b_index = min_index;
		 sum.s_index = max_index;
	}
	
	*sell_price = sum.s_index;
	*buy_price = sum.b_index;
	
	return ( sum.profit);
}
