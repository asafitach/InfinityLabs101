#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include <stdio.h>
#include <string.h>

#define WORD_SIZE 8
/******************************************************************************/
int Coupling(unsigned char chr)
{
/* 	size_t index = 0;
	size_t count = 0;
	int check = chr & 1;
	
	chr >>= 1;
	
	for (index = 1; index < WORD_SIZE; index++)
	{
		if(check == (chr & 1))
		{
			count++;
		}
		check = chr & 1;
		chr >>= 1;
	}
	
	return (count); */

	char mask1 = 0x1;
	char mask2 = 0x2;
	size_t count = 0;

	for (; mask1 != (char)0x80; mask1 <<= 1, mask2 <<= 1)
	{
		count += (mask1 & chr) && (mask2 & chr);
	}
	
	return (count);
}

int CountSetBits(unsigned char chr)
{
/* 	int count = 0;

	while (chr != 0)
	{
		chr &= (chr - 1);
		count++;
	}
	
	return (count); */

	char lut[16] = {0, 1, 1, 2,
					1, 2, 2, 3,
					1, 2, 2, 3,
					2, 3, 3, 4};
	return((int)(lut[chr & 0xf] + lut[chr & 0x0f]));
}

int main()
{
	unsigned char chr = 0xeb;
	char check = 0xfe;
	printf("the number of couple bits in 111001011 is: %d\n", Coupling(chr));
	
	printf("the number of bits on in 111001011 is: %d\n", CountSetBits(chr));
	
	printf("%d --> %d\n", check, check >> 1);

	return (0);
}
/********************************E.O.F*****************************************/
