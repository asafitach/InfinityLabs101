#include <stdio.h> /* printf, sizeof */
#include <stdlib.h> /*calloc, free */
#include <string.h> /* memset, memcpy, memmove strcmp */
#include "mem.h"

typedef enum 
{
	SUCCESS,
	MALLOC_FAILED
}status_t;

void PrintError(size_t stat);
status_t MemSetTest();	
status_t MemCpyTest();	
status_t MemMoveTest();

int main()
{
	status_t ret_val = SUCCESS;
	
	ret_val = MemSetTest();
	PrintError(ret_val);
	
	ret_val = MemCpyTest();
	PrintError(ret_val);
	
	ret_val = MemMoveTest();
	PrintError(ret_val);
	
	return (0);
}


status_t MemSetTest()
{
	char c = 'w';
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
	char *str = "welcome, it's nice to see you!";
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
	size_t size = 31;
	size_t num_bytes = 9;
	int flag = 0;
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
	
	strcpy(str_cpy1, "welcome, it's nice to see you!");
	strcpy(str_cpy2, "welcome, it's nice to see you!");
	
	MemMove(str_cpy1 + 3, str_cpy1, num_bytes);
	memmove(str_cpy2 + 3, str_cpy2, num_bytes);	
	
	if (0 == strcmp(str_cpy1, str_cpy2))
	{
		flag = 1;
	}
		
	strcpy(str_cpy1, "welcome, it's nice to see you!");
	strcpy(str_cpy2, "welcome, it's nice to see you!");
	
	MemMove(str_cpy1, str_cpy1 + 3, num_bytes);
	memmove(str_cpy2, str_cpy2 + 3, num_bytes);	
	
	if ((0 == strcmp(str_cpy1, str_cpy2)) && (flag == 1))
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


void PrintError(size_t stat)
{
	if(stat == 	MALLOC_FAILED)
	{
		printf("\n\n\n\t\t\t>>>Allocation failed!<<<\n\n\n");
	}
}
