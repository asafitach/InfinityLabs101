#ifndef __SRTLIST_H__
#define __SRTLIST_H__

#include <stddef.h>  /* size_t */

#include "dllist.h"



typedef struct srtlist srtlist_t;
typedef dlist_iter_t srtlist_iter_t; 

typedef int(*cmp_func_t)(void *data, void *param);
typedef int(*is_match_t)(void *data, void *param);

/*Description: The function creates a new sorted linked list data structure.
@return: The function returns a pointer to srtlist_t structure.
@errors: Returns NULL if malloc fails.
*/
srtlist_t *SrtListCreate(cmp_func_t cmp_func);


/*Description: The function frees all the elements in the list.
@params: The function gets a pointer to the sorted linked list.
*/
void SrtListDestroy(srtlist_t *list);


/*Description: The function returns an iterator to the element after 
the current iterator position.
@params: The function gets an iterator.
@return: The function returns an iterator to the next element.
@errors:
*/
srtlist_iter_t SrtListNext(srtlist_iter_t iterator);


/*Description: The function returns an iterator to the element before 
the current iterator position.
@params: The function gets an iterator.
@return: The function returns an iterator to the previous element.
@errors:
*/
srtlist_iter_t SrtListPrev(srtlist_iter_t iterator);


/*Description: The function gets an iterator and returns the data.
@params: The function gets an interators. 
@return: The function return void pointer.
@errors: 
*/
void *SrtListGetData(const srtlist_iter_t iterator);


/*Description: The functions inserts a new element to the sorted list.
@params: The function gets sorted list and the data to be inserted.
@return: srtlist_iter_t if success or Dummy if malloc fail.
@errors: malloc fail.
*/
srtlist_iter_t SrtListInsert(srtlist_t *list, void *data);


/*Description: The function removes an element from the list.
@params: The function gets an iterator to the element to be removed.
@return: srtlist_iter_t
@errors: 
*/
srtlist_iter_t SrtListRemove(srtlist_iter_t iterator);


/*Description: The function removes an element from beginning of the list.
@params: The function gets a pointer to the list.
@return: void pointer to the data.
@errors: 
*/
void *SrtListPopFront(srtlist_t *list);


/*Description: The function removes an element from end of the list.
@params: The function gets a pointer to the list.
@return: void pointer to the data.
@errors: 
*/
void *SrtListPopBack(srtlist_t *list);


/*Description: The function returns the number of items stored in the list.
@params: The function gets a pointer to the list.
@return: The function returns the number of items in the list.
@errors: 
*/
size_t SrtListSize(const srtlist_t *list);


/*Description: The function checks if list is empty. 
@params: The function gets a pointer to the list.
@return: The function returns an int - 1 for TRUE, 0 for FALSE.
@errors:
*/
int SrtListIsEmpty(const srtlist_t *list);


/*Description: The function returns iterator to the head of the list.
@params: The function gets a pointer list.
@return: The function returns an iterator.
@errors:
*/
srtlist_iter_t SrtListBegin(const srtlist_t *list);

/*Description: The function returns iterator to the tail of the list.
@params: The function gets a pointer list.
@return: The function returns an iterator.
@errors:
*/
srtlist_iter_t SrtListEnd(const srtlist_t *list);


/*Description: The function invokes func_ptr for each element in the mentioned range. 
@params: A function pointer, iterator start and end and void *param.
return: returns 0 for SUCCESS, 1 for FAIL if actaion_func didn't work on all the elements.
@errors:
*/
int SrtListForeach(srtlist_iter_t from, srtlist_iter_t to , action_func_t actaion_func, void *param);


/*Description: The function finds the first element in the list.
@params: The function gets a pointer to the list, a range, compare function and void *param.
@return: The function returns an iterator that points to the data or Dummy if data is not in the list.
@errors: 
*/
srtlist_iter_t SrtListFind(srtlist_iter_t from, srtlist_iter_t to, const void *to_find); 


/*Description: The function finds the first element in the list.
@params: The function gets a pointer to the list, a range, compare function and void *param.
@return: The function returns an iterator that points to the data or Dummy if data is not in the list.
@errors: 
*/
srtlist_iter_t SrtListFindIf(srtlist_iter_t from, srtlist_iter_t to, is_match_t is_match, void *param); 


/*Description: The function merges two sorted lists.
@params: The function gets a pointer to the dest list and src list
@return: 
@errors: 
*/
void SrtListMerge(srtlist_t *dest, srtlist_t *src);



#endif /* __SRTLIST_H__ */
