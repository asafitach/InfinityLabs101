#include <stdlib.h> /* NULL, malloc, free */
#include <assert.h> /* assert */

#include "srtlist.h"

/*********************sorted management struct definition***************************/

struct srtlist
{
	dlist_t *d_list;
	cmp_func_t cmp_func;
};

struct node 
{
	void *data;
	node_t *next;
	node_t *prev;

};

struct dlist
{
	node_t head;
	node_t tail; 
}; 


/*********************sorted list API definition***************************/

/************************SrtListCreate**********************************/

srtlist_t *SrtListCreate(cmp_func_t cmp_func)
{
	srtlist_t *srt_list = NULL;
	
	assert(NULL != cmp_func);
	
	srt_list = malloc(1 * sizeof(srtlist_t));
	if (NULL == srt_list)
	{
		return (NULL);
	}

	srt_list->d_list = DlistCreate();
	if (NULL == srt_list->d_list)
	{
		free(srt_list);
		srt_list = NULL;
		
		return (NULL);
	}
	
	srt_list->cmp_func = cmp_func;
	
	return (srt_list);
}
	
/************************SrtListDestroy**********************************/
	
void SrtListDestroy(srtlist_t *srt_list)
{
	assert(NULL != srt_list);
	
	DlistDestroy(srt_list->d_list);
	
	free(srt_list);
	srt_list = NULL;
	
	return ;
}

/************************SrtListInsert**********************************/

srtlist_iter_t SrtListInsert(srtlist_t *srt_list, void *data)
{
	srtlist_iter_t iter = NULL;
	srtlist_iter_t tail = NULL;
	
	assert(NULL != srt_list);
	
	iter = DlistBegin(srt_list->d_list);
	tail = DlistEnd(srt_list->d_list);
	
	while (iter != tail)
	{
		if (srt_list->cmp_func(DlistGetData(iter), data) == 0)
		{
			return (DlistInsert(iter, data));
		}
		
		iter = iter->next;
	}
	
	return (DlistInsert(tail, data));
}

/***********************SrtListRemove*********************************/

srtlist_iter_t SrtListRemove(srtlist_iter_t iterator)
{
	return (DlistRemove(iterator));
}

/************************SrtListPopFront**********************************/

void *SrtListPopFront(srtlist_t *srt_list)
{
	assert(NULL != srt_list);
	
	return (DlistPopFront(srt_list->d_list));
}

/************************SrtListPopBack**********************************/

void *SrtListPopBack(srtlist_t *srt_list)
{
	assert(NULL != srt_list);
	
	return (DlistPopBack(srt_list->d_list));
}
	
/************************SrtListGetData**********************************/

void *SrtListGetData(const srtlist_iter_t iterator)
{	
	return (DlistGetData(iterator));
}

/************************SrtListSize**********************************/

size_t SrtListSize(const srtlist_t *srt_list)
{
	return (DlistSize(srt_list->d_list));
}

/************************SrtListFind**********************************/

srtlist_iter_t SrtListFind(srtlist_iter_t from, srtlist_iter_t to, const void *to_find) 
{
	
	srtlist_iter_t iter = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	
	iter = from;
	
	while (iter != to)
	{
		if (iter->data == to_find)
		{
			return (iter);
		}
		
		iter = DlistNext(iter);
	}
	
	while (NULL != iter->next)
	{
		iter = DlistNext(iter);
	}
	
	return (iter);
}

/************************SrtListFindIf**********************************/

srtlist_iter_t SrtListFindIf(srtlist_iter_t from, srtlist_iter_t to, is_match_t is_match, void *param)
{
	return (DlistFindOne(from, to, is_match, param));
}

/************************SrtListBegin**********************************/

srtlist_iter_t SrtListBegin(const srtlist_t *srt_list)
{
	assert(NULL != srt_list);

	return (DlistBegin(srt_list->d_list));
}

/************************SrtListEnd***********************************/

srtlist_iter_t SrtListEnd(const srtlist_t *srt_list)
{
	assert(NULL != srt_list);

	return (DlistEnd(srt_list->d_list));
}

/************************SrtListNext**********************************/

srtlist_iter_t SrtListNext(srtlist_iter_t iterator)
{ 
	return (DlistNext(iterator));
}

/************************SrtListPrev**********************************/

srtlist_iter_t SrtListPrev(srtlist_iter_t iterator)
{
	return (DlistPrev(iterator));
}

/************************SrtListIsEmpty**********************************/

int SrtListIsEmpty(const srtlist_t *srt_list)
{
	assert(NULL != srt_list);
	
	return (DlistIsEmpty(srt_list->d_list));
}

/************************SrtListForeach**********************************/

int SrtListForeach(srtlist_iter_t from, srtlist_iter_t to , action_func_t action_func, void *param)
{
	return (DlistForeach(from, to, action_func, param));
}

/************************SrtListMerge**********************************/

void SrtListMerge(srtlist_t *dest, srtlist_t *src)
{
    srtlist_iter_t dest_iter = NULL;
    srtlist_iter_t dest_tail = NULL;
    
    srtlist_iter_t src_iter = NULL;
    srtlist_iter_t src_tail = NULL;
    
    srtlist_iter_t temp_src = NULL;
    
    assert(NULL != dest);
    assert(NULL != src);
    
    dest_iter = DlistBegin(dest->d_list);
    dest_tail = DlistEnd(dest->d_list);
    
    src_iter = DlistBegin(src->d_list);
    src_tail = DlistEnd(src->d_list);
    
    while (dest_iter != dest_tail && src_iter != src_tail)
    {
        if (dest->cmp_func(DlistGetData(dest_iter), DlistGetData(src_iter)) == 0) 
        {
            temp_src = src_iter->next;    
         	
         	DlistSplice(dest_iter, src_iter, temp_src);
            
            src_iter = temp_src;    
        }
        else
        {
            dest_iter = dest_iter->next;
        }    
    }
    
    if (dest_iter == dest_tail)
    {
        DlistSplice(dest_iter, src_iter, src_tail);
    }
    
    return ;

}

/************************END*********************************/

