/*****************************************************************************
 *	FILENAME:	ex3.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    ex3.											      	 	 *
 *																			 *
 *****************************************************************************/

#include <cstdio>
#include <iostream>

/*****************************************************************************/
int main(void)
{
	char c = 100;
	bool b1 = true;
	bool b2 = 7;
	int i = b1;
	
	i = 7;
	b2 = i;

	printf("value of b2: %d \n", b2);
	printf("value of char: %c \n", c);
	printf("bool size: %ld \n", sizeof(bool));

	return 0;
}
/*****************************************************************************/