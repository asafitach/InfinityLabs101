#include<stdio.h>/*printf*/
#include<stdlib.h>/*getchar*/
#include"lut.h"


static void (*fun_arr[256])();

int main()
{
	int chr = 0;
	
	system("stty -icanon -echo");
	
	Initialize(fun_arr, 256);
	
	do
	{
	printf("Please press a key\n");
	chr = getchar();
	(*fun_arr[ chr ])();
	}
	while(chr != 27);
	
	return (0);
}
	
