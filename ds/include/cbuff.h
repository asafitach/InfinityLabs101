#ifndef __CBUFF_H__
#define __CBUFF_H__

#include <stddef.h>  /* size_t */
#include <unistd.h> /* ssize_t */

typedef struct cbuff cbuff_t;

/*Description: The function creates a new cbuff data structure.
@return: The function returns a pointer to cbuff_t structure.
@errors: Returns NULL if malloc fails.
*/
cbuff_t *CbuffCreate(size_t capacity);

/*Description: The function frees all the elements in the Buffer.
@params: The function gets a pointer to cbuff.
*/
void CbuffDestroy(cbuff_t *cbuff);


/*Description: The function read num_of_bytes from cbuff to dest .
@params: The function gets a pointer to the cbuff and num_of_bytes and dest.
@return: num_of_bytes that read
@errors: return -1.
*/
ssize_t CbuffRead(cbuff_t *cbuff, void * dest, size_t num_of_bytes);


/*Description: The function write num_of_bytes from src to the cbuff.
@params: The function gets a pointer to the cbuff and src and num_of_bytes.
@return: num_of_bytes that write.
@errors: return -1.
*/
ssize_t CbuffWrite(cbuff_t *cbuff, const void *src, size_t num_of_bytes);


/*Description: The function gets a pointer to the cbuff and returns the free space in cbuff.
@params: The function gets a pointer to the cbuff. 
@return: free space in cbuff.
*/
size_t CbuffFreeSpace(const cbuff_t *cbuff);


/*Description: The function gets a pointer to the cbuff and returns the used space in cbuff.
@params: The function gets a pointer to the cbuff. 
@return: used space in cbuff.
*/
size_t CbuffCountFull(const cbuff_t *cbuff);


/*Description: The function checks if cbuff is empty. 
returns 1 for TRUE, 0 for FALSE.
@params: The function a pointer to the cbuff.
@return: The function returns an int (BOOLEAN).
*/
int CbuffIsEmpty(const cbuff_t *cbuff);




#endif /* __CBUFF_H__ */
