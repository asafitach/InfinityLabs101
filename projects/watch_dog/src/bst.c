#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include "bst.h"

/******************************************************************************/

typedef enum children
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILDREN
}children_t;

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

typedef enum insert_stat
{
	SMALL,
	BIG,
	END,
	FIRST
}insert_stat_t;

typedef enum find_status
{
	FIND,
	INSERT
}find_status_t;

/***************************** tools for c ************************************/
static bst_node_t *GoRight(bst_node_t *node)
{
	assert(NULL != node);
	return (node->children[RIGHT]);
}

static bst_node_t *GoLeft(bst_node_t *node)
{
	assert(NULL != node);
	return (node->children[LEFT]);
}

static bst_node_t *GoUp(bst_node_t *node)
{
	assert(NULL != node);
	return (node->parrent);
}

static void DisconnectChiled(bst_node_t *cur_node)
{
	if (cur_node->parrent->children[RIGHT] == cur_node)
	{
		cur_node->parrent->children[RIGHT] = NULL;
	}
	
	else /*if (cur_node->parrent->children[LEFT] == cur_node)*/
	{
		cur_node->parrent->children[LEFT] = NULL;
	}
		
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
	
	tree->root_stub.data = NULL;
	tree->root_stub.parrent = NULL;
	for (index = 0; index < NUM_OF_CHILDREN; ++index)
	{
		tree->root_stub.children[index] = NULL;
	}

	return (tree);
}

/******************************************************************************/

void BstDestroy(bst_t *tree)
{
	bst_node_t *cur_node = NULL;
	bst_node_t *parrent = NULL;
	
	assert(NULL != tree);
	
	cur_node = BstBegin(tree);
	while (1 != BstIsEmpty(tree))
	{
		if (NULL == cur_node->children[LEFT] && NULL == cur_node->children[RIGHT])
		{
			parrent = cur_node->parrent;
			DisconnectChiled(cur_node);
			free(cur_node);
			cur_node = parrent;
		}
		
		else
		{
			if (NULL != cur_node->children[RIGHT])
			{
				cur_node = cur_node->children[RIGHT];
			}
			else
			{
				cur_node = cur_node->children[LEFT];
			}
		}
	}
	
	free(tree);
}

/******************************************************************************/
/* this function deals with insertion to the right place in the tree. 
in the base case this function called from the function "find in tree" 
which findes the right place to insert this new node. */
static bst_node_t *NewNode(void *data, bst_node_t *parrent, insert_stat_t status)
{
	size_t index = 0;
	bst_node_t *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}
	
	new_node->parrent = parrent;
	new_node->data = data;
	
	for (index = 0; index < NUM_OF_CHILDREN; ++index)
	{
		new_node->children[index] = NULL;
	}

	if (FIRST == status)/*tree is empty*/
	{
		parrent->children[LEFT] = new_node;
		return (new_node);
	}
	if (END == status)/*this node is the last node - there is no node more valueble then it.*/
	{
		new_node->children[RIGHT] = parrent->children[RIGHT];
		parrent->children[RIGHT] = new_node;
	}
	else if (BIG == status)
	{
		parrent->children[RIGHT] = new_node;
	}
	else
	{
		parrent->children[LEFT] = new_node;
	}

	return (new_node);
}

/* this function find the right place for insertion (when status == INSERT)
or if a particular data exist in the tree*/
static bst_node_t *FindInTree(bst_t *tree, void *data, find_status_t status)/*add commant*/
{
	bst_node_t *end = &(tree->root_stub);
	bst_node_t *cur_node = end->children[LEFT];
	bst_node_t *next_node = cur_node;
	cmp_func_t cmp_func = tree->cmp_func;
	void *param = tree->param;
	int res = 0;

	assert(NULL != tree);

	while (next_node != end && NULL != next_node)
	{
		cur_node = next_node;
		res = cmp_func(cur_node->data, data, param);
		if (res > 0)
		{
			next_node = GoRight(next_node);
		}
		else if (0 == res)
		{
			return (cur_node);
		}
		else
		{
			next_node = GoLeft(next_node);
		}
	}

	if (status == FIND)
	{
		return (NULL);
	}
	if (next_node == end)/*(status == INSERT)*/
	{
		return (NewNode(data, cur_node, END));
	}

	if (res > 0)
	{
		return (NewNode(data, cur_node, BIG));
	}
	return (NewNode(data, cur_node, SMALL));
}

