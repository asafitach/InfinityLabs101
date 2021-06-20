/*****************************************************************************
 *	FILENAME:	ex5.c              AUTHOR: Liad Oz	     LAB: RD100	     	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    testing for ex5 lib.							      	 	 *
 *																			 *
 *****************************************************************************/

#include <stdio.h> /* printf */

/*****************************************************************************/
typedef struct student { int key; } student_t;

int main(void)
{
	student_t s = {2};
	int x = 5;

	foo(x);

	return 0;
}

int foo(student_t *ps)
{
	/*
	puts("yay!");

	printf("%d \n", s.key);
	*/

	ps->key = 3;
	
	return 0;
}
/*****************************************************************************/