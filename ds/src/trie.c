#include <assert.h>   /* assert */
#include <stddef.h>   /* NULL size_t */
#include <stdlib.h>   /* malloc free */

#include "trie.h"

#define LEFT_CHILD root->children[LEFT]

#define RIGHT_CHILD root->children[RIGHT]

#define CHILD root->children[bit]

#define MASK 1

/********************* manegment structs and enums ***************************/

typedef enum children
{
    LEFT = 0,
    RIGHT,
    NUM_OF_CHILDREN 
}children_t;

struct trie
{
    trie_node_t *root;
    size_t num_of_input_bits; 
    size_t num_of_nodes; 
};

struct trie_node
{
    int is_occupied;
	trie_node_t *parent;
	trie_node_t *children[NUM_OF_CHILDREN];
};



/********************* service function signitures ***************************/


static void TrieDestroyHelper(trie_node_t *root);

static trie_node_t *CreateTrieNode(trie_node_t *parent);

static void SetOccupied(trie_node_t *child);

static trie_status_t FindNext(trie_node_t *root, size_t num_of_input_bits, size_t *data_ptr, size_t tmp_data, size_t i);
static size_t Reverse(size_t data, size_t num_of_input_bits);



/********************* Api functions definition ***************************/

trie_t *TrieCreate(size_t num_of_input_bits)
{
    trie_t *trie = (trie_t *)malloc(1 * sizeof(trie_t));
    if (NULL == trie)
    {
        return (NULL);
    }
    
    trie->root = CreateTrieNode(NULL);
    if (NULL == trie->root)
    {
        free(trie);
        trie = NULL;

        return (NULL);
    }

    trie->num_of_input_bits = num_of_input_bits;

    trie->num_of_nodes = 0;

    return (trie);
}

/********************* TrieDestroy ***************************/

void TrieDestroy(trie_t *trie)
{
	assert(NULL != trie);
	
	if (NULL != trie->root)
	{
		TrieDestroyHelper(trie->root);
	}
	
	free(trie);
	trie = NULL;
	
	return ;
}

/********************* TrieDestroyHelper ***************************/

static void TrieDestroyHelper(trie_node_t *root)
{
	if (NULL != root)
	{
		TrieDestroyHelper(LEFT_CHILD);
		
		TrieDestroyHelper(RIGHT_CHILD);
		
		free(root);
        root = NULL;
	}
	
	return ;
}

/********************* TrieInsert ***************************/

trie_status_t TrieInsert(trie_t *trie, size_t data)
{
    size_t bit = 0;

    trie_node_t *root = NULL;

    size_t i = 0;

    assert(NULL != trie);

    root = trie->root;

    for(i = 0; i < trie->num_of_input_bits; i++)
    {
         if (1 == root->is_occupied)  /* if occupied */
        {
            return (PATH_OCCUPIED);
        }

        bit = (data >> i) & MASK;

        if (NULL == CHILD)  /* if not exsits and not occupied */
        {
            CHILD = CreateTrieNode(root);

            if (NULL == CHILD)
            {
                return (MALLOC_FAIL);
            }
        }

        root = CHILD;
    }

    if (1 == root->is_occupied)  /* checks if the last node is occupied */
    {
        return (PATH_OCCUPIED);
    }

    SetOccupied(root);

    trie->num_of_nodes++;

    return (SUCCESS);
}

trie_status_t TrieRemove(trie_t *trie, size_t data)
{    
    trie_node_t *root = NULL;
    unsigned int bit = 0;
    size_t num_of_elements = 0;
    
    assert(NULL != trie);
    
    root = trie->root;
    num_of_elements = trie->num_of_input_bits;
    
    while (num_of_elements)
    {
        bit = data & MASK;
        data >>= 1;
        if (NULL == CHILD)
        {
            return (PATH_INVALID);
        }
        root = CHILD;
        --num_of_elements;
    }
    
    if (0 == root->is_occupied)
    {
        return (PATH_INVALID);
    }
    
    while (NULL != root && 1 == root->is_occupied)
    {
        root->is_occupied = 0;
        root = root->parent;
    }
    --trie->num_of_input_bits;
    return (SUCCESS);
}

int TrieIsFound(const trie_t *trie, size_t data)
{
    size_t bit = 0;

    trie_node_t *root = NULL;

    size_t i = 0;

    assert(NULL != trie);

    root = trie->root;

    for(i = 0; i < trie->num_of_input_bits; i++)
    {
        bit = (data >> i) & MASK;

        if (NULL == CHILD)  /* if not exsits */
        {
            return (0);
        }

        root = CHILD;
    }

    if (0 == root->is_occupied)
    {
        return (0);
    }

    return (1);
}  

/********************* TrieCount ***************************/

