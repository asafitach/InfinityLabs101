/*****************************************************************************/

#include <assert.h>   /* assert */
#include <stdlib.h>   /* malloc free abs */

/*****************************************************************************/

#include "avl.h"

#define LEFT_CHILD root->children[LEFT]
#define RIGHT_CHILD root->children[RIGHT]
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/*****************************************************************************/

typedef struct avl_node avl_node_t;

typedef enum children
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILDREN
} children_t;

typedef enum rotate_status
{
    DONT_ROTATE = 0,
    ROTATE_TO_LEFT = 1,
    ROTATE_TO_RIGHT = 2
} rotate_status_t;

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

/********************* service function signatures **********************/

static void *GetMin(avl_node_t *root);
static void AvlSetHeight(avl_node_t *root);
static int GetBalanceFactor(avl_node_t *node);
static avl_node_t *Balance(avl_node_t *node);
static avl_node_t *Balance(avl_node_t *node);
static avl_node_t *Balance(avl_node_t *node);
static size_t AvlSizeHelper(avl_node_t *root);
static int GetBalanceFactor(avl_node_t *node);
static avl_node_t *InitAvlTreeNode(void *data);
static void UpdateNodeHeight(avl_node_t *node);
static void AvlDestroyHelper(avl_node_t *root);
static size_t RootHeight(const avl_node_t *root);
static avl_node_t *RotateSide(avl_node_t *root, children_t side);
static avl_node_t *Rebalance(avl_node_t *node, int node_balance);
static void *AvlFindHelper(avl_node_t *root, const void *data, cmp_func_t cmp_func);
static avl_node_t *AvlInsertHelper(avl_node_t *root, void *data, cmp_func_t cmp_func);
static int AvlForeachHelper(avl_node_t *root, action_func_t action_func, void *param, order_t order);
static avl_node_t *AvlRemoveHelper(avl_node_t *root, void *data, cmp_func_t cmp_func, status_t *status);

/********************* AvlCreate ***************************/

avl_t *AvlCreate(cmp_func_t cmp_func)
{
	avl_t *avl_tree = NULL;
	
	assert(NULL != cmp_func);
	
	avl_tree = malloc(sizeof(avl_t));
	if (NULL == avl_tree)
	{
		return (NULL);
	}
	
	avl_tree->cmp_func = cmp_func;
	
	avl_tree->root = NULL;
	
	return (avl_tree);
}

/********************* AvlDestroy ***************************/

void AvlDestroy(avl_t *avl_tree)
{
	assert(NULL != avl_tree);
	
	if (NULL != avl_tree->root)
	{
		AvlDestroyHelper(avl_tree->root);
	}
	
	free(avl_tree);
	/*avl_tree = NULL !!! */
	
	return ;
}

/********************* AvlDestroyHelper ***************************/

static void AvlDestroyHelper(avl_node_t *root)
{
	if (NULL != root)
	{
		AvlDestroyHelper(LEFT_CHILD);
		
		AvlDestroyHelper(RIGHT_CHILD);
		
		free(root);
	}
	
	return ;
}

/********************* AvlInsert ***************************/

status_t AvlInsert(avl_t *avl_tree, void *data)
{
	avl_node_t *new_node = NULL;
	
	assert(NULL != avl_tree);
	
	new_node = AvlInsertHelper(avl_tree->root, data, avl_tree->cmp_func);
	
	if (new_node)/*NULL != new_node more readable !!! */
	{
		avl_tree->root = new_node;
		
		return (SUCCESS);
	}
	
	return (FAIL);
}

/********************* AvlInsertHelper ***************************/

static avl_node_t *AvlInsertHelper(avl_node_t *root, void *data, cmp_func_t cmp_func)
{
	int compare_result = 0;
	
	children_t goto_child_position = LEFT;
	
	if (NULL == root)
	{
		return (InitAvlTreeNode(data));
	}
	
	compare_result = cmp_func(data, root->data);
	
	goto_child_position = compare_result <= 0 ? LEFT : RIGHT;
	
	root->children[goto_child_position] = AvlInsertHelper(root->children[goto_child_position], data, cmp_func);
	
	if (NULL == root->children[goto_child_position])
	{
		return (NULL);
	}
	
	AvlSetHeight(root);
	
	root = Balance(root);

	return (root);
}

