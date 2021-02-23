#include <stdio.h>
#include "ex4.h"

int main()
{

	struct check{
	int check_i;
	long check_l;
	long check_2;
	};
	
	
	printf("The size of struct (int long long) is %ld\n", SIZEOF2( struct check));
	printf("The size of int is %ld\n", SIZEOF2( int));

	
	return (0);
	
}
