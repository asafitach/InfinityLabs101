#include <stdio.h> /* printf */
#include <stdlib.h> /* system */

#include "pqueue.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"
#define MAG   "\x1B[35m"

/*****************************************************************************/

#define TEST(name, actual, expected)\
    				printf("%s: %s\n\n", name, actual == expected ?\
     				GREEN"Pass"WHITE : RED"Fail"WHITE)
    
/*****************************************************************************/

typedef struct data
{
	char *name;
	int priority;
}data_t;

int CmpDataFunc(void *val1, void *val2);
int PrintDataFunc(void *data, void* param);
int CmpPriorityMatch(void *val1, void *val2);

pq_t * TestCreate();
void Test(pq_t *queue);

data_t name1 = {"Eden", 1};
data_t name2 = {"Carmel", 2};
data_t name3 = {"Naor", 7};
data_t name4 = {"Noam", 6};
data_t name5 = {"Liran", 3};

data_t name6 = {"Fei", 3};

int main()
{
	pq_t *queue = NULL;
    system("clear");
    
    queue = TestCreate();
    if(NULL == queue)
    {
    	return 1;
    }
    
    Test(queue);
    
    return 0; 
}

pq_t * TestCreate()
{
	pq_t *queue = NULL;
	
    printf(CYAN"Test\n\n"WHITE); 
    queue = PQCreate(CmpDataFunc);
    if(NULL == queue)
    {
    	return NULL;
    }
    TEST("PQCreate(CmpDataFunc)", (queue != NULL), 1);
    
    return queue;
}

void Test(pq_t *queue)
{   
	size_t size = 0;
	void *data = NULL;
	
    TEST("PQueueIsEmpty(queue)", PQIsEmpty(queue), 1);
     
    PQEnqueue(queue, &name1);
	PQEnqueue(queue, &name2);
	PQEnqueue(queue, &name3);
	PQEnqueue(queue, &name4);
	PQEnqueue(queue, &name5);
    
	printf("PQEnqueue(queue, {Eden, 1})\n");
	printf("PQEnqueue(queue, {Carmel, 2})\n");
	printf("PQEnqueue(queue, {Naor, 7})\n");
	printf("PQEnqueue(queue, {Noam, 6})\n");
	printf("PQEnqueue(queue, {Liran, 3})\n");
	
	printf("\nPQueuePrint(queue, PrintDataFunc, NULL)\n");
    PQPrint(queue, PrintDataFunc, NULL);
    
    TEST("\nPQueueIsEmpty(queue)", PQIsEmpty(queue), 0);
    
    size = PQCount(queue);
    TEST("PQueueCount(queue)", size, 5);
    
    data = PQDequeue(queue);
	TEST("PQDequeue(queue)", ((data_t*)data)->priority, 7);
	
	printf("PQueuePrint(queue, PrintDataFunc, NULL)\n");
    PQPrint(queue, PrintDataFunc, NULL);
    
    data = PQPeek(queue);
	TEST("\nPQPeek(queue)", ((data_t*)data)->priority, 6);
    
    data = PQErase(queue, CmpPriorityMatch, &name6);
    TEST("PQErase(queue, CmpPriorityMatch, {Fei, 3})", ((data_t*)data)->priority, 3);
    
    printf("PQueuePrint(queue, PrintDataFunc, NULL)\n");
    PQPrint(queue, PrintDataFunc, NULL);
    
    PQClear(queue);
	size = PQCount(queue);
	TEST("\nPQClear(queue)", size, 0);
    
    PQDestroy(queue);
    TEST("PQDestroy(queue)", 1, 1);
    
	printf(CYAN"\nEnd Test\n\n"WHITE); 
}

int CmpDataFunc(void *val1, void *val2)
{
	data_t *data1 = (data_t*)val1;
	data_t *data2 = (data_t*)val2;
	
	return data2->priority - data1->priority;
}

int CmpPriorityMatch(void *val1, void *val2)
{
	data_t *data1 = (data_t*)val1;
	data_t *data2 = (data_t*)val2;
	
	return data2->priority == data1->priority;
}

int PrintDataFunc(void *data, void* param)
{
	data_t *value = NULL;
	param = param;
	
	value = (data_t*)(data);
	printf(MAG"%s, "WHITE, value->name);
	printf(MAG"\b\b.\n"WHITE);
	
	return 0;
}
