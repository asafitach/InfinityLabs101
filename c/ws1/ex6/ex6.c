#include "ex6.h"	/* FlipNumber*/

/*recieves an number and flips its digits*/
int FlipNumber(int n)
{
    int flipped = 0;
    
    while (n) 
    {
        flipped *= 10;
	flipped += n % 10;
        n /= 10;
    }
    return (flipped);
}


