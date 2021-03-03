#include <stdio.h>
#include "bit_array.h"

void TestBitArrSetBitOn();
void TestBitArrSetBitOff();
void TestBitArrSetBit();
void TestBitArrFlipBit();
void TestBitArrIsBitOn();
void TestBitArrIsBitOff();
void TestBitArrGetBit();
void TestBitArrCountBitsOn();
void TestBitArrCountBitsOff();
void TestBitArrSetAll();
void TestBitArrUnSetAll();
void TestBitArrMirror();
void TestBitArrRotateRight();
void TestBitArrRotateLeft();
void TestBitArrShiftRight();
void TestBitArrShiftLeft();
void TestBitArrArrToString();

int main()
{
	TestBitArrSetBitOn();
	TestBitArrSetBitOff();
	TestBitArrSetBit();
	TestBitArrFlipBit();
	TestBitArrIsBitOn();
	TestBitArrIsBitOff();
	TestBitArrGetBit();
	TestBitArrCountBitsOn();
	TestBitArrCountBitsOff();
	TestBitArrSetAll();
	TestBitArrUnSetAll();
	TestBitArrMirror();
	TestBitArrRotateRight();
	TestBitArrRotateLeft();
	TestBitArrShiftRight();
	TestBitArrShiftLeft();
	TestBitArrArrToString();

	return (0);
}

void TestBitArrSetBitOn()
{
	char buffer[65];
	bitarray_t test = 0;
	printf(" TestBitArrSetBitOn  \n");
	printf("original: \n%s\n",BitArrArrToString(test, buffer)); 
	test = BitArrSetBitOn(test, 3);
	printf("bit num 3 should be on: \n%s\n\n", BitArrArrToString(test, buffer));
}


void TestBitArrSetBitOff()
{
	char buffer[65];
	bitarray_t test = 0xffffffffffffffff;
	printf(" TestBitArrSetBitOff  \n");
	printf("original: \n%s\n",BitArrArrToString(test, buffer)); 
	test = BitArrSetBitOff(test, 3);
	printf("bit num 3 should be off: \n%s\n\n", BitArrArrToString(test, buffer));
	
}

void TestBitArrSetBit()
{
	char buffer[65];
	bitarray_t test = 0;
	printf("  TestBitArrSetBit \n");
	printf("original: \n%s\n",BitArrArrToString(test, buffer)); 
	test = BitArrSetBit(test, 3, 8);
	printf("bit num 3 should be on: \n%s\n\n", BitArrArrToString(test, buffer));
	
}

void TestBitArrFlipBit()
{
	char buffer[65];
	bitarray_t test = 0;
	printf("  TestBitArrFlipBit \n");
	printf("original: \n%s\n",BitArrArrToString(test, buffer)); 
	test = BitArrFlipBit(test, 3);
	printf("bit num 3 should be on: \n%s\n\n", BitArrArrToString(test, buffer));
	
}

void TestBitArrIsBitOn()
{
	bitarray_t test = 0xf;
	printf(" TestBitArrIsBitOn  \n");
	printf("1 means success:   %d\n\n", BitArrIsBitOn(test, 2));
	
}

void TestBitArrIsBitOff()
{
	bitarray_t test = 0xf;
	printf("  TestBitArrIsBitOff \n");
	printf("0 means success:   %d\n\n", BitArrIsBitOff(test, 2));
	
}

void TestBitArrGetBit()
{
	bitarray_t test = 0xf;
	bitstate_t stat = BitArrGetBit(test, 2);
	printf(" TestBitArrGetBit  \n");
	if(stat == BIT_ON)
	{
		printf("success\n\n");
	}
	else
	{
		printf("failed\n\n");
	}
}


void TestBitArrCountBitsOn()
{
	bitarray_t test = 0xf0c3;
	printf("  TestBitArrCountBitsOn \n");
	printf("sould print 8:   %lu\n\n", BitArrCountBitsOn(test));
	
}

void TestBitArrCountBitsOff()
{
	bitarray_t test = 0xf;
	printf(" TestBitArrCountBitsOff  \n");
	printf("sould print 60:   %lu\n\n", BitArrCountBitsOff(test));
	
}

void TestBitArrSetAll()
{
	char buffer[65];
	bitarray_t test = BitArrSetAll();
	printf(" TestBitArrSetAll  \n");
	printf("\n%s\n\n", BitArrArrToString(test, buffer));
	
}

void TestBitArrUnSetAll()
{
	char buffer[65];
	bitarray_t test = BitArrUnSetAll();
	printf("  TestBitArrUnSetAll \n");
	printf("\n%s\n\n", BitArrArrToString(test, buffer));
	
}

void TestBitArrMirror()
{
	char buffer[65];
	bitarray_t test = 0xf0f0f0f0a5a5c3c3;
	printf("  TestBitArrMirror \n");
	printf("\n%s\n\n", BitArrArrToString(test, buffer));
	test = BitArrMirror(test);
	printf("\n%s\n\n", BitArrArrToString(test, buffer));	
}

void TestBitArrRotateRight()
{
	char buffer[65];
	bitarray_t test = 0xffff;
	printf(" TestBitArrRotateRight  n = 23\n");
	printf("\n%s\n\n", BitArrArrToString(test, buffer));
	test = BitArrRotateRight(test, 87);
	printf("\n%s\n\n", BitArrArrToString(test, buffer));
}

void TestBitArrRotateLeft()
{
	char buffer[65];
	bitarray_t test = 0xffff;
	printf("  TestBitArrRotateLeft n = 23 \n");
	printf("\n%s\n\n", BitArrArrToString(test, buffer));
	test = BitArrRotateLeft(test, 87);
	printf("\n%s\n\n", BitArrArrToString(test, buffer));
	
}

void TestBitArrShiftRight()
{
	char buffer[65];
	bitarray_t test = 0xffff;
	printf("  TestBitArrShiftRight n = 3 \n");
	printf("\n%s\n\n", BitArrArrToString(test, buffer));
	test = BitArrShiftRight(test, 67);
	printf("\n%s\n\n", BitArrArrToString(test, buffer));
}

void TestBitArrShiftLeft()
{
	char buffer[65];
	bitarray_t test = 0xffff;
	printf("  TestBitArrShiftLeft n = 3 \n");
	printf("\n%s\n\n", BitArrArrToString(test, buffer));
	test = BitArrShiftLeft(test, 67);
	printf("\n%s\n\n", BitArrArrToString(test, buffer));
}

void TestBitArrArrToString()
{
	char buffer[65];
	bitarray_t test = 0xffff00fff00;
	printf(" TestBitArrArrToString  \n");
	printf("\n%s\n\n", BitArrArrToString(test, buffer));	
}

	

