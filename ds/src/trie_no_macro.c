#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */

#include "trie.h"

typedef enum children
{
    LEFT = 0,
    RIGHT ,
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
	trie_node_t *children[NUM_OF_CHILDREN];
};

/****************************TrieCreate****************************************/
static trie_node_t *CreateNode(); 

trie_t *TrieCreate(size_t num_of_input_bits)
{
    trie_t *trie = NULL; 

    trie = (trie_t *)malloc(sizeof(trie_t)); 
    if (NULL == trie)
    {
        return (NULL);
    } 

    trie->num_of_input_bits = num_of_input_bits;  
    
    trie->root = CreateNode();
    if (NULL == trie->root)
    {
        free(trie);
        return (NULL);
    }  
    
    trie->size = 0; 

    return (trie); 
}

static trie_node_t *CreateNode()
{
    trie_node_t *new_node = (trie_node_t*)malloc(sizeof(trie_node_t));
    if (NULL == new_node)
    {
        return (NULL);
    }
 
    new_node->children[0] = NULL;
    new_node->children[1] = NULL;
    new_node->is_occupied = 0;

    return (new_node);    
}

/****************************TrieDestroy***************************************/

static void RecTrieDestroy(trie_node_t *root);

void TrieDestroy(trie_t *trie)
{
    assert(NULL != trie);

    RecTrieDestroy(trie->root);
    
    free(trie); 
}

static void RecTrieDestroy(trie_node_t *node)
{
    if (NULL == node)
    {
        return;
    }

    RecTrieDestroy(node->children[LEFT]);
    RecTrieDestroy(node->children[RIGHT]);

    free(node);    
}

/****************************TrieInsert****************************************/

static void UpdateOccupied(trie_node_t *parent);
static children_t GetDirection(size_t data, size_t index);
static trie_status_t TrieRecInsert(trie_node_t *runner, size_t data, size_t i);

trie_status_t TrieInsert(trie_t *trie, size_t data)
{
    trie_status_t status = SUCCESS;

    assert(NULL != trie);

    status = TrieRecInsert(trie->root, data, trie->num_of_input_bits);

    if (SUCCESS == status)
    {
        ++trie->size;
    }

    return (status);
}

static trie_status_t TrieRecInsert(trie_node_t *runner, size_t data, size_t i)
{
    trie_status_t status = SUCCESS;
    children_t direction = GetDirection(data, i - 1);

    if (1 == runner->is_occupied)
    {
        return (PATH_OCCUPIED);
    }  

    if (0 == i)
    {     
        runner->is_occupied = 1;
        
        return (SUCCESS);
    }

    if (NULL == runner->children[direction])
    {
        runner->children[direction] = CreateNode();
        if (NULL == runner->children[direction])
        {
            return (MALLOC_FAIL);
        }
    }

    status = TrieRecInsert(runner->children[direction], data, i - 1);

    UpdateOccupied(runner);

    return (status);
}

static void UpdateOccupied(trie_node_t *parent)
{
    trie_node_t *left_child = parent->children[LEFT]; 
    trie_node_t *right_child = parent->children[RIGHT];

    if ((left_child != NULL) && (right_child != NULL))
    {
        if ((left_child->is_occupied == 1) && (right_child->is_occupied == 1))
        {
            parent->is_occupied = 1; 
        }
    }
}

static children_t GetDirection(size_t data, size_t index)
{
    data >>= index;

    return (data & (size_t)1);
}


/****************************TrieIsFound***************************************/

static int TrieIsFoundRec(const trie_node_t *runner, size_t data, size_t i);

int TrieIsFound(const trie_t *trie, size_t data)
{
    assert(NULL != trie);

    return (TrieIsFoundRec(trie->root, data, trie->num_of_input_bits - 1));
}

static int TrieIsFoundRec(const trie_node_t *runner, size_t data, size_t i)
{
    children_t direction = GetDirection(data, i);

    if (NULL == runner->children[direction])
    {
        return (0);
    }
    if (i == 0)
    {
        return (1);
    }

    return (TrieIsFoundRec(runner->children[direction], data, i - 1));
}

/****************************TrieCount*****************************************/

