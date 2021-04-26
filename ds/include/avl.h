#ifndef __avl_H__
#define __avl_H__

#include <stddef.h>  /* size_t */

typedef struct avl avl_t;

typedef int(*cmp_func_t)(const void *data1, const void *data2);
typedef int(*action_func_t)(void *data, void *param);

/****************************c file *************/

typedef struct avl_node avl_node_t;

typedef enum children
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILDREN
}children_t;

typedef enum order
{
	INORDER = 0,
	PREORDER,
	POSTORDER
	
}order_t;

struct avl_node 
{
	void *data;
	size_t height;
	avl_node_t *children[NUM_OF_CHILDREN];
};

struct avl
{
	cmp_func_t cmp_func;
	avl_node_t *root;
	
};

/**********************************************/
                
typedef enum 
{
	SUCCESS = 0,
	FAIL = 1
} status_t;   


avl_t *AvlCreate(cmp_func_t cmp_func);

/*Description: The function creates a avl_t *tree data structure.
@return: The function returns a pointer to avl_t *tree.
@errors: Returns NULL if malloc fails.

*/
void AvlDestroy(avl_t *tree);

/*Description: The function frees all the elements in the avl_t *tree.
@params: The function gets a pointer to the avl_t *tree.*/

status_t AvlInsert(avl_t *tree, void *data);

/*Description: The functions inserts a void *data and places by oreder and balances the avl_t *tree.
@params: The function gets a pointer to the avl_t *tree and the data to be inserted.
@return: status_t if malloc fails
@errors: malloc fail.*/

status_t AvlRemove(avl_t *tree, const void *data);

/*Description: The function removes void *data from the avl_t *tree.
@params: The function gets void *data to be removed and a pointer to the avl_t *tree.
@return: status_t 
@errors: 
*/

size_t AvlSize(const avl_t *tree);


/*Description: The function returns the number of items stored in the avl_t *tree.
@params: The function gets a pointer to the avl_t *tree.
@return: The function returns the number of items in the avl.
@errors: 
*/

void *AvlFind(const avl_t *tree, const void *data); 

/*Description: The function finds the void *data element in the avl.
@params: The function gets a pointer to the avl.
@return: The function returns void *data to the data or NULL
if data is not in the avl.
@errors: 
*/

int AvlIsEmpty(const avl_t *tree);

/*Description: The function checks if avl is empty. 
returns 1 for TRUE, 0 for FALSE.
@params: The function a pointer to the avl.
@return: The function returns an int (BOOLEAN).
@errors:
*/

int AvlForeach(avl_t *tree, action_func_t action_func, void *param, order_t order);

/*Description: The function invokes func_ptr for all the elements in the tree. 
@params: A function pointer, void *param and the order of invoking(post/pre/in).
@return: int, 0 for success, 1 if one of the actions has failed
@errors:
*/

size_t AvlHeight(const avl_t *tree);

/*Description: The function returns the hight of the avl.
@params: The function gets a pointer to the avl.
@return: The function returns the height of the avl.
@errors: 
*/

#endif /* __avl_H__ */
