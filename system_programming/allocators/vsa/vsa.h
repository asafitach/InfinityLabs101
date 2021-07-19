#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h>      /* size_t */
	
/* managment structure */
typedef struct block_header vsa_t;




/****************************************************************************/
/*
Description: Creates a new VSA.
Parameters: memory_ptr and total size of memory.
Return Value: pointer to the vsa_pool.
*/

vsa_t *VsaInit(void *memory_ptr, size_t total_size); 

/****************************************************************************/
/*
Description: Allocates a block and return a pointer to it.
Parameters: a pointer to vsa_pool, size.
Return Value: pointer to the allocated block.
*/

void *VsaAlloc(vsa_t *vsa, size_t size); 

/****************************************************************************/
/*
Description: Frees an allocated block.
Parameters: a pointer to the block to free.
Return Value: void.
*/

void VsaFree(void *block); 

/****************************************************************************/
/*
Description: Returns the largest chunck available in vsa_pool.
Parameters: pointer to vsa_pool.
Return Value: Largest chunck available.
*/

size_t VsaLargestChunkAvailable(vsa_t *vsa); 

#endif /* __VSA_H__ */



