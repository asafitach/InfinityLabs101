/*****************************************************************************/

#ifndef __PQ_HEAP_H__
#define __PQ_HEAP_H__

/*****************************************************************************/

#include <stddef.h> /* size_t */


/*****************************************************************************/

typedef struct pq pq_t; 

typedef int(*pq_cmp_t)(void *data, void *param);
typedef int(*pq_match_t)(void *data, void *param);
typedef int(*print_func_t)(void *data, void *param);

/*****************************************************************************/

/*
Description: The function creates a new priority queue.
@return: The function returns a pointer to the new priority queue.
@errors: Returns NULL if malloc fails.
*/
pq_t *PQCreate(pq_cmp_t pq_cmp);

/*****************************************************************************/

/*
Description: The function frees the queue.
@params: The function gets a pointer to the priority queue.
*/
void PQDestroy(pq_t *pq);

/*****************************************************************************/
/*
Description: The function clear all the elements.
@params: The function gets a pointer to the pq.
@return: 
@errors: 
*/
void PQClear(pq_t *pq);

/*****************************************************************************/
/*Description: The functions inserts a new element to the queue.
@params: The function gets a pointer to the queue and the data to be inserted.
@return: returns 0 on SUCCESS and 1 in FAILURE.
@errors: malloc fail.
*/
int PQEnqueue(pq_t *pq, void *data);

/*****************************************************************************/
/*
Description: The function removes an element from the front of the pq.
@params: The function gets a pointer to the pq.
@return: The function is void.
@errors: 
*/
void *PQDequeue(pq_t *pq);

/*****************************************************************************/
/*
Description: The function gets a pointer to the pq and returns the data at the 
head of the pq.
@params: The function gets a pointer to the pq. 
@return: The function return the data at the front of the pq.
@errors: 
*/
void *PQPeek(const pq_t *pq);

/*****************************************************************************/
/*
Description: The function returns the number of items stored in the pq.
@params: The function gets a pointer to the pq.
@return: The function returns the number of items in the pq.
@errors: 
*/
size_t PQCount(const pq_t *pq);

/*****************************************************************************/
/*
Description: The function checks if pq is empty. 
returns 1 for TRUE, 0 for FALSE.
@params: The function a pointer to the pq.
@return: The function returns an int (BOOLEAN).
@errors:
*/
int PQIsEmpty(const pq_t *pq);

/*****************************************************************************/

/*
Description: The function remove the first element tham match
the condition that returned by the function is match.
@params: The function gets a pointer to the pq, is match function and a element.
@return: The function returns 0 for success 1 for fail.
@errors: 
*/
void *PQErase(pq_t *pq, pq_match_t pq_match, void *param);



/*****************************************************************************/

#endif /* __PQ_HEAP_H__ */

/*****************************************************************************/
