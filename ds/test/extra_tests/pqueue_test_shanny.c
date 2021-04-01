#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include "pqueue.h"

#define RED "\33[1;5;31m"
#define GREEN "\33[1;32m"
#define WHIT "\33[0m"
#define MAG "\33[1;96m"
#define YEL "\33[1;33m"

#define TEST(testName,real,expected)\
            (real == expected ?\
                printf("%s:" GREEN" PASS\n"WHIT, testName) :\
                printf("%s:"  RED" FAIL\n"WHIT, testName))
               

#define TEST_NOT(testName,real,expected)\
            (real != expected ?\
                printf("%s:" GREEN" PASS\n"WHIT, testName) :\
                printf("%s:"  RED" FAIL\n"WHIT, testName))               
                
typedef enum 
{
	SUCCESS = 0,
	FAIL = 1
} status_t;
              
status_t Testqueue(); 
static pq_t *TestCreate(pq_t *pq);
static void TestIEmpty(pq_t *pq, int bol);
static void TestPeek(pq_t *pq, int peek);
static void TestEnpqueue(pq_t *pq, int *arr, int size);
static void TestDepqueue(pq_t *pq);
static void TestCount(pq_t *pq, size_t count);
static int IsMatch(void *data, void *param);
int cmp_func(void *data, void *param);
static void TestClear(pq_t *pq);
static void TestErase(pq_t *pq, int arr[], int param);
#ifndef NDEBUG
static void TestPrint(pq_t *pq);
static int IntPrint(void *data, void *param);
#endif
int main()
{
	printf(MAG"\tTest pqueue:\n"WHIT);
	TEST("The test complete succesfuly", Testqueue(), 0);
	                         
	return 0;
} 

status_t Testqueue()
{
	pq_t *pq = NULL;
	int arr[] = {6,8,30,10,99};
	int arr2[] = {-5,20,-4,100,35,67};
	int size = sizeof(arr)/sizeof(int);	
	int size2 = sizeof(arr2)/sizeof(int);				
	pq = TestCreate(pq);
	TestIEmpty(pq, 1);
	TestEnpqueue(pq, arr, size);
	TestPeek(pq, 10);
	TestCount(pq, 5);	

	#ifndef NDEBUG		
	TestPrint(pq);
	#endif
	TestErase(pq, arr + 1, 30);
	TestClear(pq);
	printf(MAG"Inserting new elements:\n"WHIT);
	TestEnpqueue(pq, arr2, size2);
	TestCount(pq, 6);	
	#ifndef NDEBUG		
	TestPrint(pq);
	#endif
	TestDepqueue(pq);		
	PQDestroy(pq);
	
	return SUCCESS;
}

static pq_t *TestCreate(pq_t *pq)
{
	pq = PQCreate(cmp_func);
	TEST_NOT("The pqueue created", pq, NULL);	
	
	return pq;
}

static void TestIEmpty(pq_t *pq, int bol)
{	
	assert(NULL != pq);
	
	printf(MAG"Test is empty:\n"WHIT);
	if (1 == bol)
	{
		TEST("The pqueue is empty", PQIsEmpty(pq), bol);
	}
	else 
	TEST("The pqueue is not empty", PQIsEmpty(pq), bol);	
}

static void TestEnpqueue(pq_t *pq, int arr[], int size)
{
	int i = 0;	
	
	printf(MAG"Test insert:\n"WHIT);
	
	while(i < size)
	{
		printf ("%d ", *(int *)(arr + i));
		++i;
	} 
	
	printf ("\n"); 
	i = 0;
	while(i < size)
	{
		PQEnqueue(pq, arr + i);
		++i;
	} 
}

static void TestPeek(pq_t *pq, int peek)
{
	assert(NULL != pq);
	
	printf(MAG"Test peek data:\n"WHIT);
	printf("Value %d, ", peek);				
	TEST("is the first value", *(int *)PQPeek(pq), peek);
}

static void TestCount(pq_t *pq, size_t count)
{
	assert(NULL != pq);
	
	printf(MAG"Test Count list:\n"WHIT);
	printf("The pqueue have %lu ", count);	
	TEST("value", PQCount(pq), count);	
	
}

static void TestDepqueue(pq_t *pq)
{
	assert(NULL != pq);
	
	printf(MAG"Test dequeue:\n"WHIT);			
	while (3 != PQCount(pq))
	{
		PQDequeue(pq);
	}

	TEST("remove succesfuly",*(int *)PQDequeue(pq), -4);
}

static void TestErase(pq_t *pq, int *arr, int param)
{
	void *res = NULL;
	
	printf(MAG"Test erase above 15:\n"WHIT);	
	printf("Serching for %d to erase, ", param);	
	res = PQErase(pq, IsMatch, arr);
	TEST("erase succesfuly", *(int *)res, param);
	
}
#ifndef NDEBUG
static void TestPrint(pq_t *pq)
{

	printf(MAG"Test print only in dbug:\n"WHIT);	
	PQPrint(pq, IntPrint, 0);
	printf("\n");	

}
#endif

static void TestClear(pq_t *pq)
{
	printf(MAG"Test clear all element:\n"WHIT);	
	PQClear(pq);
	TEST("The pqueue is empty", PQIsEmpty(pq), 1);
}

int cmp_func(void *data, void *param)
{
	if (0 == *(int *)data % 10 && *(int *)data - *(int *)param)
	{
		return -1;
	}
	
	return 1;
}

static int IsMatch(void *data, void *param)
{
	*(int *)param = 15;
	return *(int *)data > *(int *)param;
}

#ifndef NDEBUG

static int IntPrint(void *data, void *param)
{
	param = param;
	printf("%d ", *(int *)data);
	
	return 0;
}

#endif
               
