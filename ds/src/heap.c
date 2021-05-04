#include <assert.h>
#include <stdlib.h>
#include "heap.h"
#include "d_vector.h"
/*****************************************************************************/
struct heap
{
	d_vector_t *d_vector;
    heap_cmp_t cmp_func;
}; 

#define RIGHT(a) (2 * a) + 2
#define LEFT(a) (2 * a) + 1
#define PARRENT(a) (a - 1) / 2

#define INIT_CAPACITY 15
/*****************************************************************************/

heap_t *HeapCreate(heap_cmp_t heap_cmp)
{
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    if (NULL == heap)
    {
        return (NULL);
    }
    
    assert (NULL != heap_cmp);

    heap->d_vector = VectorCreate(INIT_CAPACITY);
    if (NULL == heap->d_vector)
    {
        free(heap);
        return (NULL);
    }

    heap->cmp_func = heap_cmp;

    return (heap);
}

/*****************************************************************************/

void HeapDestroy(heap_t *heap)
{
    assert(NULL != heap);

    VectorDestroy(heap->d_vector);

    free(heap);
    heap = NULL;
}

/*****************************************************************************/

int HeapPush(heap_t *heap, void *data)
{
    assert(NULL != heap);
   
    if (SUCCESS != VectorPushBack(heap->d_vector, data))
    {
        return (0);
    }

    HeapifyUp(heap);
}

/*****************************************************************************/
/*
Description: The function removes an element from the front of the heap.
@params: The function gets a pointer to the heap.
@return: The function is void.
@errors: 
*/
void HeapPop(heap_t *heap)
{
    size_t index = 0;

    assert(NULL != heap);

    index = VectorGetSize(heap->d_vector) - 1;
    VectorSetElement(heap->d_vector, 0, VectorGetElement(heap->d_vector, index));

    VectorPopBack(heap->d_vector);

    HeapifyDown(heap, 0);
}

/*****************************************************************************/

void *HeapRemove(heap_t *heap, heap_is_match is_match, void * param)
{
    void *data = NULL;
    size_t index = 0;
    size_t size = 0;

    assert(NULL != heap);
    assert(NULL != is_match);
    assert(1 != HeapIsEmpty(heap));

    size = VectorGetSize(heap->d_vector);
    
    while (index < size)
    {
        data = VectorGetElement(heap->d_vector, index);
        if (1 == is_match(data, param))
        {
            break;
        }
        ++index;
    }

    if (index == size)
    {
        return (NULL);
    }

    VectorSetElement(heap->d_vector, index, VectorGetElement(heap->d_vector, size));

    VectorPopBack(heap->d_vector);

    HeapifyDown(heap, index);

    return (data);
}

/*****************************************************************************/

void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);

    return (VectorGetElement(heap->d_vector, 0));
}

/*****************************************************************************/

size_t HeapSize(const heap_t *heap)
{
    assert (NULL != heap);

    return (VectorGetSize(heap->d_vector));
}

/*****************************************************************************/

int HeapIsEmpty(const heap_t *heap)
{
    assert(NULL != heap);

    return (VectorGetSize(heap->d_vector) == 0 ? 1: 0);
}

/*****************************************************************************/

void HeapifyDown(heap_t *heap, size_t index)
{
    d_vector_t *vector = heap->d_vector;
    size_t last_index = VectorGetSize(vector) - 1;
    int *(*cmp)(const void *, const void *) = heap->cmp_func;
    void *data_to_move = VectorGetElement(vector, index);
    void *right = NULL;
    void *left = NULL;

    while (RIGHT(index) <= last_index)
    {
        right = VectorGetElement(vector, RIGHT(index));
        left = VectorGetElement(vector, LEFT(index));
        if (cmp(right, left) > 0)
        {

        }
    }


    void *cmp_data = VectorGetElement(vector, PARRENT(index));

}

void HeapifyUp(heap_t *heap, void *data)
{
    d_vector_t *vector = heap->d_vector;
    size_t index = VectorGetSize(vector) - 1;
    int *(*cmp)(const void *, const void *) = heap->cmp_func;
    void *cmp_data = VectorGetElement(vector, PARRENT(index));
    
    while (index && 1 == cmp(data, cmp_data))
    {
        VectorSetElement(vector, index, cmp_data);
        index = PARRENT(index);
        VectorSetElement(vector, index, data)
        cmp_data = VectorGetElement(vector, PARRENT(index));
    }
}


/*****************************************************************************/
