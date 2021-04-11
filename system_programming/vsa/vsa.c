#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include <unistd.h> /* ssize_t */
#include "vsa.h"


#define WORD_SIZE 8
#define BLOCK (sizeof(vsa_t) / WORD_SIZE)

/******************************************************************************/

struct block_header
{
	ssize_t block_size;
#ifndef NDEBUG
	size_t magic_number; /* 0xCAFEABBA */
#endif
};

/****************************************************************************/

vsa_t *VsaInit(void *memory_ptr, size_t total_size)
{
	vsa_t *vsa = memory_ptr;
	size_t managment = 0;

	assert((2 * sizeof(vsa_t)) < total_size);
	assert(NULL != memory_ptr);

	total_size /= WORD_SIZE;
	managment = 1 + BLOCK;

	vsa->block_size = -(total_size - managment);
	#ifndef NDEBUG
	vsa->magic_number = 0xCAFEABBA;
	#endif

	((vsa_t *)((size_t *)vsa - vsa->block_size + BLOCK))->block_size = 0x90909090;

	return ((vsa_t *)memory_ptr);
}


/****************************************************************************/
void Largest(vsa_t *vsa_o)
{
	size_t *vsa = (size_t *)vsa_o;
	ssize_t current_val = 0;
	ssize_t cmp_val = 0;
	
	current_val = ((vsa_t *)vsa)->block_size;
	
	while (current_val != 0x90909090)
	{
		while (current_val < 0)
		{
			/*cmp_val is the block size of the --next block after-- vsa's block*/
			cmp_val = ((vsa_t *)(vsa - current_val + BLOCK))->block_size;
			if (cmp_val < 0 && cmp_val != 0x90909090)
			{
				/*update vsa's block size*/
				current_val += cmp_val - BLOCK;
				((vsa_t *)vsa)->block_size += current_val - BLOCK;
			}
			else if (cmp_val == 0x90909090)
			{
				((vsa_t *)vsa)->block_size = current_val;
				return;
			}
			else
			{
				/* at this point cmp_val>0 and we reached to occupied block */
				vsa -= current_val - BLOCK;	/*vsa is change to that occupied block*/
				current_val = ((vsa_t *)vsa)->block_size; /*this value is positive by assertion*/
				break;
			}
		}
		/*this while loop iterate until the next negative block_size value*/
		while (current_val != 0x90909090 && current_val < 0)	
		{
			vsa += current_val + BLOCK;
			current_val = ((vsa_t *)vsa)->block_size;
		}
	}	
}

void *VsaAlloc(vsa_t *vsa, size_t size)
{
	ssize_t current_val = 0;
	ssize_t wanted_size = (ssize_t)size; /*will gain negative value*/
	size_t *run = (size_t *)vsa;

	#ifndef NDEBUG
	assert(0xCAFEABBA == vsa->magic_number);
	#endif
	
	Largest(vsa);


	ssize = -((ssize - 1) / WORD_SIZE + 1);
	
	current_val = vsa->block_size;

	while (current_val != 0x90909090 && current_val > ssize)
	{
		current_val = (current_val > 0) ? current_val : -current_val;
		run += current_val + BLOCK; 
		current_val = ((vsa_t *)run)->block_size;
	} 
			
	if (current_val == 0x90909090)
	{
		return (NULL);
	}
	
	if ((size_t)(ssize - current_val) <= BLOCK)	
	{
		((vsa_t *)run)->block_size *= -1;
		return ((vsa_t *)(run + BLOCK));
	}
	
	current_val -= (ssize - BLOCK);
	((vsa_t *)run)->block_size = -ssize;
	run -= (ssize - BLOCK);
	((vsa_t *)run)->block_size = current_val;
	((vsa_t *)run)->magic_number = 0xCAFEABBA;
	
	return ((vsa_t *)(run + ssize));
}

/****************************************************************************/

void VsaFree(void *block)
{
	assert (NULL != block);

	block = (size_t *)block - BLOCK;
	
	#ifndef NDBUG
	assert(((vsa_t *)block)->magic_number == 0xCAFEABBA); 
	#endif
	
	((vsa_t *)block)->block_size *= -1;
}

/****************************************************************************/


size_t VsaLargestChunkAvailable(vsa_t *vsa)
{
	ssize_t max_free = 0;
	ssize_t current_val = 0;
	size_t *run = (size_t *)vsa;
	
	
	#ifndef NDEBUG
	assert(0xCAFEABBA == vsa->magic_number);
	#endif
	
	Largest(vsa);
	
	current_val = vsa->block_size;
	
	while (current_val != 0x90909090)
	{
		if (max_free > current_val)
		{
			max_free = current_val;
		}
		current_val = (current_val > 0) ? current_val : -current_val;
		run += BLOCK + current_val;
		current_val = ((vsa_t*)run)->block_size;
	}

	return ((size_t)(-max_free * WORD_SIZE));
}

/********************************E.O.F*****************************************/
