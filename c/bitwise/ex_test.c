#include<stdio.h>/*printf*/
#include"ex.h"

int main()
{
	unsigned int x, y, n, ans = 0;
	unsigned char b, c =16;
	unsigned int arr[9]={5, 9, 15, 12, 7, 2, 10, 55, 8};
	float f = 0;
	x = 3;
	y = 0;
	n = 16;


/****************************** test 1-4 ************************************/
	ans = Pow2(x,y);
	printf("x=%u\ny=%u\nx*2^y=%u\n", x, y, ans);
	
	ans = IsPowOf2Itarate(n);
	printf("%u is a power of 2? %u\n", n, ans);
	
	ans = IsPowerOf2(n);
	printf("%u is a power of 2? %u\n", n, ans);
	
	ans = AddOne(n);
	printf("%u+1=%u\n", n, ans);

	TreeBitsOn(arr, 9);

/******************************* test 5-6 ************************************/
	
	c = 129;
	b = MirrorBitsLoop(c);
	printf("mirror of %d is %d\n", c, b);

	c = 129;
	b = MirrorBits(c);
	printf("mirror of %d is %d\n", c, b);

	b = BitsOn2N6( c);
	printf("in %d is the 2'th and 6'th both on? %d\n", c, b);

	c = 2;
	b = BitsOn2O6( c);
	printf("in %d is the 2'th and 6'th  on even" 
	"if its only one of them? %d\n", c, b);
	
	c = 16;
	b = SwapBits35(c);
	printf("swap bit nu 3 with bit nu 5 original is: %d, swap: %d\n", c, b);

/********************************* test 7-11 *********************************/
	c = 85;
	b = DivideBy16(c);
	printf("the closest number to %d that devide by 16 is: %d \n", c, b);
	
	x = 2;
	y = 6;
	printf("x=%u y=%u\nnow swap!\n", x, y);
	SwapValue(&y, &x);
	printf("x=%u y=%u\n", x, y);
	
	x = 23;
	ans = CountBits(x);
	printf("in %u the number of set bits is:%u\n", x, ans);

	x = 7;
	ans = CountBitsOn(x);
	printf("in %u the number of set bits is:%u\n", x, ans);


	f = 0.004;
	printf("The binary interpration of %f is:\n", f);
	PrintFloatBits((unsigned int *)&f);


	return 0;
}

