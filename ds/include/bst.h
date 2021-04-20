#ifndef __BST_H__
#define __BST_H__

#include <stddef.h>  /* size_t */

typedef enum children
{
	LEFT = 0,
	RIGHT =  1,
	NUM_OF_CHILDREN = 2
}children_t;

typedef struct bst_node bst_node_t;
typedef bst_node_t* bst_iter_t; 
typedef struct bst bst_t;

typedef int(*cmp_func_t)(const void *data1, const void *data2, const void *param);
typedef int(*action_func_t)(void *data, void *param);



/*Description: The function creates a new binary tree data structure.
@return: The function returns a pointer to bst_t structure.
@errors: Returns NULL if malloc fails.
*/

bst_t *BstCreate(cmp_func_t cmp_func, void *param);


/*Description: The function frees all the elements in the tree.
@params: The function gets a pointer to the binary tree.
*/
void BstDestroy(bst_t *tree);


/*Description: The functions inserts a new element and places it in the right place- left/right.
@params: The function gets a pointer to the tree and the data to be inserted.
@return: status_t
@errors: malloc fail.
*/
bst_iter_t BstInsert(bst_t *tree, void *data);


/*Description: The function removes an element from the bst.
@params: The function gets an iterator to the element to be removed and a pointer to the tree.
@return: iterator 
@errors: 
*/
void BstRemove(bst_iter_t iterator);


/*Description: The function gets an iterator and returns the data at the 
location.
@params: The function gets an interators. 
@return: The function return int.
@errors: 
*/

void *BstGetData(bst_iter_t iterator);

/*Description: The function returns the number of items stored in the bst.
@params: The function gets a pointer to the bst.
@return: The function returns the number of items in the bst.
@errors: 
*/
size_t BstSize(const bst_t *tree);


/*Description: The function finds and element in the bst.
@params: The function gets a pointer to the bst.
@return: The function returns an iterator that points to the data or NULL
if data is not in the bst.
@errors: 
*/
bst_iter_t BstFind(const bst_t *tree, void *data); 

/*Description: The function returns iterator to the head of the bst.
@params: The function gets a pointer bst.
@return: The function returns an iterator.
@errors:
*/
bst_iter_t BstBegin(const bst_t *tree);


/*Description: The function returns iterator to the tail of the bst.
@params: The function gets a pointer bst.
@return: The function returns an iterator.
@errors:
*/
bst_iter_t BstEnd(const bst_t *tree);

/*Description: The function returns an iterator to the n element after 
the current iterator position.
@params: The function gets an iterator and n.
@return: The function returns an iterator.
@errors:
*/

bst_iter_t BstNext(bst_iter_t iterator);


/*Description: The function returns an iterator to the n element before 
the current iterator position.
@params: The function gets an iterator and n.
@return: The function returns an iterator.
@errors:
*/

bst_iter_t BstPrev(bst_iter_t iterator);

/*Description: The function checks if bst is empty. 
returns 1 for TRUE, 0 for FALSE.
@params: The function a pointer to the bst.
@return: The function returns an int (BOOLEAN).
@errors:
*/

int BstIsEmpty(const bst_t *tree);

/*Description: The function invokes func_ptr for each element in the mentioned range. 
@params: A function pointer, iterator start and end.
@return: int, 0 for success, 1 if one of the actions has failed
@errors:
*/

int BstForeach(bst_iter_t from, bst_iter_t to , action_func_t action_func, void *param);

/*Description: The function checks if the 2 iterators are equal. 
returns 1 for TRUE, 0 for FALSE.
@params: The function a pointer to 2 iterators.
@return: The function returns an int (BOOLEAN).
@errors:
*/

int BstIterIsEqual(bst_iter_t iter1, bst_iter_t iter2);
#endif /* __BST_H__ */
