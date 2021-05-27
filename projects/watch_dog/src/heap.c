#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free */
#include <stdio.h> /* printf */
#include "heap.h"
#include "d_vector.h"

/*****************************************************************************/

struct heap
{
	d_vector_t *d_vector;
    heap_cmp_t cmp_func;
}; 

#define RIGHT(a) ((2 * a) + 2)
#define LEFT(a) ((2 * a) + 1)
#define PARRENT(a) (((int)a - 1) / 2)

#define INIT_CAPACITY 10


void HeapifyDown(heap_t *heap, size_t index);

void HeapifyUp(heap_t *heap, void *data);

void VectorSwap(d_vector_t *d_vector, size_t index1, size_t index2);

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
}

/*****************************************************************************/

int HeapPush(heap_t *heap, void *data)
{
    assert(NULL != heap);
   
    if (SUCCESS != VectorPushBack(heap->d_vector, data))
    {
        return (1);
    }
/*     if (1 == HeapSize(heap))
    {
        return(0);
    } the parrent will be tha same and heapify will return it*/

    HeapifyUp(heap, data);

    return (0);
}

/*****************************************************************************/

void HeapPop(heap_t *heap)
{
    size_t index = 0;

    assert(NULL != heap);

    index = VectorGetSize(heap->d_vector) - 1;
    VectorSetElement(heap->d_vector, 0, VectorGetElement(heap->d_vector, index));

    VectorPopBack(heap->d_vector);

/*     if (2 > HeapSize(heap))
    {
        return;
    }  test if there is no need in this "if"*/

    HeapifyDown(heap, 0);
}

/*****************************************************************************/

void *HeapRemove(heap_t *heap, heap_is_match is_match, void * param)
{
    void *data = NULL;
    size_t index = 0;
    size_t size = 0;
    d_vector_t *vector = NULL;

    assert(NULL != heap);
    assert(NULL != is_match);

    vector = heap->d_vector;
    size = VectorGetSize(vector);
    
    while (index < size)
    {
        data = VectorGetElement(vector, index);
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

    VectorSetElement(vector, index, VectorGetElement(vector, size - 1));

    VectorPopBack(vector);

    HeapifyDown(heap, index);

    return (data);
}

/*****************************************************************************/

void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);

    if (1 == HeapIsEmpty(heap))
    {
        return (NULL);
    }

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
    heap_cmp_t cmp = heap->cmp_func;
    void *data_to_move = VectorGetElement(vector, index);
    void *right = NULL;
    void *left = NULL;

    while (RIGHT(index) <= last_index)
    {
        right = VectorGetElement(vector, RIGHT(index));
        left = VectorGetElement(vector, LEFT(index));
        if (0 > cmp(data_to_move, left))
        {
            if (/* 0 > cmp(data_to_move, right) &&  */0 < cmp(right, left))
            {
                VectorSwap(vector, index, RIGHT(index));
                index = RIGHT(index);
            }
            else
            {
                VectorSwap(vector, index, LEFT(index));
                index = LEFT(index);
            }
        }
        else if (0 > cmp(data_to_move, right))
        {
            VectorSwap(vector, index, RIGHT(index));
            index = RIGHT(index);
        }
        else
        {
            return;
        }
    }

    if (LEFT(index) == last_index && 0 > cmp(data_to_move, VectorGetElement(vector, LEFT(index))))
    {
        VectorSwap(vector, index, LEFT(index));
    }
}

void HeapifyUp(heap_t *heap, void *data)
{
    d_vector_t *vector = heap->d_vector;
    size_t index = VectorGetSize(vector) - 1;
    heap_cmp_t cmp = heap->cmp_func;
    void *cmp_data = NULL;
     
    cmp_data = VectorGetElement(vector, PARRENT(index));
    while (0 < cmp(data, cmp_data))
    {
        VectorSwap(vector, index, PARRENT(index));
        index = PARRENT(index);
        if (0 == index)
        {
            return;
        }
        cmp_data = VectorGetElement(vector, PARRENT(index));
    }
}

void VectorSwap(d_vector_t *vector, size_t index1, size_t index2)
{
    void *data1 = VectorGetElement(vector, index1);
    VectorSetElement(vector, index1, VectorGetElement(vector, index2));
    VectorSetElement(vector, index2, data1);
}

void PrintHeap(heap_t *heap)
{
    size_t arr_size = VectorGetSize(heap->d_vector);
    size_t i = 0;
    void *data = NULL;

    for(i = 0; i < arr_size; i++)
    {
        data = VectorGetElement(heap->d_vector, i);
        printf("%d-->", *(int *)&data);
    }
    printf("\n");
}
/* for int* and not int
void PrintHeap(heap_t *heap)
{
    size_t arr_size = VectorGetSize(heap->d_vector);
    size_t i = 0;

    for(i = 0; i < arr_size; i++)
    {
        printf("%d-->", *(int *)VectorGetElement(heap->d_vector, i));
    }
}*/
/*
void HespSort(heap_t *heap, heap_cmp_t cmp)
{
    assert(NULL != heap);
    assert(NULL != cmp);


    return (RecursiveHespSort(heap->d_vector, cmp, 0, LogOf2(HeapSize(heap) / 2), 0));
}

size_t LogOf2(size_t number)
{
    size_t log = 0;

    while(number)
    {
        ++log;
        number /= 2;
    }

    return (log - 1);
}

void RecursiveHeapSort(d_vector_t *vector, heap_cmp_t cmp, size_t cur_index, size_t level, size_t cur_level)
{

    if (NULL == VectorGetElement(cur_index));
    {
        return;
    }

    if (cur_level <= level)
    {
        RecursiveHeapSort(vector, cmp, VectorGetElement(vector, RIGHT(cur_index)), level, cur_level + 1);
        RecursiveHeapSort(vector, cmp, VectorGetElement(vector, LEFT(cur_index)), level, cur_level + 1);
    }

    SortBrench(vector, cur_index, cmp);
}

void SortBrench(d_vector_t *vector, size_t parrent_index, heap_cmp_t cmp)
{
    void *parrent = VectorGetElement(vector, parrent_index);
    void *right = VectorGetElement(vector, RIGHT(parrent_index));
    void *left = VectorGetElement(vector, LEFT(parrent_index));

    if (NULL != right && 0 > cmp(parrent, right))
    {
        if (0 > cmp(left, right) && 0 > cmp(left, parrent))
        {
            VectorSwap(vector, LEFT(parrent_index), parrent_index);
            HeapifyDown()LEFT(parrent_index)
        }
        else
        {
            VectorSwap(vector, RIGHT(parrent_index), parrent_index);
            HeapifyDown()RIGHT(parrent_index)
        }
    }
    else if (NULL != left && 0 > cmp(left, parrent))
    {
        VectorSwap(vector, LEFT(parrent_index), parrent_index);
        HeapifyDown()LEFT(parrent_index)
    }

}*/
/*****************************************************************************/
