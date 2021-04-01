#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h>

#include "pqueue.h"

/*********************************Test Macros**********************************/

#define TEST(name, real, expected) \
		printf(CYAN"%s %s\n", name, real == expected ? \
		GREEN"SUCCESS"RESET : RED"FAIL"RESET)
		
#define TEST_NOT(name, real, expected) \
		printf(CYAN"%s %s\n", name, real != expected ? \
		GREEN"SUCCESS"RESET : RED"FAIL"RESET)
		
/******************************Color definitions*******************************/

#define RED "\033[5;91m"      /* print in red          */
#define GREEN "\033[1;92m"    /* print in green        */
#define MAGEN "\033[1;95m"    /* print in magenta      */
#define YELLOW "\033[1;93m"   /* print in light yellow */
#define CYAN "\033[1;96m"     /* print in cyan         */
#define LIGHT "\033[2;37m"    /* print in gray         */
#define RESET "\033[1;0m"     /* reset print color     */

/***************************Test Struct Definition*****************************/

typedef struct test
{
	int data;
	int priority;
} test_t;

/**************************Test functions declarations*************************/

static int TestPQStruct(size_t size);
static void TestPQInt(void);
static pq_t *TestCreate(pq_cmp_t pq_cmp);
static void TestIsEmpty(pq_t *pq, int expected);
static void TestClear(pq_t *pq);

static void TestPQDequeueStruct(pq_t *pq, test_t *expected);
static void TestPeekStruct(pq_t *pq, test_t *expected);
static void TestEraseStruct(pq_t *pq, pq_match_t pq_match, void *param, void *expected, int hits);

static void TestErase(pq_t *pq, pq_match_t pq_match, void *param, void *expected, int hits);
static void TestPeek(pq_t *pq, int expected);
static void TestPQDequeue(pq_t *pq, int expected);

/**************************Help functions declarations*************************/

static int IntCmpFunc(void *data, void *param);
static void InsertArray(pq_t *pq, int *array, size_t length);
static int IsIntMatch(void *data, void *param);
static int StructCmpFunc(void *data, void *param);
static int IsStructMatch(void *data, void *param);
static void InsertStructs(pq_t *pq, test_t *test_array, size_t length);

#ifndef NDEBUG
static int PrintInt(void *data, void *param);
static int PrintStruct(void *data, void *param);
#endif 

/************************************Main**************************************/

int main()
{
	TestPQInt();
	TestPQStruct(5);
	
	return (0);
}

/**************************Test functions definitions**************************/

static void TestPQInt(void)
{
	#ifndef NDEBUG
	size_t count = 0;
	#endif
	int array[] = {0, 23, -1, 3, 200, -10};
	pq_t *pq = NULL;
	
	printf(YELLOW"\n-----Test 1 - Integer-----\n\n"RESET);
	printf(MAGEN"--Creating a priority queue & testing if it is empty--\n\n"RESET);
	pq = TestCreate(IntCmpFunc);
	
	TestIsEmpty(pq, 1);

	printf(MAGEN"\n--Inserting nums 0, 23, -1, 3, 200, -10--\n"RESET);
	InsertArray(pq, array, 6);
	
	#ifndef NDEBUG
	printf(MAGEN"\n--Printing PQ using PQPrint--\n"RESET);
	PQPrint(pq, PrintInt, &count);
	TEST("\nPQPrint  ", PQCount(pq), count);
	#endif
	
	printf(MAGEN"\n--Testing Count--\n"RESET);
	TEST("PQCount  ", PQCount(pq), 6);
	
	printf(MAGEN"\n--Testing Peek--\n"RESET);
	TestPeek(pq, -10);
	
	printf(MAGEN"\n--Testing Dequeue--\n"RESET);
	TestPQDequeue(pq, -10);
	
	printf(MAGEN"\n--Erasing num 23 from the queue--\n"RESET);
	TestErase(pq, IsIntMatch, array + 1, array + 1, 1);
	
	#ifndef NDEBUG
	printf(MAGEN"\n--Printing PQ using PQPrint--\n"RESET);
	PQPrint(pq, PrintInt, &count);
	#endif
	
	TestIsEmpty(pq, 0);
	
	printf(MAGEN"\n--Testing Clear--\n"RESET);
	TestClear(pq);
	PQDestroy(pq);
	
	printf(YELLOW"\n-----End Of Test-----\n\n"RESET);
}

