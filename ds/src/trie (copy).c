#include <assert.h>   /* assert */
#include <stddef.h>   /* NULL size_t */
#include <stdlib.h>   /* malloc free */
#include <stdio.h>

#include "trie.h"

#define LEFT_CHILD runner->children[LEFT]

#define RIGHT_CHILD runner->children[RIGHT]

#define CHILD runner->children[bit]

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
    size_t size; 
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

static trie_status_t FindNext(trie_node_t *runner, size_t num_of_input_bits, size_t *data_ptr, size_t tmp_data, size_t i);

static size_t Reverse(size_t data, size_t num_of_input_bits);

trie_node_t *CreatePath(trie_node_t *parrent, size_t level, size_t data);




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
        return (NULL);
    }

    trie->num_of_input_bits = num_of_input_bits;

    trie->size = 0;

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
	
}

/********************* TrieDestroyHelper ***************************/

static void TrieDestroyHelper(trie_node_t *runner)
{
	if (NULL != runner)
	{
		TrieDestroyHelper(LEFT_CHILD);
		
		TrieDestroyHelper(RIGHT_CHILD);
		
        free(runner);
	}
}

/********************* TrieInsert ***************************/

trie_status_t TrieInsert(trie_t *trie, size_t data)
{
    trie_node_t *runner = NULL;
    trie_node_t *parrent = NULL;
    size_t level = 0;
    size_t index = 0;

    assert(NULL != trie);

    runner = trie->root;
    level = trie->num_of_input_bits;
    index = level;

    while(level && NULL != runner)
    {
        parrent = runner;
        --level;
        runner = parrent->children[(data >> level) & 1];
    }

    if (!level && 1 == runner->is_occupied)
    {

        return (PATH_OCCUPIED);

    }

    if (level)
    {
        runner = CreatePath(parrent, level - 1, data);
        if (NULL == runner)
        {
            return (MALLOC_FAIL);
        }
    }

    SetOccupied(runner);

    return (SUCCESS);
}

trie_status_t TrieRemove(trie_t *trie, size_t data)
{    
    trie_node_t *runner = NULL;
    trie_node_t *parrent = NULL;
    size_t level = 0;
    size_t index = 0;

    assert(NULL != trie);

    runner = trie->root;
    level = trie->num_of_input_bits;
    index = level;

    while(level && NULL != runner)
    {
        parrent = runner;
        --level;
        runner = parrent->children[(data >> level) & 1];
    }

    if (!level && 1 == runner->is_occupied)
    {
        while (NULL != runner && 1 == runner->is_occupied)
        {
            runner->is_occupied = 0;
            runner = runner->parent;
        }

        return (SUCCESS);
    }

    return (PATH_INVALID);
}

int TrieIsFound(const trie_t *trie, size_t data)
{
    trie_node_t *runner = NULL;
    trie_node_t *parrent = NULL;
    size_t level = 0;
    size_t index = 0;

    assert(NULL != trie);

    runner = trie->root;
    level = trie->num_of_input_bits;
    index = level;

    while(level && NULL != runner)
    {
        parrent = runner;
        --level;
        runner = parrent->children[(data >> level) & 1];
    }

    if (!level && 1 == runner->is_occupied)
    {

        return (1);

    }

    return (0);
}  

/********************* TrieCount ***************************/

size_t TrieCount(const trie_t *trie)
{
    assert(NULL != trie);

    return (trie->size);
}

/********************* comment ***************************/

trie_status_t TrieNextAvailable(const trie_t *trie, size_t *data_ptr)
{
    trie_node_t *runner = NULL;
    trie_node_t *parrent = NULL;
    size_t level = 0;
    size_t index = 0;
    size_t data = 0;

    assert(NULL != trie);
    assert(NULL != data_ptr);

    runner = trie->root;
    level = trie->num_of_input_bits;
    index = level;
    data = *data_ptr;

    while (level && NULL != runner && 1 != runner->is_occupied)
    {
        parrent = runner;
        --level;
        runner = parrent->children[(data >> level) & 1];
    }

    while (NULL != parrent && parrent->children[RIGHT] == runner && 1 == parrent->children[RIGHT]->is_occupied)
    {
        runner = parrent;
        parrent = parrent->parent;
        ++level;
    }

    if (NULL == parrent)
    {
        return (PATH_OCCUPIED);
    }

    parrent = runner;
    --level;
    runner = parrent->children[RIGHT];

    while (NULL != runner && level)
    {
        if (NULL == parrent)
        {
            *data_ptr = data << level;
            return (SUCCESS);
        }
        runner = parrent->children[LEFT];
        if (!runner || 1 != runner->is_occupied)
        {
            parrent = runner;
            data |= 1 << (level - 1);
            --level;
        }
        else if (!parrent->children[RIGHT] || 1 != parrent->children[RIGHT]->is_occupied)
        {
            parrent = parrent->children[RIGHT];
            data = (data << (level - 1)) >> level + (data >> (9 - level)) << level;
            --level;
        }
    }
}

/********************* comment ***************************/

static size_t Reverse(size_t data, size_t num_of_input_bits)
{
return (data);
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

static void SetOccupied(trie_node_t *parent)
{
    trie_node_t *left_child = NULL;
    trie_node_t *right_child = NULL;

    assert(NULL != parent);

    parent->is_occupied = 1;

    parent = parent->parent;

    while (NULL != parent)
    {
        left_child = parent->children[LEFT];

        right_child = parent->children[RIGHT];

        if (NULL != left_child && 1 == left_child->is_occupied && 
        NULL != right_child && 1 == right_child->is_occupied) /* if both children are occupied so is the parrent*/
        {
            parent->is_occupied = 1;
        }
        else
        {
            return ;    /* do nothing and return */
        }

        parent = parent->parent;
    }
}

trie_node_t *CreatePath(trie_node_t *parrent, size_t level, size_t data)
{
    while (NULL != CreateTrieNode(parrent) && level)
    {
        --level;
    }

    return ((level) ? NULL: parrent);    
}


#ifndef NDEBUG

void Print2DInt(trie_node_t *root, int space)
{
    int i = 0;
        
    space += 10;
    if (root == NULL)
    {
        return;
    }
    Print2DInt(root->children[1], space);
    
    printf("\n");
    for(i = 10; i < space; ++i)
         printf(" ");
    printf("d:%d", (root->is_occupied));    
    Print2DInt(root->children[0], space);
}

void PrintTrie(trie_t *trie)
{
    Print2DInt(trie->root, 0);

    printf("\n");
} 

#endif