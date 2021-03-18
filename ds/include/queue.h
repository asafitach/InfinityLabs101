#ifndef __QUEUE_H__
#define __QUEUE_H__


typedef struct queue queue_t;




/*Description: The function creates a new queue data structure.
@return: The function returns a pointer to queue_t structure.
@errors: Returns NULL if malloc fails.
*/
queue_t *QueueCreate();

/*Description: The function frees all the elements in the Queue.
@params: The function gets a pointer to the Queue head.
*/
void QueueDestroy(queue_t *queue);


/*Description: The functions inserts a new element at the back of the queue.
@params: The function gets a pointer to the queue and the data to be inserted.
@return: returns 0 if malloc failed.
@errors: malloc fail.
*/
int Enqueue(queue_t *queue, const void *data);


/*Description: The function removes an element from the front of the queue.
@params: The function gets a pointer to the queue.
@return: The function is void.
@errors: 
*/
void Dequeue(queue_t *queue);


/*Description: The function gets a pointer to the queue and returns the data at the 
head of the queue.
@params: The function gets a pointer to the queue. 
@return: The function return the data at the front of the queue.
@errors: 
*/
void *QueuePeek(const queue_t *queue);


/*Description: The function returns the number of items stored in the queue.
@params: The function gets a pointer to the queue.
@return: The function returns the number of items in the queue.
@errors: 
*/
size_t QueueCount(const queue_t *queue);


/*Description: The function checks if queue is empty. 
returns 1 for TRUE, 0 for FALSE.
@params: The function a pointer to the queue.
@return: The function returns an int (BOOLEAN).
@errors:
*/
int QueueIsEmpty(const queue_t *queue);


/*Description: The function appends queue2 to queue1 
@params: The function gets pointers to the front of the queues to connect.
@return: The function returns a pointer to the front of the new queue.
@errors: 
*/
void QueueAppend(queue_t *dest, queue_t *src);


#endif /* __QUEUE_H__ */
