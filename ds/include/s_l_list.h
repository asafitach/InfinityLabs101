#ifndef __S_L_LIST_H__
#define __S_L_LIST_H__

#include <stddef.h>  /* size_t */

typedef enum 
{
	SUCCESS = 0,
	FAIL = 1
} status_t;

typedef struct node node_t;
typedef node_t* slist_iter_t; 
typedef struct list slist_t;

typedef int(*cmp_func_t)(const void *data, void *param);
typedef int(*action_func_t)(void *data, void *param);



/*Description: The function creates a new singly linked list data structure.
@return: The function returns a pointer to slist_t structure.
@errors: Returns NULL if malloc fails.
*/
slist_t *SlistCreate(void);


/*Description: The function frees all the elements in the list.
@params: The function gets a pointer to the singly linked list.
*/
void SlistDestroy(slist_t *list);


/*Description: The functions inserts a new element after the element
pointed by the iterator.
@params: The function gets an iterator and the data to be inserted.
@return: status_t
@errors: malloc fail.
*/
slist_iter_t SlistInsert(slist_iter_t iterator, const void *data);


/*Description: The function removes an element from the list.
@params: The function gets an iterator to the element to be removed.
@return: The function is void.
@errors: 
*/
slist_iter_t SlistRemove(slist_iter_t iterator);


/*Description: The function gets an iterator and returns the data at the 
location.
@params: The function gets an interators. 
@return: The function return int.
@errors: 
*/
void *SlistGetData(const slist_iter_t iterator);


/*Description: The function sets the element pointed to by the iterator 
to data. 
@params: The function gets an iterator and data for insertion.
@return: 
@errors: 
*/
void SlistSetData(const slist_iter_t iterator, const void *data); 


/*Description: The function returns the number of items stored in the list.
@params: The function gets a pointer to the list.
@return: The function returns the number of items in the list.
@errors: 
*/
size_t SlistCount(const slist_t *list);


/*Description: The function finds and element in the list.
@params: The function gets a pointer to the list.
@return: The function returns an iterator that points to the data or NULL
if data is not in the list.
@errors: 
*/
slist_iter_t SlistFind(const slist_iter_t from, const slist_iter_t to, cmp_func_t cmp_func, void *param); 



/*Description: The function returns iterator to the head of the list.
@params: The function gets a pointer list.
@return: The function returns an iterator.
@errors:
*/
slist_iter_t SlistBegin(const slist_t *list);


/*Description: The function returns iterator to the tail of the list.
@params: The function gets a pointer list.
@return: The function returns an iterator.
@errors:
*/
slist_iter_t SlistEnd(const slist_t *list);

/*Description: The function returns an iterator to the n element after 
the current iterator position.
@params: The function gets an iterator and n.
@return: The function returns an iterator.
@errors:
*/

slist_iter_t SlistNext(const slist_iter_t iterator);

/*Description: The function checks if list is empty. 
returns 1 for TRUE, 0 for FALSE.
@params: The function a pointer to the list.
@return: The function returns an int (BOOLEAN).
@errors:
*/

int SlistIsEmpty(slist_t *list);

/*Description: The function invokes func_ptr for each element in the mentioned range. 
@params: A function pointer, iterator start and end.
@errors:
*/

status_t SlistForeach(slist_iter_t from, slist_iter_t to , action_func_t action_func, void *param);

void PrintList (node_t *head);
void SlistAppend(slist_t *dest, slist_t *src);

#endif /* __S__L_LIST_H__ */
