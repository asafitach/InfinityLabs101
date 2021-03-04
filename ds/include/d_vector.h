#ifndef __D_VECTOR_H__
#define __D_VECTOR_H__

#include <stddef.h>  /* size_t */

typedef struct d_vector d_vector_t;


typedef enum {
SUCCESS = 0, 
FAIL = 1
} status_t;

/*Description: The function creates new vector data structure.
@return: The function returns a pointer to vector_t structure.
@errors: malloc errors
*/
d_vector_t *VectorCreate(size_t init_capacity);


/*Description: The function frees the dynamic vector.
@params: The function gets a pointer to the vector.
*/
void VectorDestroy(d_vector_t *d_vector);


/*Description: The function deletes the last in the vector 
@params: The function gets a pointer to the vector and the location index.
@return: The function is void.
@errors: index given does not exist 
*/
void VectorPopBack(d_vector_t *d_vector);


/*Description: The function adds an item to the vector
@params: The function gets a pointer to the vector and a void pointer
@return: The function is void.
@errors: realloc fail
*/
status_t VectorPushBack(d_vector_t *d_vector, const void *item);


/*Description: The function inserts item to location index in the vector.
@params: The function gets a pointer to the vector, 
		 an index of size_t and a void pointer.
@return: The function is void.
@errors: 
*/
void VectorSetElement(const d_vector_t *d_vector, size_t index, const void *item);


/*Description: The function gets the item stored in location index in the vector 
@params: The function gets a pointer to the vector and a size_t index
@return: Returns a pointer to the item. returns NULL if index given does not exist
@errors: 
*/
void *VectorGetElement(const d_vector_t *d_vector, size_t index); 


/*Description: The function returns the number of items stored in the vector
@params: The function gets a pointer to the vector.
@return: The function returns the number of items in the stack.
@errors: 
*/
size_t VectorGetSize(const d_vector_t *d_vector);


/*Description: The function returns the capacity of the vector
@params: The function gets a pointer to the vector.
@return: The function returns the capacity of the vector
@errors: 
*/
size_t VectorGetCapacity(const d_vector_t *d_vector);


/*Description: The function expands the vector
@params: The function gets a pointer to the vector, and the desired size
@return: The function returns status.
@errors: realloc fail
*/
status_t VectorExpand(d_vector_t *d_vector, size_t total_size);


/*Description: The function shrinks the vector to the optimal size
@params: The function gets a pointer to the vector
@return: The function returns status.
@errors: realloc fail
*/
status_t VectorShrink(d_vector_t *d_vector);


#endif /* __D_VECTOR_H__ */
