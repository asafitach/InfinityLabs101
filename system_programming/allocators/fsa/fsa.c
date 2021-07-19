#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include "fsa.h"

#define WORD_SIZE 8

/******************************************************************************/

struct fsa
{
	size_t total_blocks;
	size_t block_size; 
	size_t num_of_free_blocks; 
	size_t next_free;/*0 if full*/
};



/****************************************************************************/

fsa_t *FsaInit(void *memory_ptr, size_t total_size, size_t block_size)
{
	size_t build = 0;
	fsa_t *fsa = NULL;
	size_t *ptr = NULL;
	
	assert(NULL != memory_ptr);
	assert(0 != total_size);
	assert(0 != block_size);

	if (block_size % WORD_SIZE != 0)
	{
		block_size = ((block_size / WORD_SIZE) + 1) * WORD_SIZE;
	}
	
		
	fsa = (fsa_t *)memory_ptr;
	
	fsa->total_blocks = (total_size - sizeof(fsa_t)) / (block_size);
	fsa->num_of_free_blocks = fsa->total_blocks;
	fsa->block_size = block_size;
	fsa->next_free = sizeof(fsa_t);
	
	total_size -= fsa->next_free;
	

	while (total_size > block_size)
	{

		ptr = (size_t *)((char *)fsa + sizeof(fsa_t) + (build * block_size));
		*ptr = sizeof(fsa_t) + ((build + 1) * block_size);
		build++;
		total_size -= block_size;

	}
	
	ptr = (((char *)fsa + sizeof(fsa_t) + ((build ) * block_size)));
	*(size_t *)ptr = 0;	
		

				
	return (fsa);
	
}

/****************************************************************************/

size_t FsaSuggestedSize(size_t block_size, size_t amount_of_blocks)
{
	assert(0 != block_size);
	assert(0 != amount_of_blocks);
	
	if (block_size % WORD_SIZE != 0)
	{
		block_size = ((block_size / WORD_SIZE) + 1) * WORD_SIZE;
	}
	
	
	return (sizeof(fsa_t) + (block_size * amount_of_blocks));
}

/****************************************************************************/

void *FsaAllocBlock(fsa_t *fsa_pool)
{
	size_t *ptr = NULL;
	
	assert(NULL != fsa_pool);
	
	if (0 == fsa_pool->next_free)
	{
		return (NULL);
	}
	
	fsa_pool->num_of_free_blocks--;
	ptr = (size_t *)((char *)fsa_pool + fsa_pool->next_free);
	fsa_pool->next_free = *ptr;

	return ((void *)ptr);
}

/****************************************************************************/

void FsaFreeBlock(fsa_t *fsa_pool, void *block)
{	
	assert(NULL != fsa_pool);
	assert(NULL != block);
	
	*(size_t *)block = fsa_pool->next_free;
	fsa_pool->next_free = (char *)block - (char *)fsa_pool;
	fsa_pool->num_of_free_blocks++;
}

/****************************************************************************/

size_t FsaCountFreeBlocks(const fsa_t *fsa_pool)
{
	assert(NULL != fsa_pool);
	
	return (fsa_pool->num_of_free_blocks);
}

/********************************E.O.F*****************************************/
