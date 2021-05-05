#include <stdlib.h>
#include <assert.h>
#include "pq_heap.h"
#include "heap.h"



struct pq
{
    heap_t *heap;
};


/*****************************************************************************/

pq_t *PQCreate(pq_cmp_t pq_cmp)
{
    pq_t *pq = (pq_t *)malloc(sizeof(pq_t));
    if (NULL == pq)
    {
        return (NULL);
    }

    assert(NULL != pq_cmp);

    pq->heap = HeapCreate((heap_cmp_t)pq_cmp);
    if (NULL == pq->heap)
    {
        free(pq);
        return (NULL);
    }

    return (pq);
}

/*****************************************************************************/

void PQDestroy(pq_t *pq)
{
    assert(NULL != pq);

    HeapDestroy(pq->heap);

    free(pq);
}

/*****************************************************************************/

void PQClear(pq_t *pq)
{
    size_t size = 0;
    heap_t *heap = NULL;

    assert(NULL != pq);

    heap = pq->heap;
    size = HeapSize(pq->heap);

    while (size)
    {
        HeapPop(heap);
        --size;
    }
}

/*****************************************************************************/

int PQEnqueue(pq_t *pq, void *data)
{
    assert(NULL != pq);

     return (HeapPush(pq->heap, data));
}

/*****************************************************************************/

void *PQDequeue(pq_t *pq)
{
    void *data = NULL;
    heap_t *heap;
    
    assert(NULL != pq);

    heap = pq->heap;
    data = HeapPeek(heap);
    HeapPop(heap);

    return (data);
}

/*****************************************************************************/

void *PQPeek(const pq_t *pq)
{
    heap_t *heap = NULL;

    assert(NULL != pq);
    
    heap = pq->heap;
    if (1 == HeapIsEmpty(heap))
    {
        return (NULL);
    }

    return (HeapPeek(heap));
}

/*****************************************************************************/

size_t PQCount(const pq_t *pq)
{
    assert(NULL != pq);

    return (HeapSize(pq->heap));
}

/*****************************************************************************/

int PQIsEmpty(const pq_t *pq)
{
    assert(NULL != pq);

    return (HeapIsEmpty(pq->heap));
}

/*****************************************************************************/

void *PQErase(pq_t *pq, pq_match_t pq_match, void *param)
{
    assert(NULL != pq);

    return (HeapRemove(pq->heap, (heap_is_match)pq_match, param));
}

/*****************************************************************************/
