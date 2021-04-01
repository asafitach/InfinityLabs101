#include <stdlib.h> /* malloc, free, system */
#include <stdio.h> /* printf */

#include "fsa.h"

#define RED "\033[1;31m" 
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"
#define PURPLE "\033[1;35m"
#define RESET "\033[0m" 


#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)

int main()
{
	void *memory_ptr = NULL;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	fsa_t *fsa_pool = NULL;
	size_t block_size = 6;
	size_t num_of_blocks = 3;	
	size_t suggested_size = FsaSuggestedSize(block_size, num_of_blocks);
	
	printf(PURPLE"\n\tFSA Test\n\n"WHITE);
	
	TEST("FsaSuggestedSize", suggested_size, 56);
	
	memory_ptr = malloc(suggested_size);
	if (NULL == memory_ptr)
    {
        return (1);
    }
    
	fsa_pool = FsaInit(memory_ptr, suggested_size, block_size);

	TEST("FsaInit", (fsa_pool == NULL), 0);
	
	TEST("FsaInit", FsaCountFreeBlocks(fsa_pool), 3);
	
	block1 = FsaAllocBlock(fsa_pool);	
	
	TEST("FsaAllocBlock1", ((size_t)block1 == (size_t)((char*)fsa_pool + 32)), 1);
	
	block2 = FsaAllocBlock(fsa_pool);
	
	TEST("FsaAllocBlock2", ((size_t)block2 == (size_t)((char*)fsa_pool + 40)), 1);	
	
	FsaFreeBlock(fsa_pool, block1);

	block3 = FsaAllocBlock(fsa_pool);
	
	TEST("FsaFreeBlock", ((size_t)block3 == (size_t)((char*)fsa_pool + 32)), 1);
	
	block1 = FsaAllocBlock(fsa_pool);	
	
	TEST("FsaAllocBlock3", ((size_t)block1 == (size_t)((char*)fsa_pool + 48)), 1);
	
	block1 = FsaAllocBlock(fsa_pool);	
	
	TEST("FsaAllocBlock (free blocks = 0)", (block1 == NULL), 1);
	
	free(memory_ptr);
	
	printf(PURPLE"\tEnd Test\n\n"WHITE);
	
	return (0);
}
