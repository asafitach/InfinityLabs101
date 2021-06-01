#include <stdio.h>   /* printf */
#include "stdlib.h" /* NULL, malloc, free */
#include "assert.h" /* assert */

#include "srtlist.h"
#include "pqueue.h"

/***********************color macros for printf*********************************/

#define RED "\033[1;31m"  /* print in red */

#define GREEN "\033[1;5;32m"	/* print in green */

#define BLUE "\033[1;34m"  /* print in blue */

#define YELLOW "\033[1;4:1;33m" /* print in yellow  */

#define YELLOW2 "\033[1;33m" /* print in yellow  */

#define PURPLE "\033[1;35m" /* print in purple */

#define CYAN "\033[1;3;36m" /* print in cyan */

#define RESET "\033[0m" /* reset print color  */

/*********************Typedef of queue***************************/
					    
struct pq
{
	srtlist_t *srt_list;	
};

/************************PQCreate**********************************/

pq_t *PQCreate(pq_cmp_t pq_cmp)
{	
	pq_t *pqueue = malloc(1 * sizeof(pq_t));
	if (NULL == pqueue)
	{
		return (NULL);
	}
	
	pqueue->srt_list = SrtListCreate(pq_cmp);
	if (NULL == pqueue->srt_list)
	{
		free(pqueue);
		pqueue = NULL;
		return (NULL);
	}
	

	
	return (pqueue);
}
	
/************************PQDestroy**********************************/
	
void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	SrtListDestroy(pq->srt_list);
	
	free(pq);
	pq = NULL;
}

/************************QueueDestroy**********************************/

void PQClear(pq_t *pq)
{
	srtlist_iter_t iter =  NULL;
	srtlist_iter_t tail = NULL;
	
	assert(NULL != pq);
	
	iter =  SrtListBegin(pq->srt_list);
	
	tail = SrtListEnd(pq->srt_list);
	
	while (iter != tail)
	{
		iter = SrtListRemove(iter);
	}
	
	return ;
}

/************************PQEnQueue**********************************/

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	
	return ((SrtListEnd(pq->srt_list) == SrtListInsert(pq->srt_list, data)) ? 1 : 0);
}

/************************PQDeQueue**********************************/

void *PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	
	return (SrtListPopFront(pq->srt_list));	
}
	
/************************PQPeek**********************************/

void *PQPeek(const pq_t *pq)
{	
	assert(NULL != pq);
	
	return (SrtListGetData(SrtListBegin(pq->srt_list)));
}
	
/************************PQCount**********************************/
	
size_t PQCount(const pq_t *pq)
{
	assert(NULL != pq);
	
	return (SrtListSize(pq->srt_list));
}

/************************PQIsEmpty**********************************/

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return (SrtListIsEmpty(pq->srt_list));
}

/************************PQErase**********************************/

void *PQErase(pq_t *pq, pq_match_t pq_match, void *param)
{
	void * data = NULL;
	
	srtlist_iter_t iter = NULL;
	
	srtlist_iter_t from = NULL;
	
	srtlist_iter_t to = NULL;
	
	assert(NULL != pq);
	
	from = SrtListBegin(pq->srt_list);
	
	to = SrtListEnd(pq->srt_list);
	
	iter = SrtListFindIf(from, to, pq_match, param);
	
	if (SrtListEnd(pq->srt_list) == iter)
	{
		return (NULL);
	}

	data = SrtListGetData(iter);
	
	SrtListRemove(iter);
	
	return (data);
}	

#ifndef NDEBUG

/************************PQPrint**********************************/

void PQPrint(pq_t *pq, print_func_t print_func, void *param)
{
	srtlist_iter_t begin = NULL;
	
	srtlist_iter_t end = NULL;
	
	assert(NULL != pq);
	assert(NULL != print_func);
	
	begin = SrtListBegin(pq->srt_list);
	
	end = SrtListEnd(pq->srt_list);
	
	printf(YELLOW2"START "RESET);
	printf("<== ");
	
	SrtListForeach(begin, end, print_func, param);
	
	printf(YELLOW2" END\n\n"RESET);
	
	return ;
}

#endif
	
/************************END*********************************/