/*****************************************************************************/

static int TestPQStruct(size_t size)
{
	#ifndef NDEBUG
	size_t count = 0;
	#endif
	
	pq_t *pq = NULL;
	test_t *test_ptr = (test_t *)malloc(sizeof(test_t) * size);
	if (NULL == test_ptr)
	{
		return (1);
	}

	printf(YELLOW"\n-----Test 2 - Struct { int data, int priority }-----\n\n"RESET);
	printf(MAGEN"--Creating a priority queue & testing if it is empty--\n\n"RESET);
	
	pq = TestCreate(StructCmpFunc);
	TestIsEmpty(pq, 1);

	printf(MAGEN"\n--Inserting %lu structs--\n"RESET, size);
	InsertStructs(pq, test_ptr, size);
	
	#ifndef NDEBUG
	printf(MAGEN"\n--Printing PQ using PQPrint--\n"RESET);
	PQPrint(pq, PrintStruct, &count);
	TEST("\nPQPrint  ", PQCount(pq), count);
	#endif
	
	printf(MAGEN"\n--Testing Count--\n"RESET);
	TEST("PQCount  ", PQCount(pq), size); 
	
	printf(MAGEN"\n--Testing Peek--\n"RESET);
	TestPeekStruct(pq, test_ptr + size - 1);
	
	printf(MAGEN"\n--Testing Dequeue--\n"RESET);
	TestPQDequeueStruct(pq, test_ptr + size - 1);
	
	printf(MAGEN"\n--Erasing data with priority 2 from the queue--\n"RESET);
	TestEraseStruct(pq, IsStructMatch, test_ptr + size - 2, test_ptr + size - 2, 1);
	
	TestIsEmpty(pq, 0);
	
	printf(MAGEN"\n--Testing Clear--\n"RESET);
	TestClear(pq);
	PQDestroy(pq);
	free(test_ptr);
	test_ptr = NULL;
	
	printf(YELLOW"\n-----End Of Test-----\n\n"RESET);
	
	return (0);
}

/*****************************************************************************/

static void TestErase(pq_t *pq, pq_match_t pq_match, void *param, void *expected, int hits)
{
	size_t count = PQCount(pq);
	void *result = PQErase(pq, pq_match, param);
	TEST(RESET"Testing by count: "CYAN"PQErase ", count - hits, PQCount(pq));
	TEST(RESET"Testing by value: "CYAN"PQErase ", *(int *)result, *(int *)expected);
}

static void TestEraseStruct(pq_t *pq, pq_match_t pq_match, void *param, void *expected, int hits)
{
	size_t count = PQCount(pq);
	test_t *test_struct = (test_t *)param;
	test_t *expected_struct = (test_t *)expected;
	void *result = PQErase(pq, pq_match, param);
	int res = 0;
	
	test_struct =  (test_t *)result;
	TEST(RESET"Testing by count: "CYAN"PQErase ", count - hits, PQCount(pq));
	
	printf("Expected:\nData: %d\nPriority: %d\n", expected_struct->data, expected_struct->priority);
	printf("By Peek :\nData: %d\nPriority: %d\n", test_struct->data, test_struct->priority);
	
	res = StructCmpFunc(test_struct, expected);
	TEST("PQErase  ", res, 0);
}

/*****************************************************************************/

static void TestIsEmpty(pq_t *pq, int expected)
{
	int is_empty = PQIsEmpty(pq);
	
	TEST("PQIsEmpty", is_empty, expected);
	
	if (1 == is_empty)
	{
		printf(LIGHT"Sorted list is empty\n\n"RESET);
	}
	else
	{
		printf("Sorted list is not empty\n\n");		
	}
}

