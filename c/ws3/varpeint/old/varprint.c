#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "varprint.h"

size_t Count(char **arr)
{
	size_t count = 0;
	while(*(arr + count))
	{
		count++;
	}
	return(count);
}

/**************************************************/

void ArrayOfEnvVar(char **dest, char **src)
{
	size_t str = 0;
	size_t chr = 0;

	while(*(src + str))
	{
		while(*(chr + *(src + str)))
		{
			*(chr + *(str + dest))=*(chr + *(str + src));
			chr++;
		}
		chr=0;
		str++;
	}
	return;
}
 
/**************************************************/

void ToLowerToAll(char **env_arr, size_t size)
{
	size_t str = 0;
	size_t chr = 0;

	while(str < size - 1)
	{
		while(*(chr + *(env_arr + str)))
		{
			if( *(chr + *(env_arr + str)) > 64 && *(chr + *(env_arr + str)) < 91)
			{
				*(chr + *(str + env_arr)) = *(chr + *(env_arr + str)) + 32;
			}
			chr++;
		}
		chr=0;
		str++;
	}
	return;
}

/**************************************************/

void PrintAll(char **env_arr, size_t size)
{
	size_t str = 0;

	while(str < size - 1)
	{
		printf("%s \n", *(env_arr + str));
		str++;
	}
	return;
}

/**************************************************/

void Free(char **multi_arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	
	for(i = size - 1; i > 0; i--)
	{
		/*for(j = strlen(*(multi_arr + i)) + 1; j > 0; j--)
		{
			free(*(*(multi_arr + i) + j));
		}*/
		free(*(multi_arr + i));
	}
	
	free(multi_arr);

	return;
}

/*********************EOF**************************/

