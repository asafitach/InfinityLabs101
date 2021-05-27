#include <assert.h>/* assert */
#include "bit_array.h"

#define ARR_SIZE (64)

bitarray_t BitArrSetBitOn(bitarray_t bitarray, size_t bit_index)
{
	assert(bit_index < ARR_SIZE);

	return (bitarray |= ((bitarray_t)1 << bit_index));
}

bitarray_t BitArrSetBitOff(bitarray_t bitarray, size_t bit_index)
{
	assert(bit_index < ARR_SIZE);
	bitarray |= ((bitarray_t)1 << bit_index);
	bitarray ^= ((bitarray_t)1 << bit_index);

	return (bitarray);
}

bitarray_t BitArrSetBit(bitarray_t bitarray, size_t bit_index, int set_to)
{
	assert(bit_index < ARR_SIZE);
	
	if(set_to == 0)
	{
		bitarray = BitArrSetBitOff(bitarray, bit_index);
	}
	else
	{
		bitarray = BitArrSetBitOn(bitarray, bit_index);
	}

	return (bitarray);
}
	
bitarray_t BitArrFlipBit(bitarray_t bitarray, size_t bit_index)
{
	assert(bit_index < ARR_SIZE);

	return(bitarray ^ ((bitarray_t)1 << bit_index));
}

bitstate_t BitArrGetBit(bitarray_t bitarray, size_t bit_index)
{
	assert(bit_index < ARR_SIZE);
	if((bitarray & ((bitarray_t)1 << bit_index)) == 0)
	{
		return(BIT_OFF);
	}
	else
	{
		return (BIT_ON);
	}
}

int BitArrIsBitOn(bitarray_t bitarray, size_t bit_index)
{
	assert(bit_index < ARR_SIZE);
	
	if(BitArrGetBit(bitarray, bit_index) == BIT_ON)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

int BitArrIsBitOff(bitarray_t bitarray, size_t bit_index)
{
	assert(bit_index < ARR_SIZE);

	if(BitArrGetBit(bitarray, bit_index) == BIT_OFF)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

size_t BitArrCountBitsOn(bitarray_t bitarray)
{
	size_t count = 0;

	while(bitarray)
	{
		bitarray &= (bitarray -1);
		count++;
	}
	
	return(count);
}
	

size_t BitArrCountBitsOff(bitarray_t bitarray)
{
	return (ARR_SIZE - BitArrCountBitsOn(bitarray));
}

bitarray_t BitArrSetAll()
{
	return((bitarray_t)0xffffffffffffffff);
}

bitarray_t BitArrUnSetAll()
{
	return((bitarray_t)0);
}

bitarray_t BitArrMirror(bitarray_t bitarray)
{
	bitarray = (bitarray & 0xffffffff00000000) >> 32 | (bitarray & 0x00000000ffffffff) << 32;
	bitarray = (bitarray & 0xffff0000ffff0000) >> 16 | (bitarray & 0x0000ffff0000ffff) << 16;
	bitarray = (bitarray & 0xff00ff00ff00ff00) >> 8 | (bitarray & 0x00ff00ff00ff00ff) << 8;
	bitarray = (bitarray & 0xf0f0f0f0f0f0f0f0) >> 4 | (bitarray & 0x0f0f0f0f0f0f0f0f) << 4;
   	bitarray = (bitarray & 0xcccccccccccccccc) >> 2 | (bitarray & 0x3333333333333333) << 2;
	bitarray = (bitarray & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitarray & 0x5555555555555555) << 1;
	
	return(bitarray);
}


bitarray_t BitArrRotateRight(bitarray_t bitarray, size_t n)
{
	bitarray_t tmp = 0;
	
	n %= ARR_SIZE;
	tmp = bitarray << (ARR_SIZE - n);
	bitarray >>= n;
	
	return (bitarray |= tmp);
}


bitarray_t BitArrRotateLeft(bitarray_t bitarray, size_t n)
{
	bitarray_t tmp = 0;
	
	n %= ARR_SIZE;
	tmp = bitarray >> (ARR_SIZE - n);
	bitarray <<= n;
	
	return (bitarray |= tmp);
}

bitarray_t BitArrShiftRight(bitarray_t bitarray, size_t n)
{
	return(bitarray >> (n % ARR_SIZE));
}

bitarray_t BitArrShiftLeft(bitarray_t bitarray, size_t n)
{
	return(bitarray << (n % ARR_SIZE));
}

char *BitArrArrToString(bitarray_t bitarray, char *buffer)
{
	size_t index = 0;
	assert(NULL != buffer);
	for(index = 0; index < ARR_SIZE; index++)
	{
		*(buffer + index) = (char)('0' + (BitArrIsBitOn(bitarray, ARR_SIZE - index - 1)));
	}
	*(buffer + ARR_SIZE) = '\0';
	
	return(buffer);
}
	


