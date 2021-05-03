#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include "dllist.h"

#include <stdio.h>


int global_implicit_lib = 5;

/******************************************************************************/

typedef struct node node_t;

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
   
/********************until here***************************/


void MemoryMap(int num)
{
	int const int_const = 3;
	static size_t static_var_imp = 5;
	char *implicit_literal = "i am here";
	int reg = num;
	

	printf("|int---------implicit----->\t\t\t%lu|\n", (size_t)&reg);
	printf("|const int---implicit----->\t\t\t%lu|\n", (size_t)&int_const);
	printf("|static------implicit----->\t\t\t%lu|\n", (size_t)&static_var_imp);
	printf("|literal ----implicit----->\t\t\t%lu|\n", (size_t)implicit_literal);
	printf("----------------------------------------------------------------\n\n");
}

dlist_t *DlistCreate(void)
{
	dlist_t *list = (dlist_t *)malloc(sizeof(dlist_t));
	
	if(NULL == list)
	{
		return (NULL);
	}
	
	list->head.data = (void *)list;
	list->head.prev = NULL;
	list->head.next = &list->tail;
	
	list->tail.data = (void *)list;
	list->tail.next = NULL;
	list->tail.prev = &list->head;
	
	return (list);
}	


void DlistDestroy(dlist_t *list)
{
	void *res = (void *)list;
	assert(NULL != list);
	
	while(NULL != res)
	{
		res = DlistPopBack(list);
	}
	
	free(list);
	list = NULL;
}

/******************************************************************************/

static dlist_iter_t EndDummy(dlist_iter_t iter)	
{
	while(NULL != iter->next)
	{
		iter = iter->next;
	}
	
	return (iter);
}


dlist_t *GetList(dlist_iter_t iter)
{
	dlist_iter_t iterator = EndDummy(iter);
	return ((dlist_t *)(iterator->data));
}
	
/******************************************************************************/

dlist_iter_t DlistInsert(dlist_iter_t iterator, void *data)
{
	dlist_iter_t tmp_iter = (dlist_iter_t)malloc(sizeof(node_t));
	if(NULL == tmp_iter)
	{
		return(EndDummy(iterator));
	}
	
	assert(NULL != iterator);
	assert(NULL != iterator->prev);
	
	
	tmp_iter->data = data;
	tmp_iter->next = iterator;
	tmp_iter->prev = iterator->prev;
	iterator->prev->next = tmp_iter;
	iterator->prev = tmp_iter;
	
	return (tmp_iter);
}

/******************************************************************************/

dlist_iter_t DlistPushFront(dlist_t *dlist, void *data)
{
	return (DlistInsert(DlistBegin(dlist), data));
}

/******************************************************************************/

dlist_iter_t DlistPushBack(dlist_t *dlist, void *data)
{
	assert(NULL != dlist);
	return (DlistInsert(DlistEnd(dlist), data));
}

/******************************************************************************/

dlist_iter_t DlistRemove(dlist_iter_t iterator)
{	
	dlist_iter_t tmp = NULL;	
	
	assert(NULL != iterator->next);
	
	tmp = iterator->next;
	iterator->prev->next = iterator->next;
	iterator->next->prev = iterator->prev;
	
	free(iterator);
	iterator = NULL;
	
	return (tmp);
}

/******************************************************************************/

void *DlistPopFront(dlist_t *dlist)
{
	void *data = dlist->head.next->data;
	if (data == (void *)dlist)
	{
		return(NULL);
	}
	assert(NULL != dlist);
	
	DlistRemove(dlist->head.next);
	return (data);
}
	
	
/******************************************************************************/

void *DlistPopBack(dlist_t *dlist)
{
	void *data = dlist->tail.prev->data;
	if (data == (void *)dlist)
	{
		return(NULL);
	}
	assert(NULL != dlist);
	
	DlistRemove(dlist->tail.prev);
	
	return (data);
}

/******************************************************************************/

void *DlistGetData(const dlist_iter_t iterator)
{
	assert(NULL != iterator);
	return(((dlist_iter_t)iterator)->data);
}

/******************************************************************************/

size_t DlistSize(const dlist_t *list)
{
	size_t count = 0;
	dlist_iter_t runner = list->head.next;
	assert(NULL != list);
	
	while(NULL != runner->next)
	{
		count++;
		runner = runner->next;
	}
	
	return (count);
}
	
/******************************************************************************/

dlist_iter_t DlistFindOne(dlist_iter_t from, dlist_iter_t to, is_equal_func_t is_equal_func, const void *param)
{
	dlist_iter_t index = NULL;
/*	assert(NULL != from->next);*/
	assert(NULL != to);
	assert(NULL != from);

	index = from;
	while (index != to && NULL != index->next)
	{
		if (1 == is_equal_func(index->data, (void *)param))
		{
			return (index);
		}
		
		index = index->next;
	}
	
	return (EndDummy(index));
}

/******************************************************************************/

int DlistFindMulti(dlist_iter_t from, dlist_iter_t to, is_equal_func_t is_equal_func, const void *param, dlist_t *dest)
{
	dlist_iter_t index = NULL;
	assert(NULL != from->next);
	assert(NULL != to);
	assert(NULL != from);
	assert(NULL != is_equal_func);
	index = from;
	while (index != to && NULL != index->next)
	{
		if (1 == is_equal_func(index->data, (void *)param))
		{
			DlistPushBack(dest, (void *)index);
		}
		
		index = index->next;
	}
	
	return (DlistSize(dest));
}

/******************************************************************************/

dlist_iter_t DlistBegin(const dlist_t *list)
{
	assert(NULL != list);
	return (list->head.next);
}

/******************************************************************************/

dlist_iter_t DlistEnd(const dlist_t *list)
{
	assert(NULL != list);
	return ((node_t *)&(list->tail));
}

/******************************************************************************/

dlist_iter_t DlistNext(dlist_iter_t iterator)
{
	assert(NULL != iterator);
	return (iterator->next);
}

/******************************************************************************/

dlist_iter_t DlistPrev(dlist_iter_t iterator)
{
	assert(NULL != iterator->prev->prev);
	return (iterator->prev);
}

/******************************************************************************/

int DlistIsEmpty(const dlist_t *list)
{
	assert(NULL != list);
	return ((list->head.next == &list->tail) ? 1 : 0);
}

/******************************************************************************/

int DlistForeach(dlist_iter_t from, dlist_iter_t to , action_func_t action_func, void *param)
{
	int stat = 1;
	dlist_iter_t index = from;
	assert(NULL != to);
	assert(NULL != from);
	assert(NULL != action_func);
	while(index != to)
	{
		stat = action_func(index->data, param);
		if(1 == stat)
		{
			return (stat);
		}
		index = index->next;
	}
	
	return(stat);
}

/******************************************************************************/

dlist_iter_t DlistSplice(dlist_iter_t dest, dlist_iter_t from, dlist_iter_t to)
{
	dlist_iter_t to_prev = NULL;
	assert(NULL != dest);
	assert(NULL != from);
	assert(NULL != to);

	to_prev = to->prev;
	
	from->prev->next = to;
	to->prev = from->prev;
	
	dest->prev->next = from;
	from->prev = dest->prev;
	
	to_prev->next = dest;
	dest->prev = to_prev;
	
	return (dest);
}
		
/******************************************************************************/

int DlistIsSameIter(dlist_iter_t iterator1, dlist_iter_t iterator2)
{
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	return ((iterator1 == iterator2) ? 1: 0);
}


/********************************E.O.F*****************************************/
