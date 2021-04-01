/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h> 

/*****************************************************************************/

#include "fsa.h"

/*****************************************************************************/

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define WHITE "\033[0m"

#define TEST_ARE_EQUAL(name, actual, expected)\
     printf("%s\n%s\n\n", name, actual == expected ? GREEN"PASSED"WHITE : RED"FAILED"WHITE)
     
#define TEST_ARE_NOT_EQUAL(name, actual, expected)\
     printf("%s\n%s\n\n", name, actual != expected ? GREEN"PASSED"WHITE : RED"FAILED"WHITE)

/*****************************************************************************/

void TestFsaInit();
void TestFsaSuggestedSize();
void TestFsaAllocAndFreeBlock();
void TestFsaCountFreeBlocks();

/*****************************************************************************/

int main()
{
	TestFsaInit();
	TestFsaSuggestedSize();
	TestFsaAllocAndFreeBlock();
	
	return (0);	
}

/*****************************************************************************/

void TestFsaInit()
{
	fsa_t *fsa = NULL;
	
	size_t suggested_size = 0;
	size_t block_size = 5;
	size_t amount_of_blocks = 4;
	
	suggested_size = FsaSuggestedSize(block_size, amount_of_blocks);
	fsa = malloc(suggested_size);
	fsa = FsaInit(fsa, suggested_size, block_size);

	TEST_ARE_NOT_EQUAL("TestFsaInit", fsa, NULL);	
	
	free(fsa);
	fsa = NULL;	
}

/*****************************************************************************/

void TestFsaSuggestedSize()
{
	size_t suggested_size = 0;
	size_t block_size = 10;
	size_t amount_of_blocks = 4;
	
	suggested_size = FsaSuggestedSize(block_size, amount_of_blocks);

	TEST_ARE_EQUAL("TestFsaSuggestedSize", suggested_size, 96);			
}

/*****************************************************************************/

void TestFsaAllocAndFreeBlock()
{
	fsa_t *fsa = NULL;
	
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;
		
	size_t suggested_size = 0;
	size_t block_size = 10;
	size_t amount_of_blocks = 4;
	
	suggested_size = FsaSuggestedSize(block_size, amount_of_blocks);
	fsa = malloc(suggested_size);
	fsa = FsaInit(fsa, suggested_size, block_size);
	
	block1 = FsaAllocBlock(fsa);
	block2 = FsaAllocBlock(fsa);
	block3 = FsaAllocBlock(fsa);
	
	TEST_ARE_EQUAL("TestAllocAndFreeBlock1", (size_t)block3 - (size_t)fsa, 64);
	
	FsaFreeBlock(fsa, block2);
	FsaFreeBlock(fsa, block1);
	
	block4 = FsaAllocBlock(fsa);
	block5 = FsaAllocBlock(fsa);
		
	TEST_ARE_EQUAL("TestAllocAndFreeBlock2", (size_t)block4 - (size_t)fsa, 32);	
	TEST_ARE_EQUAL("TestAllocAndFreeBlock3", (size_t)block5 - (size_t)fsa, 48);		
	
	FsaFreeBlock(fsa, block3);
	block1 = FsaAllocBlock(fsa);
	
	TEST_ARE_EQUAL("TestAllocAndFreeBlock", (size_t)block1 - (size_t)fsa, 64);				
	
	free(fsa);
	fsa = NULL;			
}

/*****************************************************************************/


