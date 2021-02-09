#include "ex5.h"	/* PowerUp*/

/*get the power of 10 by n*/
float PowerUp(int n)
{
    float res = 1;
    float base = 10;
    int i = 0;
    
    if (n < 0)
    {
        n *= -1;
        base = 0.1;
    }
    
    for (i = 0; i < n; i++)
    {
        res *= base;
    }
    
    return res;
}