/******************************************************************************/

bst_iter_t BstInsert(bst_t *tree, void *data)
{
	assert(NULL != tree);
	assert(NULL != data);

	if (1 == BstIsEmpty(tree))
	{
		return (NewNode(data, &(tree->root_stub), FIRST));
	}

	return (FindInTree(tree, data, INSERT));/*findes the right place and call NewNode function*/
}


/******************************************************************************/

void BstRemove(bst_iter_t iterator)
{
	bst_node_t *replace = NULL;

	if (NULL == iterator->children[LEFT] && NULL == iterator->children[RIGHT])
	{
		DisconnectChiled(iterator);
		free(iterator);
		iterator = NULL;
		return;
	}

	if (NULL == iterator->children[LEFT] || NULL == iterator->children[RIGHT])
	{
		if (NULL == iterator->children[RIGHT])
		{
			if (iterator->parrent->children[LEFT] == iterator)
			{
				iterator->parrent->children[LEFT] = iterator->children[LEFT];
			}
			else
			{
				iterator->parrent->children[RIGHT] = iterator->children[LEFT];
			}	
		}
		else
		{
			if (iterator->parrent->children[LEFT] == iterator)
			{
				iterator->parrent->children[LEFT] = iterator->children[RIGHT];
			}
			else
			{
				iterator->parrent->children[RIGHT] = iterator->children[RIGHT];
			}	
		}
		free(iterator);
		return;
	}

	replace = BstPrev(iterator);
	replace->parrent->children[RIGHT] = NULL;
	iterator->data = replace->data;
	free(replace);
}

/******************************************************************************/

int Count(void *data, void *counter)
{
	assert(NULL != data);
	*(size_t *)counter = *(size_t *)counter + 1;

	return (0);
}

size_t BstSize(const bst_t *tree)
{
	size_t counter = 0;
	
	assert(NULL != tree);

	BstForeach(BstBegin(tree), BstEnd(tree), Count, (void *)&counter);

	return (counter);
}

/******************************************************************************/

bst_iter_t BstFind(const bst_t *tree, void *data)
{
	assert(NULL != tree);
	assert(NULL != data);

	return (FindInTree((bst_t *)tree, data, FIND));
}

/******************************************************************************/

bst_iter_t BstBegin(const bst_t *tree)
{
	bst_node_t *runner = NULL;
	assert(NULL != tree);

	if (BstIsEmpty(tree) == 1)
	{
		return (&((bst_t *)tree)->root_stub);
	}
	runner = tree->root_stub.children[0];

	while (NULL != GoLeft(runner))
	{
		runner = GoLeft(runner);
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


bst_node_t *PrevIsBelow(bst_iter_t runner)
{
	runner = GoLeft(runner);
	while (NULL != GoRight(runner))
	{
		runner = GoRight(runner);
	}
	return (runner);
}

bst_node_t *PrevIsAbove(bst_iter_t runner)
{
	bst_node_t *parrent = GoUp(runner);

	while (runner == GoLeft(parrent))
	{
		parrent = GoUp(parrent);
		runner = GoUp(runner);
	}
	return (parrent);
}
/******************************************************************************/
bst_iter_t BstPrev(bst_iter_t iterator)
{
	bst_node_t *runner = iterator;
	
	assert(NULL != iterator);
	
	/*prev is below*/
	if (NULL != GoLeft(runner))
	{
		return (PrevIsBelow(runner));
	}

	/*prev is above*/
	return (PrevIsAbove(runner));
}

/******************************************************************************/

int BstIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);
	return ((tree->root_stub.children[LEFT] == NULL) ? 1 :0);
}
/******************************************************************************/

int BstForeach(bst_iter_t from, bst_iter_t to , action_func_t action_func, void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);

	while (from != to)
	{
		if (1 == action_func(BstGetData(from), param))
		{
			return (1);
		}
		from = BstNext(from);
	}
	return 0;
}
/******************************************************************************/

int BstIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return(iter1 == iter2);
}

/********************************E.O.F*****************************************/