#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/

#include "fsa.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST_ARE_EQUAL(name, expected, actual)\
	 printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
#define TEST_ARE_NOT_EQUAL(name, expected, actual)\
	  printf("%s: %s\n\n", name, actual != expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
	  

struct fsa
{
	size_t total_blocks;
	size_t block_size; 
	size_t num_of_free_blocks; 
	size_t next_free;/*0 if full*/
};


void FsaSuggestedSizeTest(); 
void FsaInitTest(); 
void FsaCountFreeBlocksTest(); 
void FsaAllocBlockTest(); 
void FsaFreeBlockTest(); 
	  
int main()
{
	FsaSuggestedSizeTest(); 
	FsaInitTest(); 
	FsaCountFreeBlocksTest(); 
	FsaAllocBlockTest(); 
	FsaFreeBlockTest(); 
	
	return 0; 
}


void FsaSuggestedSizeTest()
{
	printf(CYAN"\t FsaSuggestedSize Test\n\n"WHITE);

	TEST_ARE_EQUAL("FsaSuggestedSize Test1", FsaSuggestedSize(8, 10), 8 * 10 + sizeof(fsa_t)); 
	TEST_ARE_EQUAL("FsaSuggestedSize Test2", FsaSuggestedSize(5, 10), 8 * 10 + sizeof(fsa_t)); 
	
	printf(CYAN"\t FsaSuggestedSize Test End\n\n"WHITE);
}


void FsaInitTest()
{
	size_t total_size = FsaSuggestedSize(8, 10); 
	
	void *memory_ptr = malloc(total_size); 
	
	fsa_t *fsa = FsaInit(memory_ptr, total_size, 8); 
	
	printf(CYAN"\t FsaInit Test\n\n"WHITE);
	
	TEST_ARE_EQUAL("FsaInit Test1", (fsa ? 1:0), 1); 
	TEST_ARE_EQUAL("FsaInit Test2", *(char *)(fsa + 1), 0); 
	
	free(memory_ptr); 
	
	printf(CYAN"\t FsaInit Test End\n\n"WHITE);
}


void FsaCountFreeBlocksTest()
{
	size_t total_size = FsaSuggestedSize(8, 10); 
	
	void *memory_ptr = malloc(total_size); 
	
	printf(CYAN"\t FsaCountFreeBlocks Test\n\n"WHITE);
	
	TEST_ARE_EQUAL("FsaCountFreeBlocks Test1", FsaCountFreeBlocks(FsaInit(memory_ptr, total_size, 8)), 10); 
	
	free(memory_ptr); 
	
	printf(CYAN"\t FsaCountFreeBlocks Test End\n\n"WHITE);
}


void FsaAllocBlockTest()
{
	size_t total_size = FsaSuggestedSize(8, 4); 
	void *memory_ptr = malloc(total_size); 
	fsa_t *fsa = FsaInit(memory_ptr, total_size, 4); 
	void *first_block = FsaAllocBlock(fsa); 
	
	printf(CYAN"\t FsaAllocBlock Test\n\n"WHITE);

	TEST_ARE_EQUAL("FsaAllocBlock Test1 (count free blocks)", FsaCountFreeBlocks(fsa), 3); 
	TEST_ARE_EQUAL("Alloc Test2 checkoffset", fsa->next_free, (size_t)first_block - (size_t)fsa + 8); 
	
	FsaAllocBlock(fsa);
	
	FsaAllocBlock(fsa);
	
	FsaAllocBlock(fsa);
	
	TEST_ARE_EQUAL("Alloc Test3 allocate when full", (NULL == FsaAllocBlock(fsa) ? 0:1), 0); 
	TEST_ARE_EQUAL("FsaAllocBlock Test4 (count free blocks)", FsaCountFreeBlocks(fsa), 0); 
	
	free(memory_ptr); 
	
	printf(CYAN"\t FsaAllocBlock Test End\n\n"WHITE);
}


void FsaFreeBlockTest()
{
	size_t total_size = FsaSuggestedSize(8, 2); 
	
	void *memory_ptr = malloc(total_size); 
	
	fsa_t *fsa = FsaInit(memory_ptr, total_size, 2); 
	
	void *first_block = FsaAllocBlock(fsa); 
	void *second_block = FsaAllocBlock(fsa); 
	
	printf(CYAN"\t FsaFreeBlockTest Test\n\n"WHITE);

	FsaFreeBlock(fsa, first_block); 
	TEST_ARE_EQUAL("FsaFreeBlock Test1 (count free blocks)", FsaCountFreeBlocks(fsa), 1); 
	
	FsaFreeBlock(fsa, second_block); 
	TEST_ARE_EQUAL("FsaFreeBlock Test2 (count free blocks)", FsaCountFreeBlocks(fsa), 2); 
	
	FsaFreeBlock(fsa, second_block); 
	TEST_ARE_EQUAL("FsaFreeBlock Test3 free when empty", FsaCountFreeBlocks(fsa), 2); 
	
	TEST_ARE_EQUAL("allocate after free", FsaAllocBlock(fsa), second_block); 
	TEST_ARE_EQUAL("count free blocks after allocate", FsaCountFreeBlocks(fsa), 1); 
	
	TEST_ARE_EQUAL("allocate after free", FsaAllocBlock(fsa), first_block); 
	TEST_ARE_EQUAL("count free blocks when full", FsaCountFreeBlocks(fsa), 0); 
	
	free(memory_ptr); 
	
	printf(CYAN"\t FsaFreeBlockTest Test End\n\n"WHITE);
}
