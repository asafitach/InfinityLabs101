#include<stdio.h>

int BestProfit( int *arr, int *buy_price, int *sell_price, int size);

int main()
{
int bursa_price[12]={5,43,2,56,4,7,3,6,7,9,3,7};
int *buy = bursa_price;
int *sell = bursa_price;
int profit = 0;

printf("seze of int %lu sizeof ptr %lu", sizeof(int), sizeof(int*));

profit = BestProfit(bursa_price, &buy, &sell, 12);

printf("The best profit is %d buy on %d indexed %lu and"
" sell on %d indexed %lu \n", profit, *buy, (size_t)(buy-bursa_price), *sell, (long int)(sell-bursa_price)/4);

return (0);
}

int BestProfit( int *arr, int *buy_price, int *sell_price, int size)
{
	int index = 0;
	int max_price;
	int min_price;
	max_price = *arr;
	min_price = *arr;

	for( index = 0; index < size; index++)
	{
		if(*(arr + index) > max_price)
		{
			max_price = *(arr + index);
			sell_price += index;
		}
		else if( *(arr+index) < min_price)
		{
			max_price = *(arr + index);
			min_price = *(arr + index);
			buy += index;
			sell_price += index;
		}
	}
	printf("The best profit is %d buy on %d indexed %lu and"
" sell on %d indexed %lu \n", max_price-min_price, min_price, (size_t)(buy_price-arr), max_price, (size_t)(sell_price-arr));
	return (max_price - min_price);
}
