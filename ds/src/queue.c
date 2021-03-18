#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "s_l_list.h"


struct queue
{
	slist_t *list;
}; 



queue_t *QueueCreate()
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t *));
	if(NULL == queue)
	{
		return (queue);
	}
	
	queue->list = SlistCreate();
	if (NULL == queue->list)
	{
		free(queue);
		return (NULL);
	}
	
	return(queue);
}


void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SlistDestroy(queue->list);
	queue->list = NULL;	
	free(queue);
	queue = NULL;
}



int Enqueue(queue_t *queue, const void *data)
{
		void *check = NULL;
		assert(NULL != queue);
		check = (void *)SlistInsert(SlistEnd(queue->list), data);
		
		if ((void *)SlistEnd(queue->list) == check)
		{
		    return (0);
		}
		
		return (1);
}



void Dequeue(queue_t *queue)
{
	assert(NULL != queue);
	SlistRemove(SlistBegin(queue->list));
}


void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
	return (SlistGetData(SlistBegin(queue->list)));
}


size_t QueueCount(const queue_t *queue)
{
	assert(NULL != queue);
	return (SlistCount(queue->list));
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	return (SlistIsEmpty(queue->list));
}

void QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	SlistAppend(dest->list, src->list);
	
	free(src);
}



