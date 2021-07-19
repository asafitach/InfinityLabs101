#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include "fsa.h"



/******************************************************************************/

struct fsa

{
	size_t next_free;/*0 if full*/
};



/****************************************************************************/

fsa_t *FsaInit(void *memory_ptr, size_t total_size, size_t block_size)
{
	size_t build = 0;
	fsa_t *fsa = NULL;
	void *ptr = NULL;
	
	assert(NULL != memory_ptr);
	assert(0 != total_size);
	assert(0 != block_size);
	
	fsa = (fsa_t *)memory_ptr;
	
	if (block_size % 8 != 0)
	{
		block_size = ((block_size / 8) + 1) * 8;
	}
	
	fsa->next_free = sizeof(fsa_t);
	ptr = fsa + sizeof(fsa_t);

	while(total_size > block_size)
	{

		ptr = ((char *)fsa  + sizeof(fsa_t) + (build * block_size));
		*(size_t *)ptr = sizeof(fsa_t) + ((build + 1) * block_size);
		build++;
		total_size -= block_size;
	}
	ptr = (((char *)memory_ptr + sizeof(fsa_t) + ((build - 1) * block_size)));
	*(size_t *)ptr = 0;	
	
	return (fsa);
	
}

/****************************************************************************/

size_t FsaSuggestedSize(size_t block_size, size_t amount_of_blocks)
{
	assert(0 != block_size);
	assert(0 != amount_of_blocks);
	
	if (block_size % 8 != 0)
	{
		block_size = ((block_size / 8) + 1) * 8;
	}
	
	
	return ((block_size  * amount_of_blocks) + sizeof(fsa_t));
}

/****************************************************************************/

void *FsaAllocBlock(fsa_t *fsa_pool)
{
	void *ptr = NULL;
	
	assert(NULL != fsa_pool);
	
	if (0 == fsa_pool->next_free)
	{
		return (NULL);
	}
	
	ptr = (void *)((char *)fsa_pool + fsa_pool->next_free);
	fsa_pool->next_free = *(size_t *)/*&*/(ptr);
	return (ptr);
}

/****************************************************************************/

void FsaFreeBlock(fsa_t *fsa_pool, void *block)
{	
	assert(NULL != fsa_pool);
	assert(NULL != block);
	
	if (0 == fsa_pool->next_free)
	{
		return;
	}
	
	*(size_t *)block = fsa_pool->next_free;
	fsa_pool->next_free = (char *)block - (char *)fsa_pool;
}

/****************************************************************************/

size_t FsaCountFreeBlocks(const fsa_t *fsa_pool)
{
	size_t count = 0;
	size_t next = 0;
	void *ptr = NULL;
	
	assert(NULL != fsa_pool);
	
	if (0 == fsa_pool->next_free)
	{
		return (0);
	}
	
	next = fsa_pool->next_free;
	ptr = (void *)((char *)fsa_pool + next);
	
	while (0 != *(size_t *)/*&*/ptr)
	{
		count++;
		next = *(size_t *)/*&*/ptr;
		ptr = (char *)fsa_pool + next;
		/*printf("%p\t\t%lu\n", ptr, next);*/
	}
	
	return (count + 1);
}

/********************************E.O.F*****************************************/
