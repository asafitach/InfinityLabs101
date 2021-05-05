#include <assert.h>   /* assert */
#include <stddef.h>   /* NULL size_t */
#include <stdlib.h>   /* malloc free */

#include "trie.h"

#define CHILD root->children[bit]

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


/********************* Api functions definition ***************************/



trie_t *TrieCreate(size_t num_of_input_bits)
{
    trie_t *trie = (trie_t *)malloc(1 * sizeof(trie_t));
    if (NULL == trie)
    {
        return (NULL);
    }

    trie->root = NULL;
    
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
	}
	
	return ;
}

trie_status_t TrieInsert(trie_t *trie, size_t data)
{
    size_t bit = 0;

    trie_node_t *root = NULL;

    size_t mask = 1;

    size_t i = 0;

    assert(NULL != trie);

    root =  trie->root;

    for(i = 0; i < trie->num_of_input_bits; i++)
    {
        bit = (data >> i) & mask;

        if (NULL == CHILD)
        {
            
        }

        if(NULL != CHILD && 0 == root->is_occupied) /* if exsits and  not occupied */
        {
            root = CHILD;
        }




    }
}


/*trie_status_t TrieRemove(trie_t *trie, size_t data)


int TrieIsFound(const trie_t *trie, size_t data)  */



size_t TrieCount(const trie_t *trie)
{
    assert(NULL != trie);

     return (trie->num_of_nodes);
}


/* trie_status_t TrieNextAvailable(const trie_t *trie, size_t *data) */



trie_status_t TriePathCreate(trie_node_t *root, size_t data, size_t )
