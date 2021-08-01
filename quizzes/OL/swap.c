#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include <stdio.h>
/******************************************************************************/

void Swap1(int *x, int *y)
{
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}

void Swap2(int *x, int *y)
{
	int tmp = 0;
	
	tmp = *x;
	*x = *y;
	*y = tmp;
}


void Swap3 (int *x, int *y)
{
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

int main()
{
	int x = 7;
	int y = 3;
	
	printf("x = %d\ty = %d\n", x, y);
	printf("swap!\n");
	Swap1(&x, &y);
	printf("x = %d\ty = %d\n", x, y);
	printf("swap!\n");
	Swap2(&x, &y);
	printf("x = %d\ty = %d\n", x, y);
	printf("swap!\n");
	Swap3(&x, &y);
	printf("x = %d\ty = %d\n", x, y);
	
	return (0);
}
/********************************E.O.F*****************************************/
