/**************--- reviwed by Naor ---*****************************************/
#include <string.h>/* strcpy */
#include <stdio.h> /* printf */
#include <stdlib.h>/* malloc */
#include <assert.h>/*assert*/
#include "ex1.h"

int main()
{

	status_t stat = SUCCESS;
	element_t array_of_ele[3];
	int test_int = 7;
	double test_double = 4.2;
	char *check_str = (char*) malloc(10*sizeof(char));
	assert(check_str != NULL);
	strcpy(check_str, "hello");

/**************--- INITIALIZATION ---******************************************/

	InitInt(array_of_ele, test_int);
	InitDouble(array_of_ele+1, test_double);
	InitStr(array_of_ele + 2, check_str);

/**************--- FUNCTION ---************************************************/

	stat = AddAll(array_of_ele, 3, 5);
	FreeAll(array_of_ele, 3);
	
	if(stat == FAIL)
	{
		printf("\n\nFail to allocate data \n\n");
	}


	return 0;
}
 