size_t TrieCount(const trie_t *trie)
{
    assert(NULL != trie);

    return (trie->size); 
}

/****************************TrieRemove****************************************/


static trie_status_t TrieRemoveRec(trie_node_t *runner, size_t data, size_t i);

trie_status_t TrieRemove(trie_t *trie, size_t data)
{
    assert(NULL != trie);

    if (PATH_INVALID == TrieRemoveRec(trie->root, data, trie->num_of_input_bits - 1))
    {
        return(PATH_INVALID);
    }

    --(trie->size);

    return (SUCCESS);
}

static trie_status_t TrieRemoveRec(trie_node_t *runner, size_t data, size_t i)
{
    trie_status_t status = SUCCESS;
    children_t direction = GetDirection(data, i);
    trie_node_t *child = runner->children[direction];

    if (NULL == child)
    {
        return (PATH_INVALID);
    }

    if (i == 0)
    {
        free(child);
        runner->children[direction] = NULL;
        runner->is_occupied = 0; 
        
        return (SUCCESS);
    }

    status = TrieRemoveRec(child, data, i - 1);
    runner->is_occupied = 0; 

    if ((child->children[direction] == NULL) && (child->children[!direction] == NULL))
    {
        free(child);
        runner->children[direction] = NULL;
    }

    return (status);
}

/****************************TrieNextAvailable**********************************/

static void TrieNextAvailableRec(const trie_node_t *runner, size_t *data, size_t i, int *is_found);
static void GetMinimumAvailable(trie_node_t *node, size_t i, size_t *data);
static void ChangeData(size_t *data, size_t bit_index);

trie_status_t TrieNextAvailable(const trie_t *trie, size_t *data)
{
    int is_found = 0;

    assert(NULL != trie);
    assert(NULL != data);

    if (1 == trie->root->is_occupied)
    {
        return (TRIE_FULL);
    }

    TrieNextAvailableRec(trie->root, data, trie->num_of_input_bits, &is_found);

    if (0 == is_found)
    {
        *data = 0;
        GetMinimumAvailable(trie->root, trie->num_of_input_bits, data);
    }
 
   return (SUCCESS);
}

static void TrieNextAvailableRec(const trie_node_t *runner, size_t *data, size_t i, int *is_found)
{
    children_t direction = GetDirection(*data, i - 1);
    trie_node_t *right_child = NULL;

    if (runner->is_occupied == 1)
    {
        ChangeData(data, i);

        return;
    }

    TrieNextAvailableRec(runner->children[direction], data, i - 1, is_found);

    if (*is_found == 0)
    {
        right_child = runner->children[RIGHT];

        if ((direction == RIGHT) || 
        ((right_child != NULL) && (1 == right_child->is_occupied)))
        {
            ChangeData(data, i);
        }
        else
        {
            GetMinimumAvailable(right_child, i - 1, data);
            *is_found = 1;
        }   
    }
}

static void GetMinimumAvailable(trie_node_t *node, size_t i, size_t *data)
{
    children_t direction = 0;
    trie_node_t *next_node = NULL;

    if (node == NULL)
    {
        return;
    }

    direction = GetDirection(*data, i - 1);
    next_node = node->children[direction];

    if ((next_node != NULL) && (next_node->is_occupied == 1))
    {
        ChangeData(data, i - 1);
        next_node = node->children[!direction];           
    }        

    GetMinimumAvailable(next_node, i - 1, data);
}

static void ChangeData(size_t *data, size_t bit_index)
{
    *data |= ((size_t)1 << bit_index);
    *data &= ((size_t)~0 << bit_index);
}

/****************************PrintTrie*****************************************/

void RecPrintTrie(trie_node_t *root, int space);

void PrintTrie(trie_t *trie)
{
    RecPrintTrie(trie->root, 0);
}

void RecPrintTrie(trie_node_t *root, int space)
{
    int i = 0;

    if (root == NULL)
        return;
        
    space += 10;
    
    RecPrintTrie(root->children[RIGHT], space);
    
    printf("\n");
    for(i = 10; i < space; ++i)
        printf(" ");
    printf("%d\n", (root->is_occupied));
    
    RecPrintTrie(root->children[LEFT], space);
}