/*****************************************************************************/

static void TestPeek(pq_t *pq, int expected)
{
	void *data = PQPeek(pq);
	printf("Expected: %d\nData is:  %d\n", expected, *(int *)data);
	TEST("PQPeek   ", *(int *)data, expected);
}

static void TestPeekStruct(pq_t *pq, test_t *expected)
{
	test_t *test_struct = (test_t *)PQPeek(pq);
	int res = 0;
	
	printf("Expected:\nData: %d\nPriority: %d\n", expected->data, expected->priority);
	printf("By Peek :\nData: %d\nPriority: %d\n", test_struct->data, test_struct->priority);
	
	res = StructCmpFunc(test_struct, expected);
	TEST("PQPeek   ", res, 0);
}

/*****************************************************************************/

static void TestPQDequeue(pq_t *pq, int expected)
{
	void *data = PQDequeue(pq);
	printf("Expected: %d\nData is:  %d\n", expected, *(int *)data);
	TEST("PQDequeue", *(int *)data, expected);	
}

static void TestPQDequeueStruct(pq_t *pq, test_t *expected)
{
	test_t *test_struct = (test_t *)PQPeek(pq);
	int res = 0;
	
	printf("Expected:\nData: %d\nPriority: %d\n", expected->data, expected->priority);
	printf("By Peek :\nData: %d\nPriority: %d\n", test_struct->data, test_struct->priority);
	
	res = StructCmpFunc(test_struct, expected);
	TEST("PQDequeue ", res, 0);	
}

/*****************************************************************************/

static void TestClear(pq_t *pq)
{
	PQClear(pq);
	TEST("PQClear   ", PQCount(pq), 0);
}

static pq_t *TestCreate(pq_cmp_t pq_cmp)
{
	pq_t *pq = PQCreate(pq_cmp);
	
	TEST_NOT("PQCreate ", pq, NULL);
	
	return (pq);
}

/*****************************************************************************/

static void InsertArray(pq_t *pq, int *array, size_t length)
{
	size_t i = 0;
	int res = 0;
	
	while (length > i)
	{
		res = PQEnqueue(pq, array + i);	
		TEST("PQEnqueue", res, 0);
		++i;
	}
}

static void InsertStructs(pq_t *pq, test_t *test_array, size_t length)
{
	int i = 0;
	int res = 0;
	int len = (int)length;
		
	while (i < len)
	{
		test_array[i].data = len - i;
		test_array[i].priority = i;
		++i;
	} 
	i = 0; 
	while (i < len)
	{	
		res = PQEnqueue(pq, test_array + i);
		TEST("PQEnqueue", res, 0);
		++i;
	} 
}

/*****************************************************************************/

static int IsIntMatch(void *data, void *param)
{
	return (*(int *)data == *(int *)param);
}

static int IntCmpFunc(void *data, void *param)
{	
	return (*(int *)data - *(int *)param);
}

static int IsStructMatch(void *data, void *param)
{
	test_t *test_struct = (test_t *)data;
	test_t *test_struct2 = (test_t *)param;
	
	return(test_struct->priority == test_struct2->priority);
}

static int StructCmpFunc(void *data, void *param)
{
	test_t *test_struct = (test_t *)data;
	test_t *test_struct2 = (test_t *)param;
	
	return(test_struct2->priority - test_struct->priority);
}

/*****************************************************************************/

#ifndef NDEBUG
static int PrintInt(void *data, void *param)
{
	size_t *tmp = (size_t *)param;
	++(*tmp);
	printf("%d  ", *(int *)data);
	return (0);
}


static int PrintStruct(void *data, void *param)
{
	test_t *test_struct = (test_t *)data;
	size_t *tmp = (size_t *)param;
	++(*tmp);
	printf("Data: %d\nPriority: %d\n", test_struct->data, test_struct->priority);
	return (0);
}
#endif
