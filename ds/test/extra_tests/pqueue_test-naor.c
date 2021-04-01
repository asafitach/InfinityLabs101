#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/

#include "pqueue.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
	printf("%s: %s\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)

/*****************************************************************************/
static int printName(void *data, void *param);
static int CmpPriority( void *data, void *param);
static int PriorityMatch( void *data, void *param);

pq_t *TestPQCreate(pq_t *pq);
pq_t *TestPQEnqueue(pq_t *pq);
pq_t *TestPQDequeuePeek(pq_t *pq);
pq_t *TestPQErase(pq_t *pq, int priority);
pq_t *TestPQClear(pq_t *pq);

/*****************************************************************************/
typedef struct name
{
	char *name;
	int priority;
}name_t;

name_t name1 = {"Naor", 10};
name_t name2 = {"eden", 8};
name_t name3 = {"noam", 5};
name_t name4 = {"carmel", 3};
name_t name5 = {"liran", 4};

/*****************************************************************************/
int main()
{
	pq_t *pq = NULL;
	
	system("clear");
	
	
	pq = TestPQCreate(pq);
	pq = TestPQEnqueue(pq);
	pq = TestPQDequeuePeek(pq);
	pq = TestPQErase(pq, 8);
	pq = TestPQErase(pq, 12);
	
	pq = TestPQClear(pq);
	PQDestroy(pq);
	

	return (0); 
}
/*****************************************************************************/
static int printName(void *data, void *param) 
{ 
	name_t *name = (name_t *)data;
	(void)param;
	
	printf("%s, priority: %d\n",name->name, name->priority);
	
	return 0;
} 

/*****************************************************************************/
static int CmpPriority( void *data, void *param)
{
	name_t *name1 = (name_t *)data;
	name_t *name2 = (name_t *)param;
	
	return(name2->priority - name1->priority);
}

/*****************************************************************************/
static int PriorityMatch( void *data, void *param)
{
	name_t *name1 = (name_t *)data;
	return(name1->priority == *((int *)param));
}
/*****************************************************************************/
pq_t *TestPQCreate(pq_t *pq)
{

	printf(CYAN"\tTest PQueue Create\n\n"WHITE);
	
	pq = PQCreate(CmpPriority);	
	
	TEST("pq = PQCreate(IntCmpInsert) != NULL", (pq ? 1:0) , 1);
	
	TEST("PQIsEmpty(pq) == 1", PQIsEmpty(pq) , 1);
	
	TEST("PQCount(pq) == 0", PQCount(pq) , 0);

	printf(CYAN"\n\tEnd Test pqueue Create\n\n"WHITE);
	
	return(pq);
	

	
}
/*****************************************************************************/
pq_t *TestPQEnqueue(pq_t *pq)
{
	printf(CYAN"\tTest PQueue Enqueue\n\n"WHITE);
	PQEnqueue(pq, &name1);
	PQEnqueue(pq, &name2);
	PQEnqueue(pq, &name3);
	PQEnqueue(pq, &name4);
	PQEnqueue(pq, &name3);
	PQEnqueue(pq, &name2);
	PQEnqueue(pq, &name2);
	PQEnqueue(pq, &name1);
	PQEnqueue(pq, &name1);
	
	PQPrint(pq, printName, NULL);
	TEST("PQCount(pq) == 9", PQCount(pq) , 9);
	printf(CYAN"\n\tENd Test PQueue Enqueue\n\n"WHITE);
	return(pq);
}

/*****************************************************************************/
pq_t *TestPQDequeuePeek(pq_t *pq)
{
	name_t *peek = NULL;
	name_t *dequeue = NULL;
	
	printf(CYAN"\tTest PQueue Dequeue AND Peek\n\n"WHITE);
	
	peek = (name_t *)PQPeek(pq);
	dequeue = (name_t *)PQDequeue(pq);
	printf("peek to front of Queue name : \"%s\"\n",(char *)peek->name);
	TEST("PQPeek  == PQDequeue", peek , dequeue);
	TEST("PQCount(pq) == 8", PQCount(pq) , 8);
	
	peek = (name_t *)PQPeek(pq);
	dequeue = (name_t *)PQDequeue(pq);
	
	TEST("PQPeek  == PQDequeue", peek , dequeue);
	TEST("PQCount(pq) == 7", PQCount(pq) , 7);
	
	printf(CYAN"\n\tEnd Test PQueue Dequeue AND Peek\n\n"WHITE);
	return(pq);
}
/*****************************************************************************/
pq_t *TestPQClear(pq_t *pq)
{
	printf(CYAN"\tTest PQueue clear\n\n"WHITE);
	PQClear(pq);
	TEST("PQClear(pq); PQCount(pq) == 0", PQCount(pq) , 0);
	TEST("PQIsEmpty(pq) == 1", PQIsEmpty(pq) , 1);
	printf(CYAN"\n\tEnd Test PQueue clear\n\n"WHITE);
	return(pq);
}
/*****************************************************************************/
pq_t *TestPQErase(pq_t *pq, int priority)
{
	
	name_t *res = PQErase(pq, PriorityMatch, &priority);
	
	printf(CYAN"\tTest PQueue Erase\n\n"WHITE);
	
	if(NULL != res)
	{
		printf("the name with Priority : %d is : \"%s\" \n",priority, (char *)res->name);
		
	}
	else
	{
		printf("the  Priority : %d is not found on the list\n",priority);
	}
	printf(CYAN"\tEnd Test PQueue Erase\n\n"WHITE);
	return(pq);
		
}




