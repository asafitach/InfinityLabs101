#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h>      /* size_t */


/*************************************************/

/* managment structure */
typedef struct fsa fsa_t;


/****************************************************************************/
/*
Description: Creates a new FSA.
Parameters: memory_ptr- the, total size of memory and block size of data.
Return Value: pointer to the fsa.
*/

fsa_t *FsaInit(void *memory_ptr, size_t total_size, size_t block_size); 

/****************************************************************************/
/*
Description: Suggest a size for the fsa according to the desired size.
Parameters: amount of blocks and block size.
Return Value: the suggested block size.
*/

size_t FsaSuggestedSize(size_t block_size, size_t amount_of_blocks); 

/****************************************************************************/
/*
Description: Allocates a block and return a pointer to it.
Parameters: a pointer to fsa.
Return Value: pointer to the allocated block.
*/

void *FsaAllocBlock(fsa_t *fsa_pool); 

/****************************************************************************/
/*
Description: Frees an allocated block.
Parameters: a pointer to the block to free.
Return Value: void.
*/

void FsaFreeBlock(fsa_t *fsa_pool, void *block); 

/****************************************************************************/
/*
Description: Returns the amount of available blocks remaining in the FSA
Parameters: pointer to fsa.
Return Value: amount of available blocks.
*/

size_t FsaCountFreeBlocks(const fsa_t *fsa_pool); 

#endif /* __FSA_H__ */












