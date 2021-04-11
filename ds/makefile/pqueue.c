#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include "pqueue.h"
#include "srtlist.h"



/******************************************************************************/

struct pq
{
	srtlist_t *srtlist;	
};

/*****************************************************************************/

pq_t *PQCreate(pq_cmp_t pq_cmp)
{
	pq_t *pq = (pq_t*)malloc(sizeof(pq_t));
	if(NULL == pq)
	{
		return (0);
	}
	
	pq->srtlist = SrtListCreate(pq_cmp);
	if(NULL == pq->srtlist)
	{
		free(pq);
		return (0);
		pq = NULL;
	}
	
	return (pq);
}

/*****************************************************************************/

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	SrtListDestroy(pq->srtlist);
	
	free(pq);
	pq = NULL;
}

/*****************************************************************************/

void PQClear(pq_t *pq)
{
	size_t count = 0;
	assert(NULL != pq);
	count = SrtListSize(pq->srtlist);
	while (count != 0)
	{
		SrtListPopFront(pq->srtlist);
		count--;
	}
}

/*****************************************************************************/

int PQEnqueue(pq_t *pq, void *data)
{
	void *ptr = NULL;
	assert(NULL != pq);
	assert(NULL != data);
	
	ptr = (void *)SrtListInsert(pq->srtlist, data);
	
	if(NULL == ptr)
	{
		return (1);
	}
	
	return (0);
}

/*****************************************************************************/

void *PQDequeue(pq_t *pq)
{
	assert(0 != PQCount(pq));
	assert(NULL != pq);
	return (SrtListPopFront(pq->srtlist));
}

/*****************************************************************************/

void *PQPeek(const pq_t *pq)
{
	assert(0 != PQCount(pq)); 
	assert(NULL != pq);
	return (SrtListGetData(SrtListBegin(pq->srtlist)));
}

/*****************************************************************************/

size_t PQCount(const pq_t *pq)
{
	assert(NULL != pq);
	return (SrtListSize(pq->srtlist));
}

/*****************************************************************************/

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	return (SrtListIsEmpty(pq->srtlist));
}

/*****************************************************************************/


void *PQErase(pq_t *pq, pq_match_t pq_match, void *param)
{
	srtlist_iter_t ptr = NULL;
	void *data = NULL;
	
	assert(NULL != pq);
	assert(NULL != param);
	assert(NULL != pq_match);
	
	ptr = SrtListFindIf(SrtListBegin(pq->srtlist), 		  		SrtListEnd(pq->srtlist), pq_match, param); 
	
	if (ptr == (SrtListEnd(pq->srtlist)))
	{
		return (NULL);
	}	
	
	data = SrtListGetData(ptr);
	SrtListRemove(ptr);

	return (data);
}

/*****************************************************************************/

void PQPrint(pq_t *pq, print_func_t print_func, void *param)
{
	assert(NULL != pq);
	SrtListForeach(SrtListBegin(pq->srtlist), 
	SrtListEnd(pq->srtlist), print_func, param);	
}



/********************************E.O.F*****************************************/
