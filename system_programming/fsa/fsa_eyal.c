#include <stdio.h>
#include "fsa.h"

#define WORD_SIZE sizeof(size_t)
#define PADDED_BLOCK_SIZE (((block_size - 1)/WORD_SIZE + 1) * WORD_SIZE)
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
	
	size_t next = 0;
	fsa_t *fsa = (fsa_t *)memory_ptr;
	size_t *size_t_ptr = (size_t*)memory_ptr;
	
	fsa->total_blocks = (total_size - sizeof(fsa_t))/PADDED_BLOCK_SIZE;
	fsa->block_size = PADDED_BLOCK_SIZE;
	fsa->num_of_free_blocks = fsa->total_blocks;
	fsa->next_free = sizeof(fsa_t);
	
	for (next = fsa->next_free; 
		sizeof(fsa_t) < total_size - PADDED_BLOCK_SIZE; 
		total_size -= PADDED_BLOCK_SIZE, next += PADDED_BLOCK_SIZE)
	{
		*(size_t_ptr + (next / WORD_SIZE)) = next + PADDED_BLOCK_SIZE;
	}
	*(size_t_ptr + (next / WORD_SIZE)) = 0;
	
	return fsa;
}

/****************************************************************************/

size_t FsaSuggestedSize(size_t block_size, size_t amount_of_blocks)
{
	return PADDED_BLOCK_SIZE * amount_of_blocks + sizeof(fsa_t);
}

/****************************************************************************/

void *FsaAllocBlock(fsa_t *fsa_pool)
{
	size_t cur_next_free = fsa_pool->next_free; 
	size_t *size_t_ptr = (size_t*)fsa_pool;
	
	if (0 == fsa_pool->next_free)
	{
		return NULL;
	}
	
	fsa_pool->next_free = 
					(size_t)*(size_t_ptr + (fsa_pool->next_free) / WORD_SIZE);
	
	return (void*)(size_t_ptr + cur_next_free/WORD_SIZE);
}

/****************************************************************************/

void FsaFreeBlock(fsa_t *fsa_pool, void *block)
{
	size_t *size_t_block_ptr = block;
	size_t block_address = (size_t)block;
	size_t pool_address = (size_t)fsa_pool;
	
	*size_t_block_ptr = fsa_pool->next_free;    	
	
	fsa_pool->next_free = block_address - pool_address;
}

/****************************************************************************/

size_t FsaCountFreeBlocks(const fsa_t *fsa_pool)
{
	size_t count = 0;
	size_t next_free = fsa_pool->next_free;
	char *char_ptr = (char*)fsa_pool;
	
	if (0 == fsa_pool->next_free)
	{
		return 0;
	}
	
	while (0 != *(size_t*)(char_ptr + next_free))
	{
		next_free = *(size_t*)(char_ptr + next_free);
		++count;
	}
	
	++count;
	
	return count;
}
		
		
		
	
	
	