/********************* AvlSetHeight ***************************/

static void AvlSetHeight(avl_node_t *root)/*tranverse? !!!*/
{
	size_t height1 = 0;
	
	size_t height2 = 0;	
	
	if (NULL != root)
	{
		height1 = (NULL != RIGHT_CHILD ? RIGHT_CHILD->height : 0);
		
		height2 = (NULL != LEFT_CHILD ? LEFT_CHILD->height : 0);
		
		root->height = MAX(height1, height2) + 1;
	}
	
	return ;
}

/********************************* AvlRemove ***********************************/
	
status_t AvlRemove(avl_t *avl_tree, const void *data)
{
	status_t status = SUCCESS;
	
	void *tmp_data = (void *)data;
	
	assert(NULL != avl_tree);		

	avl_tree->root = AvlRemoveHelper(avl_tree->root, tmp_data, avl_tree->cmp_func, &status);
	
	return (status);	
}				

/********************************* AvlRemoveHelper *****************************/

static avl_node_t *AvlRemoveHelper(avl_node_t *root, void *data, cmp_func_t cmp_func, status_t *status)
{
	int compare_result = 0;
	
	children_t goto_child_position = LEFT;
	
	children_t which_child_exists = LEFT;
	
	avl_node_t *temp_node = NULL;
	
	if (NULL == root)
	{
		*status = FAIL;
		
		return (NULL);
	}
	
	compare_result = cmp_func(data, root->data);
	
	if (0 != compare_result)
	{
		goto_child_position = compare_result < 0 ? LEFT : RIGHT;
		
		root->children[goto_child_position] = AvlRemoveHelper(root->children[goto_child_position], data, cmp_func, status);
		
		AvlSetHeight(root);
		
		root = Balance(root);
		
		return (root);		
	}
	
	else if (NULL != LEFT_CHILD && NULL != RIGHT_CHILD)
	{
		root->data = GetMin(RIGHT_CHILD);
		
		RIGHT_CHILD =  AvlRemoveHelper(RIGHT_CHILD, root->data, cmp_func, status);
	}
	
	else if (NULL != LEFT_CHILD || NULL != RIGHT_CHILD)
	{
		which_child_exists = (NULL != LEFT_CHILD ? LEFT : RIGHT);
			
		temp_node = root->children[which_child_exists];
		
		root->data = temp_node->data;
		
		LEFT_CHILD = temp_node->children[LEFT];
		
		RIGHT_CHILD =  temp_node->children[RIGHT];
		
		free(temp_node);
	}
	else
	{
		free(root);
		root = NULL;
	}
	
	AvlSetHeight(root);	
	
	*status = SUCCESS;
	
	root = Balance(root);
	
	return (root);
}

/********************************* GetMin ***********************************/

static void *GetMin(avl_node_t *root)
{	
	assert(NULL != root);
	
	while (NULL != LEFT_CHILD)
	{
		root = LEFT_CHILD;
	}
	
	return (root->data);	
}

/********************************* AvlHeight ***********************************/

size_t AvlHeight(const avl_t *avl_tree)
{
	assert(NULL != avl_tree);
	
	return (RootHeight(avl_tree->root));
}

static size_t RootHeight(const avl_node_t *root)
{	
	return (NULL != root ? root->height : 0);/*-1 !!!*/
}

/********************************* AvlSize *************************************/

size_t AvlSize(const avl_t *avl_tree)
{    
    assert(NULL != avl_tree);

    return (AvlSizeHelper(avl_tree->root));	
}

/********************************* AvlSizeHelper *******************************/

static size_t AvlSizeHelper(avl_node_t *root)
{
    if (NULL != root)
    {
        return (1 + AvlSizeHelper(LEFT_CHILD) + AvlSizeHelper(RIGHT_CHILD));
    }
    
    return (0);	
}

/********************************* AvlFind *******************************/

void *AvlFind(const avl_t *avl_tree, const void *data)
{
	assert(NULL != avl_tree);
	
	return (AvlFindHelper(avl_tree->root, data, avl_tree->cmp_func));
}
	
/********************************* AvlFindHelper *******************************/

