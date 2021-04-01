#include <stdio.h>

#include "pqueue.h"
#define SIZE 5
#define TEST_NOT(str, real, expected) (real != expected ?\
							 	  printf(GREEN"\n%sSUCCES\n"RESET, str) :\
							 	  printf(RED"\n%sFAIL\n"RESET, str))

#define TEST(str, real, expected) (real == expected ?\
							 	  printf(GREEN"\n%sSUCCES\n"RESET, str) :\
							 	  printf(RED"\n%sFAIL\n"RESET, str))

#define RED "\033[1;31m"  /* print in red */
#define GREEN "\033[1;32m"    /* print in green */
#define BLUE "\033[1;34m"  /* print in blue */
#define YELLOW "\033[1;33m" /* print in yellow  */
#define PURPLE "\033[1;35m" /* print in purple */
#define RESET "\033[0m" /* reset print color  */

void TestInt();
static int IntCmpFunc(void *data, void *param);
void TestPQEnqueue(pq_t *pq, int arr[]);
static int PrintInt(void *data, void *param);
void TestDepqCountPeek(pq_t *pq);
void TestErase(pq_t *pq);

int main()
{
	TestInt();
	return 0;
}



void TestInt()
{
	pq_t *pq = NULL;
	int arr[SIZE] = {4, 3, 1, 5, 2};
	printf(BLUE"\n*******************Int Test**********************\n"RESET);
	pq = PQCreate(IntCmpFunc);
	printf(PURPLE"\n*****************Create PQ***********************\n"RESET);
	TEST_NOT("Test if PQ is NULL: ", pq, NULL);
	TestPQEnqueue(pq, arr);
	TEST("Test IsEmpty when PQ is full : ", PQIsEmpty(pq), 0);
	
	TestDepqCountPeek(pq);
	TEST("Test IsEmpty when PQ is empty : ", PQIsEmpty(pq), 1);
	
	TestPQEnqueue(pq, arr);
	printf(PURPLE"\n*****************Clear Test**********************\n"RESET);
	TEST("Test IsEmpty when PQ is full : ", PQIsEmpty(pq), 0);
	TestErase(pq);
	PQClear(pq);
	TEST("Test IsEmpty when PQ is empty : ", PQIsEmpty(pq), 1);
	
	PQDestroy(pq);
			
}

/*****************************************************************************/

static int IntIsEqualFunc(void *data, void *param)
{
    return (*(int*)data == *(int*)param);
}


/*****************************************************************************/


static int PrintInt(void *data, void *param)
{
	param = param;
	printf(GREEN"%d "RESET, *(int*)data);
	return(0);
}
/*****************************************************************************/

static int IntCmpFunc(void *data, void *param)
{
    return (*(int*)data - *(int*)param);
}
/*****************************************************************************/

void TestPQEnqueue(pq_t *pq, int arr[])
{
	int i = 0;
	
	
	printf(PURPLE"\n****Enqueue elements****\n"RESET);
	for (i = 0; i < SIZE; ++i)
	{
		TEST("element enqueue : ", PQEnqueue(pq, arr + i), 0);
	}
	
	PQPrint(pq, (print_func_t)PrintInt, NULL);
	printf("\n");
}

/*****************************************************************************/

void TestDepqCountPeek(pq_t *pq)
{
	int i = 0;
	int count = 0;
	void *peek = 0;
	printf(PURPLE"\n****dequeue elements****\n"RESET);
	for (i = 0; i < SIZE; ++i)
	{
		peek = PQPeek(pq);
		printf("\npeeking - expected: %d actual: %d\n", i + 1, *(int*)peek);
		PQDequeue(pq);
		count = PQCount(pq);
		printf("counting - expected: %d actual: %d\n", count, SIZE - i - 1);
		TEST("is count-=1 after element depq? ", count, SIZE - i - 1);
	}
}	

/*****************************************************************************/

void TestErase(pq_t *pq)
{
	int x = 3;
	int y = 10;
	void *erased = PQErase(pq, (pq_match_t)IntIsEqualFunc, &x);
	TEST("check if found --->", *(int*)erased, 3);
	PQPrint(pq, (print_func_t)PrintInt, NULL);
	erased = PQErase(pq, (pq_match_t)IntIsEqualFunc, &y);	
	TEST("check if not found --->", erased, NULL);
	PQPrint(pq, (print_func_t)PrintInt, NULL);

}
