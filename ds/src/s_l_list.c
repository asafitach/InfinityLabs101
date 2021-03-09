#include <stdio.h>/* printf */
#include <stdlib.h>/* malloc free */
#include <assert.h>/* assert */
#include "s_l_list.h"

struct node 
{
	void *data;
	node_t *next;
};

struct list
{
	node_t *head;
	node_t *tail; 
}; 

slist_t *SlistCreate(void)
{
	slist_t *list = malloc(sizeof(slist_t));
	slist_iter_t dummy = NULL;
	if(NULL == list)
	{
		return (NULL);
	}	
	dummy = malloc(sizeof(node_t));
	if(NULL == dummy)
	{
		free(list);
		return (NULL);
	}
	
	dummy->next = NULL;
	dummy->data = (void *)list;

	list->head = dummy;
	list->tail = dummy;
	
	return (list);
}



void SlistDestroy(slist_t *list)
{
	slist_iter_t present = NULL;
	slist_iter_t in_line = NULL;
	assert(NULL != list);
	
	present = list->head;
	
	while(NULL != present->next)
	{
		in_line = present->next;
		free(present);
		present = in_line;
	}
	
	free(present);
	present = NULL;
	
	free(list);
	list = NULL;
}


slist_iter_t DummyPtr(slist_iter_t iter)
{
	while(NULL != iter->next)
	{
		iter = iter->next;
	}
	
	return(iter);
}


slist_iter_t SlistInsert(slist_iter_t iterator, const void *data)
{
	slist_t *ptr = NULL;
	slist_iter_t dup = (slist_iter_t)malloc(sizeof(node_t));
	if(NULL == dup)
	{
		return(DummyPtr(iterator));
	}
	assert(NULL != iterator);
	
	dup->data = iterator->data;
	dup->next = iterator->next;
	
	iterator->data = (void *)data;
	iterator->next = dup;
	
	if(NULL == dup->next)
	{
		ptr = (slist_t *)dup->data;
		ptr->tail = dup;
	}
	
	return (iterator);
}


slist_iter_t SlistRemove(slist_iter_t iterator)
{
	slist_t *ptr = NULL;
	slist_iter_t tmp = NULL; 

	assert(NULL != iterator);	
	assert(NULL != iterator->next);

	tmp = iterator->next;
	
	iterator->data = tmp->data;
	iterator->next = tmp->next;
	
	free(tmp);
	tmp = NULL;
	
	if(NULL == iterator->next)
	{
		ptr = (slist_t *)iterator->data;
		ptr->tail = iterator;
	}
	
	return(iterator);
}	


void *SlistGetData(const slist_iter_t iterator)
{
	assert(NULL != iterator->next);
	return (iterator->data);
}

void SlistSetData(const slist_iter_t iterator, const void *data)
{
	assert(NULL != iterator->next);
	iterator->data = (void *)data;
} 

int Count(void *data, void *param)
{
    size_t *tmp = (size_t *)param;
    data = data;
	++(*tmp);
    return (0);
}

size_t SlistCount(const slist_t *list)
{
	size_t size = 0;
	assert(NULL != list);
	
	SlistForeach(list->head, list->tail, Count, (void *)&size);
	
	return(size);
} 

slist_iter_t SlistFind(const slist_iter_t from, const slist_iter_t to, cmp_func_t cmp_func, void *param)
{
	slist_iter_t index = NULL;
	assert(NULL != from->next);
	assert(NULL != to);
	assert(NULL != from);

	index = from;
	while (index != to)
	{
		if (0 == cmp_func(index->data, param))
		{
			return (index);
		}
		
		index = index->next;
	}
	
	return (DummyPtr(index));
}



slist_iter_t SlistBegin(const slist_t *list)
{
	assert(NULL != list);
	return (list->head);
}
	


slist_iter_t SlistEnd(const slist_t *list)
{
	assert(NULL != list);
	return(list->tail);
}


slist_iter_t SlistNext(const slist_iter_t iterator)
{
	assert(NULL != iterator);
	return(iterator->next);
}



int SlistIsEmpty(slist_t *list)
{
	assert(NULL != list);
	return ((list->head == list->tail) ? 1 : 0);
}



status_t SlistForeach(slist_iter_t from, slist_iter_t to , action_func_t action_func, void *param)
{
	status_t stat = SUCCESS;
	slist_iter_t index = from;
	assert(NULL != to);
	assert(NULL != from);
	
	while(index != to)
	{
		stat = action_func(&(index->data), param);
		if(FAIL == stat)
		{
			return (stat);
		}
		index = index->next;
	}
	
	return(stat);
}	




