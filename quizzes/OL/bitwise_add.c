#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include <stdio.h>

/******************************************************************************/

unsigned int BitwiseAdd(unsigned int num)
{
	unsigned int mask = 1;
	
	while (mask & num)
	{
		num ^= mask;
		mask <<=1;
	}
	
	num ^= mask;
	
	return (num);
}


int main()
{
	unsigned int x = 12;
	
	printf("%d + 1 = %d", x, BitwiseAdd(x));
	
	return (0);
}
/********************************E.O.F*****************************************/
