#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/

#include "queue.h"

#define LEN 7

#define RED "\033[1;5;31m"
#define GREEN "\033[1;6;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void TestQueue(); 

int main()
{
    system("clear");
    
    TestQueue(); 
    
    return 0; 
}

void TestQueue()
{
    int stat = 0;
    size_t index = 0;
    size_t count = 0;
    queue_t *q1 = NULL;
    queue_t *q2 = NULL;
    
    printf(CYAN"\tTest StackCreate\n\n"WHITE); 
    
    q1 = QueueCreate();
    q2 = QueueCreate();
    
    TEST("create queue", (NULL != q1) , 1); 
    
    TEST("is empty", QueueIsEmpty(q1) , 1); 
    
	for(index = 0; index < LEN; index++)
	{
		stat = Enqueue(q1, (const void *)(index * index));
	}
    
   	for(index = 0; index < LEN; index++)
	{
		stat = Enqueue(q2, (const void *)(index + index));
	}
   
    TEST("enqueue", stat , 1); 
   
    count = QueueCount(q2);
    Dequeue(q2);

    TEST("dequeue and count", QueueCount(q2) , count - 1);   
    
    TEST("queuepeek", QueuePeek(q1) , (void*)0); 

    TEST("is empty", QueueIsEmpty(q1) , 0); 

    QueueAppend(q1, q2);
    
    TEST("append queues", QueueCount(q1) , 2 * LEN - 1); 
    
    QueueDestroy(q1);
    
    printf(CYAN"\tEnd Test StackCreate\n\n"WHITE); 
}
