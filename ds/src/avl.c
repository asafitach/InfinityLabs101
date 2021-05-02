#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "utility.h"
#include "avl.h"

typedef enum children
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILDREN,
    EQUAL = -1
}children_t;


typedef struct avl_node 
{
	void *data;
	size_t height;
	struct avl_node *children[NUM_OF_CHILDREN];
}avl_node_t;

struct avl
{
	cmp_func_t cmp_func;
	struct avl_node *root;
};

/**********************************************/
 
/***************************** operation functions **********************************/


static void RecursiveDestroy(avl_node_t *root);
static avl_node_t *RecursiveInsert(avl_node_t *root, cmp_func_t cmp_func, void *data, avl_node_t *new_node);
static avl_node_t *NewNode(void *data);
static void FixHeight(avl_node_t *root);
static avl_node_t *BalanceCheck(avl_node_t *node);
static avl_node_t *Rebalance(avl_node_t *node, int node_balance);
static avl_node_t *RotateSide(avl_node_t *root, children_t side);
static int GetBalanceFactor(avl_node_t *node);
static size_t RootHeight(const avl_node_t *root);
static avl_node_t *RecursiveRemove(avl_node_t *root, void *data, cmp_func_t cmp_func, status_t *status);
static void *GetDataRight(avl_node_t *root);
static size_t RecursiveSize(avl_node_t *root);
static void *RecursiveFind(cmp_func_t cmp_func, avl_node_t *root, void *data);
static int InOrder(avl_node_t *root, action_func_t action_func, void *param);/*left root right*/
static int PostOrder(avl_node_t *root, action_func_t action_func, void *param);/*lefp right root*/
static int PreOrder(avl_node_t *root, action_func_t action_func, void *param);/*Root, Left, Right*/

/*********************************** create **********************************/

avl_t *AvlCreate(cmp_func_t cmp_func)
{
	avl_t *tree = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == tree)
	{
		return (NULL);
	}
	
    assert(NULL != cmp_func);

	tree->cmp_func = cmp_func;
	tree->root = NULL;
	
	return (tree);
}

/*********************************** destroy *********************************/

void AvlDestroy(avl_t *tree)
{
    assert(NULL != tree);

    if (NULL != tree->root)
    {
        RecursiveDestroy(tree->root);
    }

    free(tree);
    tree = NULL;
}

static void RecursiveDestroy(avl_node_t *root)
{
    if (NULL != root)
    {
        RecursiveDestroy(root->children[LEFT]);

        RecursiveDestroy(root->children[RIGHT]);
    }
    free(root);
}

/*********************************** insert **********************************/

status_t AvlInsert(avl_t *tree, void *data)
{
    avl_node_t *new_node = NULL;

    assert(NULL != tree);
    assert(NULL != data);

    new_node = NewNode(data);
    if (NULL == new_node)
    {
        return (FAIL);
    }
    tree->root = RecursiveInsert(tree->root, tree->cmp_func, data, new_node);

    return (SUCCESS);
}

static avl_node_t *RecursiveInsert(avl_node_t *root, cmp_func_t cmp_func, void *data, avl_node_t *new_node)
{
    int direction = 0;

    if (NULL == root)
    {
        return (new_node);
    }

    direction = cmp_func(root->data, data);

    root->children[direction] = RecursiveInsert(root->children[direction], cmp_func, data, new_node);

    FixHeight(root);
    root = BalanceCheck(root);

    return (root);
}

/* create new node with the spcific data and return it*/
static avl_node_t *NewNode(void *data)
{
    size_t index = 0;

    avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
    if (NULL == new_node)
    {
        return (NULL);
    }

    new_node->height = 1;
    new_node->data = data;

    for (index = 0; index < NUM_OF_CHILDREN; ++index)
    {
        new_node->children[index] = NULL;
    }
    return (new_node);
}

static void FixHeight(avl_node_t *root)
{
    if (NULL == root)
    {
        return;
    }

    root->height = 1 +
    MAX(
        (NULL != root->children[RIGHT] ? root->children[RIGHT]->height :0),
        (NULL != root->children[LEFT] ? root->children[LEFT]->height :0));
}

static avl_node_t *BalanceCheck(avl_node_t *node)
{
    int balance_factor = GetBalanceFactor(node);

    if (abs(balance_factor) > 1)
    {
        return (Rebalance(node, balance_factor));
    }

    return (node);
}

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

static avl_node_t *RotateSide(avl_node_t *root, children_t side)
{
	avl_node_t *child = root->children[!side];
	avl_node_t *grand_child = child->children[side];
	
	child->children[side] = root;
	root->children[!side] = grand_child;

	FixHeight(root);
	FixHeight(child);
	
	return (child);
}

static int GetBalanceFactor(avl_node_t *node)
{
    if (NULL == node)
    {
        return (0);
    }

    return ((int)RootHeight(node->children[LEFT]) - (int)RootHeight(node->children[RIGHT]));
}
static size_t RootHeight(const avl_node_t *root)
{	
	return (NULL != root ? root->height : 0);
}

/*********************************** remove **********************************/

status_t AvlRemove(avl_t *avl_tree, const void *data)
{
	status_t status = SUCCESS;
	
	void *tmp_data = (void *)data;
	
	assert(NULL != avl_tree);		

	avl_tree->root = RecursiveRemove(avl_tree->root, tmp_data, avl_tree->cmp_func, &status);
	
	return (status);	
}				

/********************************* AvlRemoveHelper *****************************/

