/**************--- reviwed by Naor ---*****************************************/
#include <stdio.h>/* printf, sprintf*/
#include <string.h>/*strlen, strcat*/
#include <stdlib.h>/* malloc, realloc, free */
#include <assert.h>/* assert */
#include "ex1.h"

/***********************--- PRINT ---******************************************/

status_t PrintInt (element_t const *new)
{
	printf("This is an integer: %d\n", *(int*)&(new->value));
	return(SUCCESS);
}
status_t PrintDouble (element_t const *new)
{
	printf("This is a double: %f\n", *(double*)&(new->value));
	return(SUCCESS);
}
status_t PrintStr (element_t const *new)
{
	printf("This is a string: %s\n", (char*)(new->value));
	return(SUCCESS);
}

/*************************--- ADD ---******************************************/

status_t AddInt (element_t *new, int const num)
{
	*(int*)&(new->value) += num;
	return(SUCCESS);
}
status_t AddDouble (element_t *new, int const num)
{
	*(double*)&(new->value) += num;
	return(SUCCESS);
}

size_t DigitCounter( int num)
{
	size_t size = 0;

	while(num)
	{
		size += 1;
		num /= 10;
	}
	return(size + 1);
}

status_t AddStr (element_t *new, int num)
{
	char *str = (char*)new->value;
	size_t size = DigitCounter(num);	

	char *str_to_add = (char*)malloc(size);
	assert(str_to_add != NULL);
	if( NULL == str_to_add)
	{
		return(FAIL);
	}

	sprintf(str_to_add, "%d", num);


	str = (char*)realloc (str, size + strlen(str));
	assert(str != NULL);
	if( NULL == str)
	{
		return(FAIL);
	}

	strcat(str, str_to_add);

	new->value = (void*)str;
	return(SUCCESS);
}

/************************--- FREE ---******************************************/

status_t FreeEmpty( element_t const *new)
{
	new = new;
	return(SUCCESS);
}
status_t FreeStr( element_t const *new)
{
	free(new->value);
	return(SUCCESS);
}

/*********************--- STRUCTS ---******************************************/

static const functions_t INT_FUNCS = 
{
    PrintInt,
    AddInt,
    FreeEmpty
};

static const functions_t DOUBLE_FUNCS = 
{
    PrintDouble,
    AddDouble,
    FreeEmpty
};

static const functions_t STR_FUNCS = 
{
    PrintStr,
    AddStr,
    FreeStr
};

/**************--- INITIALIZATION ---******************************************/

status_t InitInt(element_t *new, int const num)
{
	new->value = *(void**)&num;
	new->funcs = &INT_FUNCS;
	return(SUCCESS);
}
status_t InitDouble(element_t *new, double const num)
{
	new->value = *(void**)&num;
	new->funcs = &DOUBLE_FUNCS;
	return(SUCCESS);
}
status_t InitStr(element_t *new, char* str)
{
	new->value = (void*)str;
	new->funcs = &STR_FUNCS;
	return(SUCCESS);
}

/**************--- FUNCTION ---************************************************/

status_t PrintAll (element_t *arr, int const size)
{
	int index = 0;
	for(index = 0 ; index < size; index++)
	{
		arr[index].funcs->print_func(& arr[index]);
	}
	return (SUCCESS);
	
}

status_t AddAll (element_t *arr, int const size, int const add)
{
	int index = 0;
	status_t stat = SUCCESS;
	PrintAll(arr, size);
	printf("Add -->  -->  -->\n");
	for(index = 0 ; index < size; index++)
	{
		stat = arr[index].funcs->add_func(& arr[index], add);
	}
	PrintAll(arr, size);
	return (stat);
}

status_t FreeAll (element_t *arr, int const size)
{
	int index = 0;
	for(index = 0 ; index < size; index++)
	{
		arr[index].funcs->free_func(& arr[index]);
	}
	return (SUCCESS);
}



