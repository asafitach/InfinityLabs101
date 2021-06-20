/*****************        Reviewed by Fei       **************************/

#include<stdio.h>/*printf*/
#include"ex.h"

/*****************************************************************************/
static int bitlut_g[256];

/*****************************************************************************/

long Pow2( unsigned int x, unsigned int y)
{

	y = (1 << y);

	return( x * y);
}

/*****************************************************************************/

unsigned int IsPowOf2Itarate( unsigned int n)
{  
	if( n == 1)
	{
		return(0);
	}
	while (n > 1)
	{
		if ((n & 1) != 0)
		{
			return (0);
		}
		n = n >> 1;
	}

	return (1);
}

/*****************************************************************************/

unsigned int IsPowerOf2( unsigned int n)
{		
	return((n != 0) && ((n & (n - 1)) == 0));
}

/*****************************************************************************/

/* unsigned int AddOne(unsigned int n)
{
	unsigned int one = 1; 
	unsigned int carry = 0;

	while(one)
	{
		carry = (n & one);
		n = (n ^ one);
		one = carry << 1;
	}
	return(n);
} */
unsigned int AddOne(unsigned int n)
{
	unsigned int mask = 1;
	while ((n & mask))
	{
		n ^= mask;
		mask <<= 1;
	}

	return (n |= mask);
}
/*****************************************************************************/

void TreeBitsOn(unsigned int *numbers, unsigned int size)
{
	unsigned int count = 0;
	unsigned int index = 0;

	for(index = 0; index < size; index++)
	{
		count = CountBits(*(numbers + index));

		if(count == 3)
		{
			printf("This number has 3 bits on: %u \n", *(numbers + index));
		}
	}
	return;
}

/*****************************************************************************/

unsigned int CountBits(unsigned int n)
{
	unsigned int count = 0;

	while(n)
	{
		if(1 == (n & 1))
		{
			count++;
		}
		n = (n >> 1);
	}

	return(count);
}

/*****************************************************************************/

unsigned char MirrorBitsLoop(unsigned char original)
{
	unsigned char mirror = 0;
	int i;

	for(i = 0; i < 8; i++)
	{
		mirror <<= 1;
		mirror |= (original & 1);
		original >>= 1;
	}

	return(mirror);
}

/*****************************************************************************/

unsigned char MirrorBits(unsigned char in)
{
	in = (in & 0xF0) >> 4 | (in & 0x0F) << 4;
   	in = (in & 0xCC) >> 2 | (in & 0x33) << 2;
	in = (in & 0xAA) >> 1 | (in & 0x55) << 1;

return (in);
}

/*****************************************************************************/

unsigned char BitsOn2N6(unsigned char n) 
{	
	return((n & 2) && (n & 32));
}

/*****************************************************************************/

unsigned char BitsOn2O6(unsigned char n)
{
	return((n & 2) || (n & 32));
}

/*****************************************************************************/

unsigned char SwapBits35(unsigned char n)
{
	int b3 = 0;
	int b5 = 0;
	unsigned char swap_mask = 0;
	unsigned char res = 0;
	
	b3 = (n >> 2) & 1;
	b5 = (n >> 4) & 1;
	
	swap_mask = b3 ^ b5;
	swap_mask = (swap_mask << 2) | (swap_mask << 4);
	
	res = n ^ swap_mask;
	return(res);
}

/*****************************************************************************/

unsigned char DivideBy16(unsigned char n)
{
	n >>= 4;
	n <<= 4;
	return(n);
}

/*****************************************************************************/

void SwapValue(unsigned int *x, unsigned int *y)
{
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
	return;
}

/*****************************************************************************/

void PrintFloatBits(float f)
{
	int count;
	unsigned int n;
	unsigned int *x = (unsigned int*)&f;

	for(count = 31; count > -1; count--)
	{
		n = (*x) >> count;
		n = n & 1;
		printf("%u", (n));
	}
	printf("\n");

	return;
}

/*****************************************************************************/

void BitLut() 
{
    int i = 0;

    for (i = 0; i < 256; i++)
    { 
        bitlut_g[i] = (i & 1) + bitlut_g[i / 2]; 		/*define the lut*/
    } 
    
    return;
} 
 
/*****************************************************************************/

int CountBitsOn(unsigned int n) 
{ 
    BitLut();

    return (bitlut_g[n & 0xff] +				/*right nible*/
            bitlut_g[(n >> 8) & 0xff] +		    /*center right nible*/
            bitlut_g[(n >> 16) & 0xff] + 		/*center left nible*/
            bitlut_g[n >> 24]); 				/*left nible*/
}
/***********************************EOF***************************************/
