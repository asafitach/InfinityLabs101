#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



typedef struct array_node
{
    int val;
    int version_num;
}array_node_t;

typedef struct array
{
    array_node_t *array_nodes;
    int *version;
    int last_set_version;
    int size;
}array_t;

array_t *ArrayCreate(int size)
{
    array_t *array = (array_t *)malloc(sizeof(array_t));
    if (NULL == array)
    {
        return (NULL);
    }
    
    array->array_nodes = (array_node_t *)calloc(size, sizeof(array_node_t));
    if (NULL == array->array_nodes)
    {
        free(array);
        return (NULL);
    }

    array->version = (int *)calloc(size * 2, sizeof(int));
    if (NULL == array->version)
    {
        free(array->array_nodes);
        free(array);
        return (NULL);
    }

    array->size = size;
    array->last_set_version = 0;

    return (array);
}

void ArrayDestroy(array_t *array)
{
    assert(NULL != array);

    free(array->array_nodes);
    free(array->version);
    free(array);

    array = NULL;
}

int ArraySetVal(array_t *array, int index, int new_val)
{
    assert(NULL != array);

    if (index + 1 == array->size)
    {
        return (1);
    }

    array->array_nodes[index].val = new_val;
    array->array_nodes[index].version_num = array->last_set_version + 1;
    
    return (0);
}

void ArraySetAll(array_t *array, int val)
{
    assert(NULL != array);

    array->last_set_version += 2;
    array->version[array->last_set_version] = val;
}

int ArrayGetVal(array_t *array, int index)
{
    assert(NULL != array);

    if (array->last_set_version >= array->array_nodes[index].version_num)
    {
        return(array->version[array->last_set_version]);
    }
    if (0 == array->array_nodes[index].version_num % 2)
    {
        return (array->version[array->array_nodes[index].version_num]);
    }

    return (array->array_nodes[index].val);
}

/* 
2. can br done by lut wich contain the corresponde number to complete the sum - only for some range. or can be done by sort the array and tranverse it once - curcurrently from the start and from the end. first is O(n) and the second is O(nlog(n)) (the first isnt so greate)
 */