size_t TrieCount(const trie_t *trie)
{
    assert(NULL != trie);

    return (trie->num_of_nodes);
}

/********************* comment ***************************/

trie_status_t TrieNextAvailable(const trie_t *trie, size_t *data_ptr)
{
    size_t data = *data_ptr;
    
    size_t bit = 0;
    
    size_t tmp_data = 0;

    trie_node_t *root = NULL;

    size_t i = 0;

    assert(NULL != trie);

    root = trie->root;
    
    if (1 == root->is_occupied)  /* if trie is full*/
    {
        return (TRIE_FULL);
    }

    for (i = 0; i < trie->num_of_input_bits; i++)
    {
        bit = (data >> i) & MASK;
    
        if (NULL != CHILD && 1 == CHILD->is_occupied)  /* if occupied */
        {
            return (FindNext(CHILD, trie->num_of_input_bits, data_ptr, tmp_data, i)); 
        }
        
        root = CHILD;
        tmp_data |= bit;
        tmp_data <<= MASK;
    }
    
    
    return (FindNext(root,trie->num_of_input_bits, data_ptr, tmp_data, i));
    
}

/********************* comment ***************************/

static trie_status_t FindNext(trie_node_t *root, size_t num_of_input_bits, size_t *data_ptr, size_t tmp_data, size_t i)
{
    tmp_data >>= MASK;
    --i;
    root = root->parent;
    
    while (NULL != root && NULL != RIGHT_CHILD && 1 == RIGHT_CHILD->is_occupied)
    {
        root = root->parent;
        tmp_data >>= MASK;
        --i;
    }
    
    if (NULL == root)
    {
        return (TRIE_FULL);
    }
    
    tmp_data <<= MASK;
    tmp_data |= MASK;
    ++i;
    root = RIGHT_CHILD;
    
    for (; i < num_of_input_bits; ++i)
    {
         if (NULL == root)
        {
            tmp_data = Reverse(tmp_data << (num_of_input_bits - i), num_of_input_bits);
            *data_ptr = tmp_data;
            return (SUCCESS);
        }

        if (NULL == LEFT_CHILD)
        {
            tmp_data = Reverse(tmp_data << (num_of_input_bits - i - 1), num_of_input_bits);
            *data_ptr = tmp_data;
            return (SUCCESS);
        }
        else if (0 == LEFT_CHILD->is_occupied)
        {
            root = LEFT_CHILD;
            tmp_data <<= MASK;
        }
        else if (NULL == RIGHT_CHILD)
        {
            tmp_data <<= MASK;
            tmp_data |= MASK;
            tmp_data = Reverse(tmp_data << (num_of_input_bits - i - 2), num_of_input_bits);
            *data_ptr = tmp_data;
            return (SUCCESS);
        }
        else
        {
            root = RIGHT_CHILD;
            tmp_data <<= MASK;
            tmp_data |= MASK;
        }
    }
    
    *data_ptr = Reverse(tmp_data , num_of_input_bits);
    
    return (SUCCESS);
}

static size_t Reverse(size_t data, size_t num_of_input_bits)
{
    size_t reversed_data = 0;

    while (num_of_input_bits > 0)
    {
        reversed_data <<= MASK;

        reversed_data |= data & MASK;

        data >>= MASK; 

        --num_of_input_bits;
    }

    return (reversed_data);
}

/********************* CreateTrieNode( ***************************/

static trie_node_t *CreateTrieNode(trie_node_t *parent)
{
    trie_node_t *new_trie_node = (trie_node_t *)malloc(1 * sizeof(trie_node_t));
    if (NULL == new_trie_node)
    {
        return (NULL);
    }

    new_trie_node->is_occupied = 0;

    new_trie_node->children[LEFT] = NULL;

    new_trie_node->children[RIGHT] = NULL;

    new_trie_node->parent = parent;

    return (new_trie_node);  
}

static void SetOccupied(trie_node_t *child)
{
    trie_node_t *parent = NULL;

    trie_node_t *left_child = NULL;

    trie_node_t *right_child = NULL;

    assert(NULL != child);

    child->is_occupied = 1;

    parent = child->parent;

    while (NULL != parent)
    {
        left_child = parent->children[LEFT];

        right_child = parent->children[RIGHT];

        if (child == left_child && NULL != right_child && 1 == right_child->is_occupied) /* the current child occupied is the left one\
                                                                                            and the right one exists and occupied */ 
        {
            parent->is_occupied = 1;
        }
        else if (child == right_child && NULL != left_child && 1 == left_child->is_occupied) /* the current child occupied is the right one\
                                                                                             and the left one exists and occupied */ 
        {
            parent->is_occupied = 1;
        }
        else
        {
            return ;    /* do nothing and return */
        }

        child = parent;         /* move up the trie */

        parent = child->parent;
    }

    return ;
}