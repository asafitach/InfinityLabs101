#include <stdio.h>
#include "ex3.h"

int main()
{
	int i = 0;
	char c = '\0';
	long l = 0;
	char *ptr = "hello";
	
	
	printf("The size of int is %ld\n", SIZEOF(&i));
	printf("The size of char is %ld\n", SIZEOF(&c));
	printf("The size of long is %ld\n", SIZEOF(&l));
	printf("The size of pointer is %ld\n", SIZEOF(&ptr));
	
	return (0);
	
}
