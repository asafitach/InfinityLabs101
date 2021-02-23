#include <stdio.h>
#include "ex2.h"

int main()
{
	int a = 6;
	int b = 8;
	int c = 7;
	
	printf("First number: %d\n", a);
	printf("Second number: %d\n", b);


	printf("Maximum number is: %d\n\n\n",MAX2(a, b));
	
	
	printf("First number: %d\n", a);
	printf("Second number: %d\n", b);
	printf("Third number: %d\n", c);


	printf("Maximum number is: %d\n",MAX(a, b, c));
	
	return 0;
}
