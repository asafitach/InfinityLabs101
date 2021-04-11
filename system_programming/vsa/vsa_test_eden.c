#include <stdio.h> /* printf */
#include <stdlib.h> /* system */
#include <sys/types.h> /* ssize_t */

#include "vsa.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

/*****************************************************************************/

#define TEST(name, actual, expected)\
    				printf("%s: %s\n\n", name, actual == expected ?\
     				GREEN"Pass"WHITE : RED"Fail"WHITE)
    
/*****************************************************************************/

int TestDebug();
int TestRelease();

void VsaPrint(vsa_t *vsa);
#define END_MARK 0x90909090

int main()
{
    system("clear");
    
	#ifndef NDEBUG
    return TestDebug();
    #endif
    
    #ifdef NDEBUG
    return TestRelease();
    #endif
}

int TestDebug()
{
	void *memory = NULL;
	vsa_t *vsa = NULL;
	size_t *res = NULL;
	size_t size = 0;
	
    printf(CYAN"\tTest Debug\n\n"WHITE);
     
    memory = (void*)calloc(24 + 48, 1);
    if(NULL == memory)
    {
    	return (1);
    }
    
    vsa = VsaInit(memory, 24 + 48);
    TEST("VsaInit(memory, 24 + 48)", (vsa != NULL), 1);
    VsaPrint(vsa);
    
	size = VsaLargestChunkAvailable(vsa);
    TEST("VsaLargestChunkAvailable(vsa)", size, 6);
    printf("%lu\n", size);
	
	res = (size_t*)VsaAlloc(vsa, 8);
	*res = 11111;
	size = VsaLargestChunkAvailable(vsa);
	TEST("VsaAlloc(vsa, 8)", size, 3);
	    printf("%lu\n", size);
	
    VsaPrint(vsa);
	
	res = (size_t*)VsaAlloc(vsa, 8);
	*res = 11111;
	size = VsaLargestChunkAvailable(vsa);
    printf("%lu\n", size);
	TEST("VsaAlloc(vsa, 8)", size, 0);
        
    VsaPrint(vsa);
    
    VsaFree(res);
    size = VsaLargestChunkAvailable(vsa);
	TEST("VsaFree(res)", size, 3);
    printf("%lu\n", size);
    	
    VsaPrint(vsa);
 	
    res = (size_t*)VsaAlloc(vsa, 24);
	*res = 11111;
	size = VsaLargestChunkAvailable(vsa);
    printf("%lu\n", size);
	TEST("VsaAlloc(vsa, 24)", size, 0);
    
    VsaPrint(vsa);
	
    printf(CYAN"\tEnd Test\n\n"WHITE); 
    
    free(memory);
    return (0);
}

int TestRelease()
{
	void *memory = NULL;
	vsa_t *vsa = NULL;
	size_t *res = NULL;
	size_t size = 0;
	
    printf(CYAN"\tTest Release\n\n"WHITE);
     
    memory = (void*)calloc(16 + 56, 1);
    if(NULL == memory)
    {
    	return (1);
    }
    
    vsa = VsaInit(memory, 16 + 56);
    TEST("VsaInit(memory, 16 + 56)", (vsa != NULL), 1);
    VsaPrint(vsa);
    
	size = VsaLargestChunkAvailable(vsa);
	printf("Largest Available: %lu. \n", size);
    TEST("VsaLargestChunkAvailable(vsa)", size, 56);
	
	res = (size_t*)VsaAlloc(vsa, 8);
	*res = 11111;
	size = VsaLargestChunkAvailable(vsa);
	TEST("VsaAlloc(vsa, 8)", size, 40);
	
    VsaPrint(vsa);
	
	res = (size_t*)VsaAlloc(vsa, 8);
	*res = 11111;
	size = VsaLargestChunkAvailable(vsa);
	TEST("VsaAlloc(vsa, 8)", size, 24);
    
    VsaPrint(vsa);
    
    VsaFree(res);
    size = VsaLargestChunkAvailable(vsa);
	TEST("VsaFree(res)", size, 40);
	
    VsaPrint(vsa);
 	
    res = (size_t*)VsaAlloc(vsa, 24);
	*res = 11111;
	size = VsaLargestChunkAvailable(vsa);
	TEST("VsaAlloc(vsa, 24)", size, 8);
    
    VsaPrint(vsa);
	
    printf(CYAN"\tEnd Test\n\n"WHITE); 
    
    free(memory);
    return (0);
}

void VsaPrint(vsa_t *vsa)
{
	size_t *ptr = (size_t*)vsa;
	int end = 0;
	
	while(!end)
	{		
		if(END_MARK == *ptr)
		{
			end = 1;
		}
		
		printf("%p: %d\n", (void*)ptr, (int)*ptr);
		ptr++;
	}
	printf("\n");
}
