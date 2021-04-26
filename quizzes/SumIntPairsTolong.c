#include <stdio.h>
#include <stddef.h>
#include <assert.h>

long *SumIntPairsToLongs(int ints[], size_t numofelements);

int main()
{
	int ints[] = {1,2,3,4,0xFF,0x7FFFFFFF};
	long *longs = NULL;
	
	longs = SumIntPairsToLongs(ints, 6);
	return 0;
}

long *SumIntPairsToLongs(int ints[], size_t numofelements)
{
	size_t i = 0;
	assert(NULL != ints);
	assert(0 == numofelements % 2);
	
	for (i = 0; i < numofelements; i +=2)
	{
		*(long*)&ints[i] = (long)ints[i] + ints[i + 1];
	}
	return (long*)ints;
}
