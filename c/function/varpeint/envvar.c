#include<stdio.h>/*printf*/
#include<stdlib.h>/*free*/
#include<string.h>/*strcpy, strlen*/
#include "envvar.h"

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

	for(str = 0; *(src + str); str++)
	{
		strcpy(*(dest+str), *(src + str));
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
			if( (*(chr + *(env_arr + str)) >= 'A') && (*(chr + *(env_arr + str)) <= 'Z'))
			{
				*(chr + *(str + env_arr)) = *(chr + *(env_arr + str)) + 'a'-'A';
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
	
	for(i = size ; i > 0; i--)
	{

		free(*(multi_arr + i - 1));
		*(multi_arr + i - 1) = NULL;
	}


	return;
}

/*********************EOF**************************/

