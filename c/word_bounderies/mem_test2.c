#include <stdio.h> /* printf, sizeof */
#include <stdlib.h> /*calloc, free */
#include <string.h> /* memset, memcpy, memmove strcmp */
#include "mem.h"

typedef enum 
{
	SUCCESS,
	MALLOC_FAILED
}status_t;

status_t MemSetTest();	
status_t MemCpyTest();	
status_t MemMoveTest();

int main()
{
	MemSetTest();
	
	MemCpyTest();
	
	MemMoveTest();
	
	return (0);
}


status_t MemSetTest()
{
	char c = 'f';
	size_t size = 23;
	char *str_cpy1 = (char*)calloc(size + 1, sizeof(char));
	char *str_cpy2 = NULL;
	
	if (NULL == str_cpy1)
	{
		return (MALLOC_FAILED);
	}
	
	str_cpy2 = (char*)calloc(size + 1, sizeof(char));
	
	if (NULL == str_cpy2)
	{
		free(str_cpy1);
		return (MALLOC_FAILED);
	}
	
	MemSet(str_cpy1, c, size);
	memset(str_cpy2, c, size);
	
	if (0 == strcmp(str_cpy1, str_cpy2))
	{
		printf("MemSet function - succeeded\n");
	}
	else 
	{
		printf("MemSet function - failed\n");
	}
		
	free(str_cpy1);	
	free(str_cpy2);	

	return (SUCCESS);
} 

status_t MemCpyTest()
{
	size_t size = 10;
	char *str = "hello world";
	char *str_cpy1 = (char*)calloc(size + 1, sizeof(char));
	char *str_cpy2 = NULL;
	
	if (NULL == str_cpy1)
	{
		return (MALLOC_FAILED);
	}
	
	str_cpy2 = (char*)calloc(size + 1, sizeof(char));
	
	if (NULL == str_cpy2)
	{
		free(str_cpy1);
		return (MALLOC_FAILED);
	}
	
	MemCpy(str_cpy1, str, size);
	memcpy(str_cpy2, str, size);
	
	if (0 == strcmp(str_cpy1, str_cpy2))
	{
		printf("MemCpy function - succeeded\n");
	}
	else 
	{
		printf("MemCpy function - failed\n");
	}
		
	free(str_cpy1);	
	free(str_cpy2);	

	return (SUCCESS);
}


status_t MemMoveTest()
{
	size_t size = 15;
	size_t num_bytes = 9;
	char *str_cpy1 = (char*)calloc(size + 1, sizeof(char));
	char *str_cpy2 = NULL;
	
	if (NULL == str_cpy1)
	{
		return (MALLOC_FAILED);
	}
	
	str_cpy2 = (char*)calloc(size + 1, sizeof(char));
	
	if (NULL == str_cpy2)
	{
		free(str_cpy1);
		return (MALLOC_FAILED);
	}
	
	strcpy(str_cpy1, "hello world!");
	strcpy(str_cpy2, "hello world!");
	
	MemMove(str_cpy1 + 3, str_cpy1, num_bytes);
	memmove(str_cpy2 + 3, str_cpy2, num_bytes);
	
	
	if (0 == strcmp(str_cpy1, str_cpy2))
	{
		printf("MemMove function - succeeded\n");
	}
	else 
	{
		printf("MemMove function - failed\n");
	}
		
	free(str_cpy1);	
	free(str_cpy2);	

	return (SUCCESS);
}
