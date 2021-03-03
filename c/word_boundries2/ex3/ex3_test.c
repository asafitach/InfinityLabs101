/*****************        Reviewed by Rachel       **************************/
#include <stdio.h>/*printf*/
#include "ex3.h"

int main()
{
endian ans = IsLittleEndian();

if(IS_LITTLE_ENDIAN && (ans == LITTLE))
{
	printf("Little Endian\n");
}
else
{
	printf("Big Endian\n");
}	

return 0;
}
