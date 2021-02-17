#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"envvar.h"

int main( int argc, char **argv, char **envp)
{
	char **buffer = NULL;
	size_t size = 0;
	size_t i = 0;
	
	if(argc > 1)
	{
		printf("Argument with no use: %s", *(argv + 1));
	}
	
/*creating a buffer */	
	
	size = Count(envp);
	buffer = (char**)malloc(size * sizeof(char*));
	if(buffer == 0)
	{
	printf("allocation failed\n");
	}
	

	i = 0;
	while(*(envp + i))
	{	
		*(buffer + i)=(char*)malloc((strlen(*(envp + i)) + 1)*(sizeof(char)));
		i++;
		if(buffer == 0)
		{
			printf("allocation failed\n");
			Free(buffer, i);
		}
				
	}


	

	ArrayOfEnvVar(buffer, envp);
	ToLowerToAll(buffer, size);
	PrintAll(buffer, size);
	
	Free(buffer, size);
	
	free(buffer);

	return (0);
}

