/*****************************************************************************
 *	FILENAME:	ex7.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    testing for ex7 lib.							      	 	 *
 *																			 *
 *****************************************************************************/
/*
typedef struct student {int key; int name;} student_t;
*/
/*****************************************************************************/

#include <cstdio>
#include <cstdlib>
int main(void)
{
	int *x = (int *)malloc(sizeof(int));
	delete x;

	int *y = new int(3);
	free(y);


	/*
	student_t *s = new student();
	int *x = new int(12.6);
	delete x;

	*x = 3;

	printf("%d \n", *x);

	float *y = new float[15];
	delete[] y;
	*/
	return 0;
}
/*****************************************************************************/