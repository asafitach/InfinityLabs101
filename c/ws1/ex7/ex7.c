#include "ex7.h"	/* swaping */

/*swaps the value of 2 variables*/
void swaping(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


