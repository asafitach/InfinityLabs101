#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include <unistd.h>
#include <stdio.h>


extern double global_double_first =0;

/******************************************************************************/
int ExternInt(int *x)
{
	*x = rand();
	return (4);
}
/********************************E.O.F*****************************************/