static avl_node_t *RecursiveRemove(avl_node_t *root, void *data, cmp_func_t cmp_func, status_t *status)
{
	int direction = 0;
	children_t which_child_exists = LEFT;
	avl_node_t *temp_node = NULL;
	
	if (NULL == root)
	{
		*status = FAIL;
		
		return (NULL);
	}
	
	direction = cmp_func(root->data, data);
	
	if (EQUAL != direction)
	{
		root->children[direction] = RecursiveRemove(root->children[direction], data, cmp_func, status);
	}
	
	else if (NULL != root->children[LEFT] && NULL != root->children[RIGHT])
	{
		root->data = GetDataRight(root->children[RIGHT]);
		
		root->children[RIGHT] =  RecursiveRemove(root->children[RIGHT], root->data, cmp_func, status);
	}  
	
	else if (NULL != root->children[LEFT] || NULL != root->children[RIGHT])
	{
		which_child_exists = (NULL != root->children[LEFT] ? LEFT : RIGHT);
			
		temp_node = root->children[which_child_exists];
		root->data = temp_node->data;
		root->children[LEFT] = temp_node->children[LEFT];
		root->children[RIGHT] =  temp_node->children[RIGHT];
		
		free(temp_node);
	}
	else
	{
		free(root);
		root = NULL;
	}
	
	FixHeight(root);	
	
	*status = SUCCESS;
	
	root = BalanceCheck(root);
	
	return (root);
}

static void *GetDataRight(avl_node_t *root)
{
    if (NULL != root->children[RIGHT])
    {
        return (GetDataRight(root->children[RIGHT]));
    }
    return (root->data);
}

/*********************************** size ************************************/

size_t AvlSize(const avl_t *tree)
{
    assert(NULL != tree);

    return (RecursiveSize(tree->root));
}

static size_t RecursiveSize(avl_node_t *root)
{
    if (NULL != root)
    {
        return (RecursiveSize(root->children[LEFT]) + RecursiveSize(root->children[RIGHT]) + 1);
    }
    return (0);
}

/*********************************** find ************************************/

void *AvlFind(const avl_t *tree, const void *data)
{
    assert(NULL != tree);
    assert(NULL != data);

    if (NULL == tree->root)
    {
        return (NULL);
    }

    return (RecursiveFind(tree->cmp_func, tree->root, (void *)data));
}

static void *RecursiveFind(cmp_func_t cmp_func, avl_node_t *root, void *data)
{
    int cmp_res = 0;
    if (NULL == root)
    {
        return (NULL);
    }
    cmp_res = cmp_func(root->data, data);
    if (EQUAL == cmp_res)
    {
        return (root->data);
    }
    if (LEFT == cmp_res)
    {
        return(RecursiveFind(cmp_func, root->children[LEFT], data));
    }
    else/*(RIGHT == cmp_res)*/
    {
        return(RecursiveFind(cmp_func, root->children[RIGHT], data));
    }
}

/*********************************** is empty ********************************/

int AvlIsEmpty(const avl_t *tree)
{
    assert (NULL != tree);

    return ((NULL == tree->root) ? 1: 0);
}

/*********************************** for each ********************************/

int AvlForeach(avl_t *tree, action_func_t action_func, void *param, order_t order)
{
    assert(NULL != tree);
    assert(NULL != action_func);

    if (INORDER == order)
    {
        return (InOrder(tree->root, action_func, param));
    }
    if (POSTORDER == order)
    {
        return (PostOrder(tree->root, action_func, param));
    }
    return (PreOrder(tree->root, action_func, param));

}


static int InOrder(avl_node_t *root, action_func_t action_func, void *param)/*left root right*/
{
    if (NULL == root)
    {
        return (0);
    }
    if (NULL != root->children[LEFT])
    {
        InOrder(root->children[LEFT], action_func, param);
    }
    else
    {
        return (action_func(root->data, param));
    }
    if (0 != action_func(root->data, param))
    {
        return (1);
    }
    InOrder(root->children[RIGHT], action_func, param);
    return (0);
}

static int PostOrder(avl_node_t *root, action_func_t action_func, void *param)/*lefp right root*/
{
    if (NULL == root)
    {
        return (0);
    } 
    if (NULL != root->children[LEFT])
    {
        PostOrder(root->children[LEFT], action_func, param);
    }
    else
    {
        return (action_func(root->data, param));
    }
    PostOrder(root->children[RIGHT], action_func, param);
    if (0 != action_func(root->data, param))
    {
        return (1);
    }
    return (0);
}

static int PreOrder(avl_node_t *root, action_func_t action_func, void *param)/*Root, Left, Right*/
{
    if (NULL == root)
    {
        return (0);
    }
    if (0 != action_func(root->data, param))
    {
        return (1);
    }
    if (NULL != root->children[LEFT])
    {
        PreOrder(root->children[LEFT], action_func, param);
    }
    if (NULL != root->children[RIGHT])
    {
        PreOrder(root->children[RIGHT], action_func, param);
    }
    return (0);
}

/*********************************** height **********************************/

size_t AvlHeight(const avl_t *tree)
{
    assert (NULL != tree);

    if (NULL == tree->root)
    {
        return (0);
    }

    return (tree->root->height);
}


/*********************************** E.O.F. **********************************/

void RecursiveMirrorTree(avl_node_t *root)
{
    avl_node_t *tmp = NULL;

    if (NULL == root)
    {
        return;
    }

    tmp = root->children[LEFT];
    root->children[LEFT] = root->children[RIGHT];
    root->children[RIGHT] = tmp;

    RecursiveMirrorTree(root->children[RIGHT]);
    RecursiveMirrorTree(root->children[LEFT]);
}

void MirrorTree(avl_t *tree)
{
    assert(NULL != tree);

    RecursiveMirrorTree(tree->root);
}