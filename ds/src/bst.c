#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include "bst.h"




/******************************************************************************/

struct bst_node 
{
	void *data;
	struct bst_node *parrent;
	struct bst_node *children[NUM_OF_CHILDREN];
};


struct bst
{
	cmp_func_t cmp_func;
	void *param;
	bst_node_t root_stub;
};

/***************************** tools for c ************************************/
bst_node_t *GoRight(bst_node_t *node)
{
	return (node->children[RIGHT]);
}

bst_node_t *GoLeft(bst_node_t *node)
{
	return (node->children[LEFT]);
}

bst_node_t *GoUp(bst_node_t *node)
{
	return (node->parrent);
}
/******************************************************************************/

bst_t *BstCreate(cmp_func_t cmp_func, void *param)
{
	size_t index = 0;
	bst_t *tree = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == tree)
	{
		return (NULL);
	}
	
	tree->cmp_func = cmp_func;
	tree->param = param;
	
	tree->root_stub.data = (void *)tree;
	tree->root_stub.parrent = NULL;
	tree->root_stub.children[LEFT] = &(tree->root_stub);
	for (index = 1; index < NUM_OF_CHILDREN; ++index)
	{
		tree->root_stub.children[index] = NULL;
	}

	return (tree);
}

/******************************************************************************/

void BstDestroy(bst_t *tree)
{
	/*BstForeach(tree, BstRemove, NULL);*/
	free(tree);
}
	

/******************************************************************************/
bst_node_t *NewNode(void *data)
{
	size_t index = 0;
	bst_node_t *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}

	for (index = 0; index < NUM_OF_CHILDREN; ++index)
	{
		new_node->children[index] = NULL;
	}

	new_node->data = data;

	return (new_node);
}
/******************************************************************************/

bst_iter_t BstInsert(bst_t *tree, void *data)
{
	bst_node_t *new_node = NULL;
	bst_node_t *cur_node = NULL;
	bst_node_t *next_node = NULL;
	bst_node_t *end = NULL;
	cmp_func_t cmp_func = NULL;
	void *param = NULL;
	int res = 0;

	assert(NULL != tree);
	assert(NULL != data);

	new_node = NewNode(data);
	if (NULL == new_node)
	{
			return (NULL);
	}
/*PARRENT!!!!*/
	param = tree->param;
	cmp_func = tree->cmp_func;
	end = &(tree->root_stub);
	cur_node = tree->root_stub.children[LEFT];
	next_node = cur_node;

	while (next_node != end && NULL != next_node)
	{
		cur_node = next_node;
		res = cmp_func(cur_node->data, data, param);
		if (res > 0)
		{
			next_node = GoRight(next_node);
		}
		else
		{
			next_node = GoLeft(next_node);
		}
	}

	new_node->parrent = cur_node;
	if (next_node == end)
	{
		new_node->children[RIGHT] = end;
	}

	if (res > 0)
	{
		cur_node->children[RIGHT] = new_node;
	}
	else
	{
		cur_node->children[LEFT] = new_node;
	}

	return (new_node);
}

/******************************************************************************/

/*Description: The function removes an element from the bst.
@params: The function gets an iterator to the element to be removed and a pointer to the tree.
@return: iterator 
@errors: 
*/
void BstRemove(bst_iter_t iterator)
{

}

/******************************************************************************/

/*Description: The function gets an iterator and returns the data at the 
location.
@params: The function gets an interators. 
@return: The function return int.
@errors: 
*/

void *BstGetData(bst_iter_t iterator)
{
	assert(NULL != iterator);
	return (iterator->data);
}
/******************************************************************************/

/*Description: The function returns the number of items stored in the bst.
@params: The function gets a pointer to the bst.
@return: The function returns the number of items in the bst.
@errors: 
*/
size_t BstSize(const bst_t *tree);

/******************************************************************************/

/*Description: The function finds and element in the bst.
@params: The function gets a pointer to the bst.
@return: The function returns an iterator that points to the data or NULL
if data is not in the bst.
@errors: 
*/
bst_iter_t BstFind(const bst_t *tree, void *data);
/******************************************************************************/

/*Description: The function returns iterator to the head of the bst.
@params: The function gets a pointer bst.
@return: The function returns an iterator.
@errors:
*/
bst_iter_t BstBegin(const bst_t *tree)
{
	bst_node_t *runner = NULL;
	bst_node_t *runner_next = NULL;

	assert(NULL != tree);

	if (BstIsEmpty(tree) == 1)
	{
		return (NULL);
	}
	runner = tree->root_stub.children[0];
	runner_next = runner;

	while (NULL != runner_next)
	{
		runner = runner_next;
		runner_next = GoLeft(runner);
	}

	return(runner);		
}

/******************************************************************************/


bst_iter_t BstEnd(const bst_t *tree)
{
	bst_t *tmp = (bst_t *)tree;
	assert(NULL != tree);
	return (&(tmp->root_stub));
}
/******************************************************************************/

bst_node_t *NextIsBelow(bst_iter_t runner)
{
	runner = GoRight(runner);
	while (NULL != GoLeft(runner))
	{
		runner = GoLeft(runner);
	}
	return (runner);
}

bst_node_t *NextIsAbove(bst_iter_t runner)
{
	bst_node_t *parrent = GoUp(runner);

	while (runner == GoRight(parrent))
	{
		parrent = GoUp(parrent);
		runner = GoUp(runner);
	}
	return (parrent);
}
/******************************************************************************/
bst_iter_t BstNext(bst_iter_t iterator)
{
	bst_node_t *runner = iterator;
	
	assert(NULL != iterator);
	
	/*next is below*/
	if (NULL != GoRight(runner))
	{
		return (NextIsBelow(runner));
	}

	/*next is above*/
	return (NextIsAbove(runner));
}

/******************************************************************************/

/*Description: The function returns an iterator to the n element before 
the current iterator position.
@params: The function gets an iterator and n.
@return: The function returns an iterator.
@errors:
*/

bst_iter_t BstPrev(bst_iter_t iterator);
/******************************************************************************/

/*Description: The function checks if bst is empty. 
returns 1 for TRUE, 0 for FALSE.
@params: The function a pointer to the bst.
@return: The function returns an int (BOOLEAN).
@errors:
*/

int BstIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);
	return ((bst_iter_t)&(tree->root_stub) == tree->root_stub.children[0]);
}
/******************************************************************************/

/*Description: The function invokes func_ptr for each element in the mentioned range. 
@params: A function pointer, iterator start and end.
@return: int, 0 for success, 1 if one of the actions has failed
@errors:
*/

int BstForeach(bst_iter_t from, bst_iter_t to , action_func_t action_func, void *param);
/******************************************************************************/

/*Description: The function checks if the 2 iterators are equal. 
returns 1 for TRUE, 0 for FALSE.
@params: The function a pointer to 2 iterators.
@return: The function returns an int (BOOLEAN).
@errors:
*/

int BstIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return(BstGetData(iter1) == BstGetData(iter2));
}
/********************************E.O.F*****************************************/
