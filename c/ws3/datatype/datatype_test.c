#include<stddef.h>/*size_t*/
#include<stdio.h>/*printf*/


int main()
{
	printf("the size of char is %lu \n", sizeof( char ));
	printf("the size of signed cahr is %lu \n", sizeof( signed char ));
	printf("the size of unsigned char is %lu \n", sizeof(  unsigned char));
	printf("the size of short is %lu \n", sizeof( short ));
	printf("the size of unsigned short is %lu \n", sizeof( unsigned short ));
	printf("the size of int is %lu \n", sizeof( int ));
	printf("the size of unsigned int is %lu \n", sizeof( unsigned int ));
	printf("the size of long is %lu \n", sizeof( long ));
	printf("the size of unsigned long is %lu \n", sizeof( unsigned long ));
	printf("the size of float is %lu \n", sizeof( float ));
	printf("the size of double is %lu \n", sizeof( double ));
	printf("the size of long double is %lu \n", sizeof( long double ));
	/*printf("the size of long long is %lu \n", sizeof( long long ));
	printf("the size of unsigned long long is %lu \n", sizeof( unsigned long long ));
	printf("the size of intmax_t is %lu \n", sizeof(  intmax_t));
	printf("the size of uintmax_t is %lu \n", sizeof( uintmax_t ));*/


	return 0;
}

	
