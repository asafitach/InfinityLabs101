#include <stdio.h> /*printf*/
#include <stdlib.h>/*malloc, free*/

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)

#define TEST_NOT(str, real, expected) (real != expected ?\
							 	  printf(GREEN"%sSUCCESS\n"RESET, str) :\
							 	  printf(RED"%sFAIL\n"RESET, str))

#define TEST(str, real, expected) (real == expected ?\
							 	  printf(GREEN"%sSUCCESS\n"RESET, str) :\
							 	  printf(RED"%sFAIL\n"RESET, str))

#define RED "\033[1;4;7;31m"  
#define GREEN "\033[1;32m" 
#define BLUE "\033[1;34m"  
#define YELLOW "\033[1;33m" 
#define PURPLE "\033[1;35m" 
#define RESET "\033[0m" 
#define MAGNETA "\033[1;35m"
#define CYAN "\033[1;4;36m"


/*Bold: \u001b[1m
Underline: \u001b[4m
Reversed: \u001b[7m
*/
static void FsaTest(void);
static void PrintFsaNexts(fsa_t *fsa, size_t suggested, size_t block_size);
static void TestAlloc(fsa_t *fsa, size_t amount_of_blocks);
static void putstr(char *ptr);

int main()
{
	FsaTest();
	return 0;
}

/******************************************************************************/
static void FsaTest(void)
{
	size_t block_size = 20;
	size_t amount_of_blocks = 6;
	size_t suggested = 0;
	void *mem_ptr = NULL;
	fsa_t *fsa = NULL;
	
	printf(CYAN"\n*****Suggest size*****\n"RESET);
	suggested = FsaSuggestedSize(block_size,amount_of_blocks);
	printf(PURPLE"\nexpected suggestion: 176 real: %ld"RESET, suggested);
	TEST(" --->", suggested, 176);
	
	printf(CYAN"\n*****Create FSA*****\n"RESET);
	mem_ptr = (void*)malloc(suggested);
	fsa = FsaInit(mem_ptr, suggested, block_size);
	PrintFsaNexts(fsa, suggested, block_size + 4);
	
	printf(CYAN"\n*****Allocate all blocks*****\n"RESET);
	TestAlloc(fsa, amount_of_blocks);
	free(mem_ptr);
	
	printf(RED"\n*****End Of Test*****\n"RESET);
}

/******************************************************************************/

static void PrintFsaNexts(fsa_t *fsa, size_t suggested, size_t block_size)
{
	size_t i = 0;
	size_t *ptr = (size_t *)fsa;
	printf(PURPLE"\nprint nexts: \n"RESET);
	for (i = 32; i < suggested - block_size; i = i + block_size)
	{
		printf("expected %ld: %ld real: %ld", i/block_size , i + block_size, 
			  *(ptr + i/WORD_SIZE));
		TEST(" --->", *(ptr + i/WORD_SIZE), i + block_size);
	} 
	printf("expected %ld: %d real: %ld", i/block_size, 0, 
			  *(ptr + i/WORD_SIZE));
	TEST(" --->", *(ptr + i/WORD_SIZE), 0);
}

/******************************************************************************/

static void TestAlloc(fsa_t *fsa, size_t amount_of_blocks) 
{

	char *ptr1 = NULL;
	char *ptr2 = NULL;
	char *ptr3 = NULL;
	char *ptr4 = NULL;
	char *ptr5 = NULL;
	char *ptr6 = NULL;

	printf(CYAN"free blocks : %ld\n"RESET,FsaCountFreeBlocks(fsa));
	
	ptr1 = (char *)FsaAllocBlock(fsa);
	printf(CYAN"Allocates block...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));
	
	ptr2 = (char *)FsaAllocBlock(fsa);
	printf(CYAN"Allocates block...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));
	
	ptr3 = (char *)FsaAllocBlock(fsa);
	printf(CYAN"Allocates block...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));
	
	ptr4 = (char *)FsaAllocBlock(fsa);
	printf(CYAN"Allocates block...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));
	
	ptr5 = (char *)FsaAllocBlock(fsa);
	printf(CYAN"Allocates block...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));
	
	ptr6 = (char *)FsaAllocBlock(fsa);
	printf(CYAN"Allocates block...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));
	
	TEST("NULL return when full? --->", FsaAllocBlock(fsa), NULL);
	printf("\n");
		
	putstr(ptr1);
	putstr(ptr2);
	putstr(ptr3);
	putstr(ptr4);
	putstr(ptr5);
	putstr(ptr6);
			
	printf(BLUE"%s allocated\n"RESET,ptr1);
	printf(BLUE"%s allocated\n"RESET,ptr2);
	printf(BLUE"%s allocated\n"RESET,ptr3);
	printf(BLUE"%s allocated\n"RESET,ptr4);
	printf(BLUE"%s allocated\n"RESET,ptr5);
	printf(BLUE"%s allocated\n"RESET,ptr6);
	
	printf("\n");
	
	FsaFreeBlock(fsa, ptr3);
	printf(YELLOW"Frees block 3...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));
	FsaFreeBlock(fsa, ptr5);
	printf(YELLOW"Frees block 5...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));
	FsaFreeBlock(fsa, ptr1);
	printf(YELLOW"Frees block 1...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));
	
	printf("\n");
	
	ptr3 = (char *)FsaAllocBlock(fsa);
	printf(CYAN"Allocates block...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));
	
	ptr1 = (char *)FsaAllocBlock(fsa);
	printf(CYAN"Allocates block...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));

	ptr5 = (char *)FsaAllocBlock(fsa);
	printf(CYAN"Allocates block...\nfree blocks :\
	%ld\n"RESET,FsaCountFreeBlocks(fsa));
	
	printf("\n");
	
	putstr(ptr3);
	putstr(ptr1);
	putstr(ptr5);
	
	printf(BLUE"%s allocated\n"RESET,ptr1);
	printf(BLUE"%s allocated\n"RESET,ptr2);
	printf(BLUE"%s allocated\n"RESET,ptr3);
	printf(BLUE"%s allocated\n"RESET,ptr4);
	printf(BLUE"%s allocated\n"RESET,ptr5);
	printf(BLUE"%s allocated\n"RESET,ptr6);
	
	TEST("NULL return when full? --->", FsaAllocBlock(fsa), NULL);
	printf("\n");
}


/******************************************************************************/

static void putstr(char *ptr) 
{
	char *str = "block  number : ";
	static char number = 1;
	int i = 0;
	while (i < 16)
	{
		ptr[i] = str[i];
		++i;
	}		
	ptr[i] = number + '0';
	ptr[i + 1] ='\0';
	++number;
}	


