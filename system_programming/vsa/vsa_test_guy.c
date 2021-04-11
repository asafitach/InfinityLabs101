#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc, free */
#include <string.h>		/* strcpy */
#include "vsa.h"
#include <unistd.h>

/******************************Color definitions*******************************/

#define RED "\033[5;91m"      /* print in red          */
#define GREEN "\033[1;92m"    /* print in green        */
#define BLUE "\033[1;34m"  		/* print in blue 		*/
#define YELLOW "\033[1;33m" /* print in yellow */
#define LYELLOW "\033[1;95m"  /* print in light magenta*/
#define CYAN "\033[1;36m"     /* print in cyan         */
#define LIGHT "\033[2;37m"    /* print in gray         */
#define RESET "\033[1;0m"     /* reset print color     */

/*********************************Test Macros**********************************/

#define TEST(name, expected, real)\
            	(real == expected ? printf(GREEN"%s PASS.\n"RESET, name):\
            	 printf(RED"%s FAIL.\n"RESET, name))

	  
/*****************************************************************************/
typedef enum
{
	SUCCESS,
	INIT_FAIL,
	ALLOC_FAIL,
	FREE_FAIL,
	BIGGEST_CHANK_FAIL
	
} status_t;

status_t TestInit();

status_t TestAllocOnce();
status_t TestAllocAlmostAll();
status_t TestAllocAll();
status_t TestRepeatedAlloc();
status_t TestAllocOverflow();
status_t TestFree();

status_t TestAllocFreeAlloc();

status_t TestLargeChunk();

/*****************************************************************************/
static void VsaPrint(ssize_t *ptr, ssize_t size_in_bytes);

int main()
{	
	TestInit();
	TestAllocOnce();
	TestAllocAlmostAll();
	TestAllocAll();
	TestRepeatedAlloc();
	TestAllocOverflow();
	TestFree();
	TestAllocFreeAlloc();
	return 0;
}

status_t TestInit()
{
	void *ptr = NULL;
	vsa_t *vsa_pool = NULL;
	ptr = calloc(100, sizeof(char));
	printf(YELLOW"\n-----------TEST INIT------------\n\n"RESET);
	vsa_pool = VsaInit(ptr, 100);
	printf(BLUE"VCA pool created.\n"RESET);
	printf(LIGHT"Block size value is %ld\n."RESET, *(ssize_t*)vsa_pool);
	free(vsa_pool);
	return SUCCESS;
}

status_t TestAllocOnce()
{
	void *ptr = NULL;
	vsa_t *vsa_pool = NULL;
	
	ptr = calloc(100, sizeof(char));
	printf(YELLOW"\n-----------TEST ALLOC ONCE------------\n\n"RESET);
	vsa_pool = VsaInit(ptr, 80);
	printf(BLUE"VCA pool created.\n"RESET);
	printf(LIGHT"Block size value is %ld\n"RESET, *(ssize_t*)vsa_pool);
	
	VsaPrint((ssize_t*)vsa_pool, 80);
	printf(CYAN"Largest chunk is %lu\n"RESET, VsaLargestChunkAvailable(vsa_pool));
	ptr = VsaAlloc(vsa_pool, 16);
	printf(LIGHT"Allocated 16 bytes\n"RESET);
	VsaPrint((ssize_t*)vsa_pool, 80);
	printf(CYAN"Largest chunk is %lu\n"RESET, VsaLargestChunkAvailable(vsa_pool));
	free(vsa_pool);
	return SUCCESS;
}

status_t TestAllocAlmostAll()
{
	void *ptr = NULL;
	vsa_t *vsa_pool = NULL;
	
	ptr = calloc(100, sizeof(char));
	printf(YELLOW"\n-----------TEST ALLOC ALLMOST ALL------------\n\n"RESET);
	vsa_pool = VsaInit(ptr, 80);
	printf(BLUE"VCA pool created.\n"RESET);
	printf(LIGHT"Block size value is %ld\n"RESET, *(ssize_t*)vsa_pool);
	
	VsaPrint((ssize_t*)vsa_pool, 80);
	
	ptr = VsaAlloc(vsa_pool, 32);
	printf(LIGHT"Allocated 32 bytes\n"RESET);
	VsaPrint((ssize_t*)vsa_pool, 80);
	printf(CYAN"Largest chunk is %lu\n"RESET, VsaLargestChunkAvailable(vsa_pool));
	free(vsa_pool);
	return SUCCESS;
}

status_t TestAllocAll()
{
	void *ptr = NULL;
	vsa_t *vsa_pool = NULL;
	
	ptr = calloc(100, sizeof(char));
	printf(YELLOW"\n-----------TEST ALLOC ALL------------\n\n"RESET);
	vsa_pool = VsaInit(ptr, 80);
	printf(BLUE"VCA pool created.\n"RESET);
	printf(LIGHT"Block size value is %ld\n"RESET, *(ssize_t*)vsa_pool);
	
	VsaPrint((ssize_t*)vsa_pool, 80);
	
	ptr = VsaAlloc(vsa_pool, 48);
	printf(LIGHT"Allocated 48 bytes\n"RESET);
	VsaPrint((ssize_t*)vsa_pool, 80);
	printf(CYAN"Largest chunk is %lu\n"RESET, VsaLargestChunkAvailable(vsa_pool));
	free(vsa_pool);
	return SUCCESS;
}

