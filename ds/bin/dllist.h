#ifndef __DLLIST_H__
#define __DLLIST_H__

#include <stddef.h>  /* size_t */


/********************until here***************************/


typedef struct node* dlist_iter_t; 
typedef struct dlist dlist_t;

typedef int(*is_equal_func_t)(void *data, void *param);
typedef int(*action_func_t)(void *data, void *param);

/*Description: The function creates a new doubly linked list data structure.
@return: The function returns a pointer to dlist_t structure.
@errors: Returns NULL if malloc fails.
*/
dlist_t *DlistCreate(void);

/*Description: The function frees all the elements in the list.
@params: The function gets a pointer to the doubly linked list.
*/
void DlistDestroy(dlist_t *list);

/*Description: The functions inserts a new element before the element
pointed by the iterator.
@params: The function gets an iterator and the data to be inserted.
@return: dlist_iter_t and NULL on malloc fail.
@errors: malloc fail.
*/
dlist_iter_t DlistInsert(dlist_iter_t iterator, void *data);

/*Description: The functions inserts a new element in the beginning of the list.
@params: The function gets an iterator and the data to be inserted.
@return: dlist_iter_t and NULL on malloc fail.
@errors: malloc fail.
*/
dlist_iter_t DlistPushFront(dlist_t *dlist, void *data);

/*Description: The functions inserts a new element in the end of the list.
@params: The function gets an iterator and the data to be inserted.
@return: dlist_iter_t and NULL on malloc fail.
@errors: malloc fail.
*/
dlist_iter_t DlistPushBack(dlist_t *dlist, void *data);

/*Description: The function removes an element from the list.
@params: The function gets an iterator to the element to be removed.
@return: dlist_iter_t
@errors: 
*/
dlist_iter_t DlistRemove(dlist_iter_t iterator);

/*Description: The function removes an element from beginning of the list.
@params: The function gets an iterator to the element to be removed.
@return: void *
@errors: 
*/
void *DlistPopFront(dlist_t *dlist);

/*Description: The function removes an element from end of the list.
@params: The function gets an iterator to the element to be removed.
@return: void *
@errors: 
*/
void *DlistPopBack(dlist_t *dlist);

/*Description: The function gets an iterator and returns the data at the 
location.
@params: The function gets an interators. 
@return: The function return void *.
@errors: 
*/
void *DlistGetData(const dlist_iter_t iterator);

/*Description: The function returns the number of items stored in the list.
@params: The function gets a pointer to the list.
@return: The function returns the number of items in the list.
@errors: 
*/
size_t DlistSize(const dlist_t *list);

/*Description: The function finds the first element in the list.
@params: The function gets a pointer to the list.
@return: The function returns an iterator that points to the data or NULL
if data is not in the list.
@errors: 
*/
dlist_iter_t DlistFindOne(dlist_iter_t from, dlist_iter_t to, is_equal_func_t is_equal_func, const void *param); 

/*Description: The function finds the elements in the list.
@params: The function gets a pointer to the list.
@return: The function returns a the number of matches found.
@errors: 
*/
int DlistFindMulti(dlist_iter_t from, dlist_iter_t to, is_equal_func_t is_equal_func, const void *param, dlist_t *dest); 

/*Description: The function returns iterator to the head of the list.
@params: The function gets a pointer list.
@return: The function returns an iterator.
@errors:
*/
dlist_iter_t DlistBegin(const dlist_t *list);

/*Description: The function returns iterator to the tail of the list.
@params: The function gets a pointer list.
@return: The function returns an iterator.
@errors:
*/
dlist_iter_t DlistEnd(const dlist_t *list);

/*Description: The function returns an iterator to the element after 
the current iterator position.
@params: The function gets an iterator.
@return: The function returns an iterator to the next element.
@errors:
*/
dlist_iter_t DlistNext(dlist_iter_t iterator);

/*Description: The function returns an iterator to the element before 
the current iterator position.
@params: The function gets an iterator.
@return: The function returns an iterator to the previous element.
@errors:
*/
dlist_iter_t DlistPrev(dlist_iter_t iterator);

/*Description: The function checks if list is empty. 
returns 1 for TRUE, 0 for FALSE.
@params: The function a pointer to the list.
@return: The function returns an int (BOOLEAN).
@errors:
*/
int DlistIsEmpty(const dlist_t *list);

/*Description: The function invokes func_ptr for each element in the mentioned range. 
@params: A function pointer, iterator start and end.
return: returns 0 for SUCCESS, 1 for FAIL if actaion_func didn't work on all the elements.
@errors:
*/
int DlistForeach(dlist_iter_t from, dlist_iter_t to , action_func_t action_func, void *param);

/*Description: The function recieves iterator from, to and dest and inserts the elements from until to to dest list and removes them from the source.
@params: dlist_iter_t.
@errors:
*/
dlist_iter_t DlistSplice(dlist_iter_t dest, dlist_iter_t from, dlist_iter_t to);

/*Description: The function checks if the iterators are the same ans. 
returns 1 for TRUE, 0 for FALSE.
@params: two iterators and cmp_func_t.
@return: The function returns an int (BOOLEAN).
@errors:
*/
int DlistIsSameIter(dlist_iter_t iterator1, dlist_iter_t iterator2);


#endif /* __DLLIST_H__ */
