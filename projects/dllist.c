#include <stdlib.h> /* NULL, malloc, free */
#include <assert.h> /* assert */

#include "dllist.h"

/*********************management struct definition***************************/
	    
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

/*********************Doubly linked list API definition***************************/

/************************DlistCreate**********************************/

dlist_t *DlistCreate(void)
{
	dlist_t *list = list = malloc(1 * sizeof(dlist_t));
	if (NULL == list)
	{
		return (list);
	}

	list->head.data = (void *)list;
	list->head.next = &list->tail;
	list->head.prev = NULL;
	
	list->tail.data = (void *)list;
	list->tail.next = NULL;
	list->tail.prev = &list->head;
	
	return (list);
}
	
/************************DlistDestroy**********************************/
	
void DlistDestroy(dlist_t *list)
{
	node_t *current_node = NULL;
	node_t *tmp_node = NULL;
	
	assert(NULL != list);

	current_node = list->head.next;

	while (current_node != &list->tail)
	{
		tmp_node = current_node;
		current_node = current_node->next;
		free(tmp_node);
	}
	
	free(list);
	list = NULL;
	
	return ;
}

/************************DlistInsert**********************************/

dlist_iter_t DlistInsert(dlist_iter_t iterator, void *data)
{
	node_t *new_node = NULL;
	
	assert(NULL != iterator);

	new_node = malloc(1 * sizeof(node_t));
	if (NULL == new_node)
	{
		while (NULL != iterator->next)
		{
			iterator = iterator->next;
		}
		
		return (iterator);
	}
	
	new_node->data = data;
	new_node->next = iterator;
	new_node->prev = iterator->prev;
	
	iterator->prev->next = new_node;
	iterator->prev = new_node;
	
	return (new_node);
}

/************************DlistPushFront**********************************/

dlist_iter_t DlistPushFront(dlist_t *dlist, void *data)
{
	assert(NULL != dlist);
	
	return (DlistInsert(dlist->head.next, data));
}

/************************DlistPushBack**********************************/

dlist_iter_t DlistPushBack(dlist_t *dlist, void *data)
{
	assert(NULL != dlist);
	
	return (DlistInsert(&dlist->tail, data));
}

/***********************DlistRemove*********************************/

dlist_iter_t DlistRemove(dlist_iter_t iterator)
{
	node_t *temp = NULL;
	
	assert(NULL != iterator);
/*	assert(NULL != iterator->next);*/

	if (NULL == iterator->next)
	{
		return (iterator);
	}
	
	iterator->prev->next = iterator->next;
	iterator->next->prev = iterator->prev;
	temp = iterator->next;
	
	free(iterator);
	iterator = NULL;
	
	return (temp);
}

/************************DlistPopFront**********************************/

void *DlistPopFront(dlist_t *dlist)
{
	void *data = NULL;
	dlist_iter_t list_begin = DlistBegin(dlist);
	
	assert(NULL != dlist);
	assert(0 == DlistIsEmpty(dlist));
	
	data = DlistGetData(list_begin);
	DlistRemove(list_begin);
	
	return (data);
}

/************************DlistPopBack**********************************/

void *DlistPopBack(dlist_t *dlist)
{
	void *data = NULL;
	dlist_iter_t list_end = NULL;;	
	
	assert(NULL != dlist);

	list_end = DlistEnd(dlist);
	
	assert(NULL != dlist);
	assert(!DlistIsEmpty(dlist));
	
	data = DlistGetData(list_end->prev);
	DlistRemove(list_end->prev);
	
	return (data);
}
	
/************************DlistGetData**********************************/

void *DlistGetData(const dlist_iter_t iterator)
{	
	assert(NULL != iterator);
	
	if (NULL == iterator->next)
	{
		return (NULL);
	}
	
	return (iterator->data);
}

/************************DlistSize**********************************/

size_t DlistSize(const dlist_t *list)
{
	size_t count = 0;
	node_t *current_node =  NULL;
	
	assert(NULL != list);
	
	current_node = list->head.next;
	
	while (current_node != &list->tail)
	{
		current_node = current_node->next;
		count++;
	}
		
	return (count);
}

/************************DlistFindOne**********************************/

dlist_iter_t DlistFindOne(dlist_iter_t from, dlist_iter_t to, is_equal_func_t is_equal_func, const void *param)
{
	
	dlist_iter_t iter = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_equal_func);
	
	
	iter = from;
	
	while (iter != to)
	{
		if (1 == is_equal_func(iter->data, (void *)param))
		{
			return iter;
		}
		
		iter = DlistNext(iter);
	}
	
	while (NULL != iter->next)
	{
		iter = DlistNext(iter);
	}
	
	return (iter);
}

/************************DlistFindMulti**********************************/

size_t DlistFindMulti(dlist_iter_t from, dlist_iter_t to, is_equal_func_t is_equal_func, const void *param, dlist_t *dest)
{
	dlist_iter_t iter = NULL;
	size_t count = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != dest);
	
	iter = from;
	
	while (iter != to)
	{
		if (1 == is_equal_func(iter->data, (void *)param))
		{
			DlistPushFront(dest, iter);
			count++;
		}
		
		iter = DlistNext(iter);
	}
	
	return (count);
}

/************************DlistBegin**********************************/

dlist_iter_t DlistBegin(const dlist_t *list)
{
	assert(NULL != list);

	return (list->head.next);
}

/************************DlistEnd***********************************/

dlist_iter_t DlistEnd(const dlist_t *list)
{
	dlist_t *temp_list = NULL;
	
	assert(NULL != list);
	
	temp_list = (dlist_t *)list;
	
	return (&temp_list->tail);
}

/************************DlistNext**********************************/

dlist_iter_t DlistNext(dlist_iter_t iterator)
{
	assert(NULL != iterator);
	 
	return (NULL == iterator->next ? iterator : iterator->next);
}

/************************DlistPrev**********************************/

dlist_iter_t DlistPrev(dlist_iter_t iterator)
{
	assert(NULL != iterator);
	
	return (NULL == iterator->prev->prev ? iterator : iterator->prev);
}

/************************DlistIsEmpty**********************************/

int DlistIsEmpty(const dlist_t *list)
{
	assert(NULL != list);
	
	return ((list->head.next == &list->tail) ? 1 : 0);
}

/************************DlistForeach**********************************/

int DlistForeach(dlist_iter_t from, dlist_iter_t to , action_func_t action_func, void *param)
{
	node_t *iter = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	
	iter = from;
	
	while (iter != to)
	{
		if (0 != action_func(iter->data, param))
		{
			return (1);
		}
		
		iter = DlistNext(iter);
	}
	
	return (0);
}

/************************DlistSplice**********************************/

dlist_iter_t DlistSplice(dlist_iter_t dest, dlist_iter_t from, dlist_iter_t to)
{		
	dlist_iter_t temp_dest_prev = NULL;
	
	assert(NULL != dest);
	assert(NULL != from);
	assert(NULL != from->next);
	assert(NULL != to);	
	
	temp_dest_prev = dest->prev;
	
	dest->prev = to->prev;
	to->prev->next = dest;
	to->prev = from->prev;
	from->prev = temp_dest_prev;
	from->prev->next = from;
	to->prev->next = to;
	
	return (dest);
}

/************************DlistIsSameIter**********************************/

int DlistIsSameIter(dlist_iter_t iterator1, dlist_iter_t iterator2)
{
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	
	return (iterator1 == iterator2 ? 1 : 0);
}

/************************END*********************************/

