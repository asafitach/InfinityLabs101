#include<stdio.h>

int BestProfit( int *arr, int *buy_price, int *sell_price, int size);

int main()
{
int bursa_price[12]={0,43,2,56,4,7,3,6,7,9,3,7};
int *buy = bursa_price;
int *sell = bursa_price;
int profit = 0;

profit = BestProfit(bursa_price, buy, sell, 12);

printf("The best profit is %d buy on %d indexed %p and"
" sell on %d indexed %p \n", profit, *buy, buy-bursa_price, *sell, sell-bursa_price);

return (0);
}

int BestProfit( int *arr, int *buy_price, int *sell_price, int size)
{
int index = 0;
int max price = *arr;
