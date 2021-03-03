/*****************        Reviewed by Rachel       **************************/
#include "ex3.h"

int IsLittleEndian()
{
	int a = 1;
	char *p = (char*)&a;
	if((*(p +1) - *p) < 0)
	{
		return(LITTLE);
	}
	return(BIG);
}


