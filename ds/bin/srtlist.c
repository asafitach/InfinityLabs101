#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */

#include "srtlist.h"
#include "dllist.h"

/********  C FILE  *******/

struct srtlist
{
	dlist_t *list;
	cmp_func_t cmp_func;
};

/*************************/

/******************************************************************************/
srtlist_t *SrtListCreate(cmp_func_t cmp_func)
{
	srtlist_t *slist = (srtlist_t *)malloc(sizeof(srtlist_t));
	if(NULL == slist)
	{
		return (NULL);
	}
	assert(NULL != cmp_func);
	
	slist->cmp_func = cmp_func;
	slist->list = DlistCreate();
	if(NULL == slist->list)
	{
		free(slist);
		return (NULL);
	}
	
	return (slist);
}

/******************************************************************************/

void SrtListDestroy(srtlist_t *slist)
{
	assert(NULL != slist);
	DlistDestroy(slist->list);
	
	free(slist);
}

/******************************************************************************/

srtlist_iter_t SrtListNext(srtlist_iter_t iterator)
{
	return (DlistNext((dlist_iter_t)iterator));
}

/******************************************************************************/

srtlist_iter_t SrtListPrev(srtlist_iter_t iterator)
{
	return (DlistPrev((dlist_iter_t)iterator));
}

/******************************************************************************/

void *SrtListGetData(const srtlist_iter_t iterator)
{
	return (DlistGetData((dlist_iter_t)iterator));
}

/******************************************************************************/

srtlist_iter_t SrtListInsert(srtlist_t *slist, void *data)
{
    dlist_iter_t iter = NULL;
    
    assert(NULL != slist);
    assert(NULL != data);

    iter = DlistBegin(slist->list);
    
    while (iter != DlistEnd(slist->list) && 
    slist->cmp_func(data, DlistGetData(iter)) >= 0)
    {
        iter = (DlistNext(iter));
    }
    
    iter = DlistInsert(iter, data);

    return (iter);
}

/******************************************************************************/

srtlist_iter_t SrtListRemove(srtlist_iter_t iterator)
{
	return (DlistRemove((dlist_iter_t)iterator));
}

/******************************************************************************/

void *SrtListPopFront(srtlist_t *slist)
{
	return (DlistPopFront(slist->list));
}

/******************************************************************************/

void *SrtListPopBack(srtlist_t *slist)
{
	return (DlistPopBack(slist->list));
}

/******************************************************************************/

size_t SrtListSize(const srtlist_t *slist)
{
	return (DlistSize(slist->list));
}

/******************************************************************************/

int SrtListIsEmpty(const srtlist_t *slist)
{
	return (DlistIsEmpty(slist->list));
}

/******************************************************************************/

srtlist_iter_t SrtListBegin(const srtlist_t *slist)
{
	return (DlistBegin(slist->list));
}

/******************************************************************************/

srtlist_iter_t SrtListEnd(const srtlist_t *slist)
{
	return (DlistEnd(slist->list));
}

/******************************************************************************/

int SrtListForeach(srtlist_iter_t from, srtlist_iter_t to , action_func_t actaion_func, void *param)
{
	return (DlistForeach(from, to, actaion_func, param));
}

/******************************************************************************/
srtlist_iter_t Dummy (srtlist_iter_t iter)
{
	while (NULL != DlistNext(iter))
	{
		iter = DlistNext(iter);
	}
	
	return(iter);
}

srtlist_iter_t SrtListFind(srtlist_iter_t from, srtlist_iter_t to, const void *to_find)
{
	assert(Dummy(from) == Dummy(to));
	assert(NULL != to_find);

	while (from != to)
	{
		if(DlistGetData(from) == to_find)
		{
			return(from);
		}
		
		from = DlistNext(from);
	}
	
	return (Dummy(from));		
}

/******************************************************************************/

srtlist_iter_t SrtListFindIf(srtlist_iter_t from, srtlist_iter_t to, is_match_t is_match, void *param)
{
	assert(Dummy(from) == Dummy(to));
	assert(NULL != param);

	while (from != to)
	{
		if(is_match(DlistGetData(from), param))
		{
			return(from);
		}
		
		from = DlistNext(from);
	}
	
	return (Dummy(from));	
}

/******************************************************************************/

void SrtListMerge(srtlist_t *dest, srtlist_t *src)
{
	cmp_func_t func = src->cmp_func;
	srtlist_iter_t to = NULL;
	srtlist_iter_t des = SrtListBegin(dest);
	
	while (SrtListBegin(src) != SrtListEnd(src))
	{
		if (des == SrtListEnd(dest))
		{
			DlistSplice(des, SrtListBegin(src), SrtListEnd(src));
			return;
		}
		
		to = SrtListBegin(src);
		
		while (NULL != SrtListNext(des) && func(SrtListGetData(to), SrtListGetData(des)) > 0)
		{
			des = SrtListNext(des);
		}
		while (NULL != SrtListNext(to) && func(SrtListGetData(to), SrtListGetData(des)) > 0)
		{
			to = SrtListNext(to);
		}
		
		if (SrtListEnd(src) != to)
		{
			to = SrtListNext(to);
		}
		
		DlistSplice(des, SrtListBegin(src), to);
		
	}
}

