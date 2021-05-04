/*****************************************************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */
#include "d_vector.h"
/*****************************************************************************/
/*struct heap*/
/*{*/
/*	d_vector_t *d_vector;*/
/*    heap_cmp_t cmp_func;*/
/*}; */

/*****************************************************************************/

typedef struct heap heap_t; 
typedef int(*heap_cmp_t)(const void *data1, const void *data2);
typedef int(*heap_is_match)(const void *data, void *param);

/*****************************************************************************/

/*
Description: The function creates a new priority heap.
@return: The function returns a pointer to the new priority heap.
@errors: Returns NULL if malloc fails.
*/
heap_t *HeapCreate(heap_cmp_t heap_cmp);

/*****************************************************************************/

/*
Description: The function frees the heap.
@params: The function gets a pointer to the priority heap.
*/
void HeapDestroy(heap_t *heap);

/*****************************************************************************/
/*Description: The functions inserts a new element to the heap.
@params: The function gets a pointer to the heap and the data to be inserted.
@return: returns 0 on SUCCESS and 1 in FAILURE.
@errors: malloc fail.
*/
int HeapPush(heap_t *heap, void *data);

/*****************************************************************************/
/*
Description: The function removes an element from the front of the heap.
@params: The function gets a pointer to the heap.
@return: The function is void.
@errors: 
*/
void HeapPop(heap_t *heap);

/*****************************************************************************/
/*
Description: The function removes an element that matches given data.
@params: The function gets a pointer to the heap, and data.
@return: The function is void.
@errors: 
*/
void *HeapRemove(heap_t *heap, heap_is_match is_match, void * param);

/*****************************************************************************/
/*
Description: The function gets a pointer to the heap and returns the data at the 
head of the heap.
@params: The function gets a pointer to the heap. 
@return: The function return the data at the front of the heap.
@errors: 
*/
void *HeapPeek(const heap_t *heap);

/*****************************************************************************/
/*
Description: The function returns the number of items stored in the heap.
@params: The function gets a pointer to the heap.
@return: The function returns the number of items in the heap.
@errors: 
*/
size_t HeapSize(const heap_t *heap);

/*****************************************************************************/
/*
Description: The function checks if heap is empty. 
returns 1 for TRUE, 0 for FALSE.
@params: The function a pointer to the heap.
@return: The function returns an int (BOOLEAN).
@errors:
*/
int HeapIsEmpty(const heap_t *heap);

/*****************************************************************************/

#endif /* __HEAP_H__ */

/*****************************************************************************/
