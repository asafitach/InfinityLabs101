/*********************************Headers*************************************/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#include "pqueue.h"

/*****************************************************************************/

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define WHITE "\033[0m"

#define TEST_ARE_EQUAL(name, expected, actual)\
     printf("%s\n%s\n\n", name, actual == expected ? GREEN"PASSED"WHITE : RED"FAILED"WHITE)

#define TEST_ARE_NOT_EQUAL(name, expected, actual) printf("%s\n%s\n\n", name, expected != actual ? GREEN"PASSED"WHITE : RED"FAILED"WHITE)

#define PQ_CREATE pq_t *pq = PQCreate(CmpPriority)

#define PQ_DESTROY PQDestroy(pq)

/*****************************************************************************/

void TestPQCreate();

void TestPQClear();

void TestPQEnqueue();

void TestPQDequeue();

void TestPQPeek();

void TestPQCount();

void TestPQIsEmpty();

void TestPQErase();

static int CmpPriority(void *x, void *y);

static int CmpInt(void *xp, void *yp);

static int PrintElement(void *data, void *param);

/*****************************************************************************/

int main()
{
	TestPQCreate();
	
	TestPQClear();

	TestPQEnqueue();

	TestPQDequeue();

	TestPQPeek();

	TestPQCount();

	TestPQIsEmpty();

	TestPQErase();
	
	return 0;
}

/*****************************************************************************/

void TestPQCreate()
{
	PQ_CREATE;
	
	TEST_ARE_NOT_EQUAL("TestPQCreate1", pq, NULL);
	TEST_ARE_EQUAL("TestPQCreate2", PQIsEmpty(pq), 1);

	PQ_DESTROY;
}

/*****************************************************************************/

void TestPQEnqueue()
{
	PQ_CREATE;
	
	int data = 1;
	
	PQEnqueue(pq, &data);
	
	TEST_ARE_EQUAL("TestPQEnqueue1", *(int *)PQPeek(pq), data);
	TEST_ARE_EQUAL("TestPQEnqueue2", PQCount(pq), (size_t)1);
	
	PQ_DESTROY;
}

/*****************************************************************************/

void TestPQDequeue()
{
	PQ_CREATE;
	
	int data1 = 2;
	int data2 = 1;
	int data3 = 3;
	
	PQEnqueue(pq, &data1);
	PQEnqueue(pq, &data2);
	PQEnqueue(pq, &data3);
	
	PQPrint(pq, PrintElement, NULL);
	
	TEST_ARE_EQUAL("TestPQDequeue1", *(int *)PQDequeue(pq), data2);
	TEST_ARE_EQUAL("TestPQDequeue2", *(int *)PQPeek(pq), data1);
	TEST_ARE_EQUAL("TestPQDequeue3", PQCount(pq), (size_t)2);
	
	PQPrint(pq, PrintElement, NULL);
	
	PQ_DESTROY;
}

/*****************************************************************************/

void TestPQClear(void)
{
    PQ_CREATE;
    
    int data1 = 2;
    int data2 = 1;
    int data3 = 3;
    
    PQEnqueue(pq, &data1);
    PQEnqueue(pq, &data2);
    PQEnqueue(pq, &data3);
    
    PQClear(pq);
    
    TEST_ARE_EQUAL("TestPQClear", PQIsEmpty(pq), 1);
    
    PQ_DESTROY;
}

/*****************************************************************************/

void TestPQPeek()
{
	PQ_CREATE;
	
	int data1 = 2;
	int data2 = 1;
	int data3 = 3;
	
	PQEnqueue(pq, &data1);
	PQEnqueue(pq, &data2);
	PQEnqueue(pq, &data3);
	
	TEST_ARE_EQUAL("TestPQPeek1", *(int *)PQPeek(pq), data2);
	
	PQDequeue(pq);
	PQDequeue(pq);
	PQDequeue(pq);
	
	TEST_ARE_EQUAL("TestPQPeek2", PQPeek(pq), NULL);

	PQ_DESTROY;
}

/*****************************************************************************/

void TestPQCount()
{
	PQ_CREATE;
	
	int data1 = 2;
	int data2 = 1;
	int data3 = 3;
	
	PQEnqueue(pq, &data1);
	PQEnqueue(pq, &data2);
	PQEnqueue(pq, &data3);
	
	TEST_ARE_EQUAL("TestPQCount", PQCount(pq), (size_t)3);

	PQ_DESTROY;
}

/*****************************************************************************/

void TestPQIsEmpty()
{
	PQ_CREATE;
	
	int data1 = 2;
	
	TEST_ARE_EQUAL("TestPQIsEmpty1", PQIsEmpty(pq), 1);
	
	PQEnqueue(pq, &data1);
	
	TEST_ARE_EQUAL("TestPQIsEmpty2", PQIsEmpty(pq), 0);
	
	PQ_DESTROY;
}

/*****************************************************************************/

void TestPQErase()
{
	PQ_CREATE;	
	
	int data1 = 2;
	int data2 = 1;
	int data3 = 3;
	
	PQEnqueue(pq, &data1);
	PQEnqueue(pq, &data2);
	PQEnqueue(pq, &data3);
	
	TEST_ARE_EQUAL("TestPQErase1", *(int *)PQErase(pq, CmpInt, &data2), data2);
	TEST_ARE_EQUAL("TestPQErase2", PQErase(pq, CmpInt, &data2), NULL);
	
	PQ_DESTROY;
}

/*****************************************************************************/

int CmpPriority(void *xp, void *yp)
{
	return (*(int *)xp - *(int *)yp);
}

/*****************************************************************************/

int CmpInt(void *xp, void *yp)
{
	return (*(int *)xp == *(int *)yp) ? 1 : 0;
}

/*****************************************************************************/

int PrintElement(void *data, void *param)
{
	assert(!param);
	
	printf("%d <== ", *(int *)data);
	
	return (0);
}

/*****************************************************************************/