static void *AvlFindHelper(avl_node_t *root, const void *data, cmp_func_t cmp_func)
{
	int compare_result = 0;
	
	children_t goto_child_position = LEFT;
	
	if (NULL == root)
	{
		return (NULL);
	}
	
	compare_result = cmp_func(data, root->data);
	
	if (0 == compare_result)
	{
		return (root->data);
	}
	
	goto_child_position = compare_result < 0 ? LEFT : RIGHT;
	
	return (AvlFindHelper(root->children[goto_child_position], data, cmp_func));
}

/********************* AvlIsEmpty ***************************/

int AvlIsEmpty(const avl_t *avl_tree)
{
	assert(NULL != avl_tree);
	
	return (!avl_tree->root);
}

/********************* BstForeach ***************************/

int AvlForeach(avl_t *avl_tree, action_func_t action_func, void *param, order_t order)
{
	assert(NULL != avl_tree);
	assert(NULL != action_func);
	
	return (AvlForeachHelper(avl_tree->root, action_func, param, order));
}

/********************* AvlForeachHelper ***************************/

static int AvlForeachHelper(avl_node_t *root, action_func_t action_func, void *param, order_t order)
{
	static int count_success = 0;
	
	if (NULL == root)
	{
		return (0);
	}
	
	switch (order)
	{
		case INORDER:
			
		AvlForeachHelper(LEFT_CHILD, action_func, param, order);
		
		count_success += (0 == action_func(root->data, param) ? 1 : 0);
		
		AvlForeachHelper(RIGHT_CHILD, action_func, param, order);
		
		break;
		
		case PREORDER:
		
		count_success += (0 == action_func(root->data, param) ? 1 : 0);
		
		AvlForeachHelper(LEFT_CHILD, action_func, param, order);
		
		AvlForeachHelper(RIGHT_CHILD, action_func, param, order);
		
		break;
		
		case POSTORDER:
		
		AvlForeachHelper(LEFT_CHILD, action_func, param, order);
		
		AvlForeachHelper(RIGHT_CHILD, action_func, param, order);
		
		count_success += (0 == action_func(root->data, param) ? 1 : 0);
		
		break;
		
		default:
			
			break;
	}
	
	return (count_success);
}

/********************* service function InitBstNode ***************************/

static avl_node_t *InitAvlTreeNode(void *data)
{
	avl_node_t *new_node = malloc(sizeof(avl_node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}
	
	new_node->data = data;
	
	new_node->height = 1;/*i think it's height is 0 and not 1 !!!*/
	
	new_node->children[LEFT] = NULL;
	
	new_node->children[RIGHT] = NULL;
	
	return (new_node);
}

/*****************************************************************************/

static int GetBalanceFactor(avl_node_t *node)
{
    if (NULL == node)
    {
        return (0);
    }

    return ((int)RootHeight(node->children[LEFT]) - (int)RootHeight(node->children[RIGHT]));
}

/*****************************************************************************/

static avl_node_t *Balance(avl_node_t *node)
{
    int node_balance = GetBalanceFactor(node);

    if (abs(node_balance) > 1)
    {
        return (Rebalance(node, node_balance));
    }

    return (node);
}

/*****************************************************************************/

static avl_node_t *Rebalance(avl_node_t *node, int node_balance)
{
    if (node_balance > 1)
    {
        if (GetBalanceFactor(node->children[LEFT]) < 0)
        {
            node->children[LEFT] = RotateSide(node->children[LEFT], LEFT);
        }

        return (RotateSide(node, RIGHT));
    }

    if (GetBalanceFactor(node->children[RIGHT]) > 0)
    {
        node->children[RIGHT] = RotateSide(node->children[RIGHT], RIGHT);
    }

    return (RotateSide(node, LEFT));   
}

/*****************************************************************************/

static avl_node_t *RotateSide(avl_node_t *root, children_t side)
{
	avl_node_t *child = root->children[!side];
	avl_node_t *grand_child = child->children[side];
	
	child->children[side] = root;
	root->children[!side] = grand_child;

	UpdateNodeHeight(root);
	UpdateNodeHeight(child);
	
	return (child);
}

/*****************************************************************************/

static void UpdateNodeHeight(avl_node_t *node)
{
    node->height = 1 + MAX(RootHeight(node->children[LEFT]), RootHeight(node->children[RIGHT]));
}


/********************* end ***************************/