status_t TestRepeatedAlloc()
{
	void *ptr = NULL;
	vsa_t *vsa_pool = NULL;
	int i = 0;
	ptr = calloc(100, sizeof(char));
	printf(YELLOW"\n-----------TEST REPEATED ALLOC------------\n\n"RESET);
	vsa_pool = VsaInit(ptr, 96);
	printf(BLUE"VCA pool created.\n"RESET);
	printf(LIGHT"Block size value is %ld\n"RESET, *(ssize_t*)vsa_pool);
	
	VsaPrint((ssize_t*)vsa_pool, 96);
	for (i = 0; i < 3; ++i)
	{
		ptr = VsaAlloc(vsa_pool, 8);
		printf(LIGHT"Allocated 8 bytes\n"RESET);
		VsaPrint((ssize_t*)vsa_pool, 96);
		printf(CYAN"Largest chunk is %lu\n"RESET, VsaLargestChunkAvailable(vsa_pool));
	}
	
	free(vsa_pool);
	return SUCCESS;
}

status_t TestAllocOverflow()
{
	void *ptr = NULL;
	vsa_t *vsa_pool = NULL;
	
	ptr = calloc(100, sizeof(char));
	printf(YELLOW"\n-----------TEST ALLOC OVERFLOW------------\n\n"RESET);
	vsa_pool = VsaInit(ptr, 40);
	printf(BLUE"VCA pool created.\n"RESET);
	printf(LIGHT"Block size value is %ld\n"RESET, *(ssize_t*)vsa_pool);
	
	VsaPrint((ssize_t*)vsa_pool, 40);
	
	ptr = VsaAlloc(vsa_pool, 100);
	if (NULL != ptr)
	{
		return ALLOC_FAIL;
	}
	VsaPrint((ssize_t*)vsa_pool, 40);
	
	free(vsa_pool);
	return SUCCESS;
}

status_t TestFree()
{
	void *ptr = NULL;
	void *ptr_arr[3] = {NULL};
	vsa_t *vsa_pool = NULL;
	int i = 0;
	ptr = calloc(100, sizeof(char));
	printf(YELLOW"\n-----------TEST FREE------------\n\n"RESET);
	vsa_pool = VsaInit(ptr, 96);
	printf(BLUE"VCA pool created.\n"RESET);
	printf(LIGHT"Block size value is %ld\n"RESET, *(ssize_t*)vsa_pool);
	
	VsaPrint((ssize_t*)vsa_pool, 96);
	for (i = 0; i < 3; ++i)
	{
		ptr_arr[i] = VsaAlloc(vsa_pool, 8);
		printf(LIGHT"Allocated 8 bytes\n"RESET);
		VsaPrint((ssize_t*)vsa_pool, 96);
	}
	VsaFree(ptr_arr[1]);
	printf(LIGHT"Freed 8 bytes\n"RESET);
	VsaPrint((ssize_t*)vsa_pool, 96);
	VsaFree(ptr_arr[0]);
	printf(LIGHT"Freed 8 bytes\n"RESET);
	VsaPrint((ssize_t*)vsa_pool, 96);
	VsaFree(ptr_arr[2]);
	printf(LIGHT"Freed 8 bytes\n"RESET);
	VsaPrint((ssize_t*)vsa_pool, 96);
	
	free(vsa_pool);
	return SUCCESS;
}

status_t TestAllocFreeAlloc()
{
	void *ptr = NULL;
	void *ptr_arr[3] = {NULL};
	vsa_t *vsa_pool = NULL;
	int i = 0;
	ptr = calloc(100, sizeof(char));
	printf(YELLOW"\n-----------TEST ALLOC FREE ALLOC------------\n\n"RESET);
	vsa_pool = VsaInit(ptr, 96);
	printf(BLUE"VCA pool created.\n"RESET);
	printf(LIGHT"Block size value is %ld\n"RESET, *(ssize_t*)vsa_pool);
	
	VsaPrint((ssize_t*)vsa_pool, 96);
	for (i = 0; i < 3; ++i)
	{
		ptr_arr[i] = VsaAlloc(vsa_pool, 8);
		printf(LIGHT"Allocated 8 bytes\n"RESET);
		VsaPrint((ssize_t*)vsa_pool, 96);
	}
	for (i = 0; i < 3; ++i)
	{
		VsaFree(ptr_arr[i]);
		printf(LIGHT"Freed 8 bytes\n"RESET);
		VsaPrint((ssize_t*)vsa_pool, 96);
	}
	
	ptr = VsaAlloc(vsa_pool, 8);
	printf(LIGHT"Allocated 8 bytes\n"RESET);
	VsaPrint((ssize_t*)vsa_pool, 96);
		
	ptr = VsaAlloc(vsa_pool, 32);
	printf(LIGHT"Allocated 32 bytes\n"RESET);
	VsaPrint((ssize_t*)vsa_pool, 96);
	printf("DONE!");
	
	free(vsa_pool);
	return SUCCESS;
}

status_t TestLargeChunk()
{
	printf(YELLOW"\n-----------TEST LARGE CHUNK------------\n\n"RESET);
	return SUCCESS;
}

static void VsaPrint(ssize_t *ptr, ssize_t size_in_bytes)
{
	ssize_t i = 0;
	for (i = 0; i < size_in_bytes; i = i + 8)
	{
		printf("%ld\t ", *ptr);	/* %ld for decimal, %lx for magic number */
		++ptr;
	}
	printf("\n");
}


