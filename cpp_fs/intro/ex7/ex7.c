/*****************************************************************************
 *	FILENAME:	ex7.c              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    testing for ex7 lib.							      	 *
 *																			 *
 *****************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* dynamic allocations */
/*****************************************************************************/
int main(void)
{
	int *x = (int *)malloc(sizeof(int));
	*x = 4;

	free(x);

	*x = 2;

	printf("%d \n", *x);

	return 0;
}
/*****************************************************************************/