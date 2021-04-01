#include <stdio.h>		/* printf */
#include <string.h>		/* strcmp */
#include "pqueue.h"


#define RED "\033[1;31m"  /* print in red */
#define GREEN "\033[1;32m"    /* print in green */
#define BLUE "\033[1;34m"  /* print in blue */
#define YELLOW "\033[1;33m" /* print in yellow */
#define PURPLE "\033[1;35m" /* print in purple */
#define RESET "\033[0m" /* reset print color  */


#define TEST(name, expected, real)\
            	(real == expected ? printf(GREEN"%s\tPASS.\n"RESET, name):\
            	 printf(RED"%s\tFAIL.\n"RESET, name))

#define CREATE(pq)\
		do{		pq = PQCreate(IntCmpFunc);\
				if (NULL == pq)\
				{\
					return FAIL;\
				}\
				printf(BLUE"pq created.\n"RESET);\
		  }		while(0)

#define DESTROY(pq)\
		do{		PQDestroy(pq);\
				printf(BLUE"pq destroyed.\n"RESET);\
		  }		while(0)
		
#define PENQUEUE(integer)\
		do{		PQEnqueue(pq, integer);\
				printf(PURPLE"Insert value %d\n"RESET, *(int*)integer);\
		  }		while(0)
		  
#define PDEQUEUE()\
		do{		data = PQDequeue(pq);\
				printf(PURPLE"Next in line is: %d\n"RESET, *(int*)data);\
		  }		while(0)



typedef enum
{
	SUCCESS,
	FAIL,
	CREATE_DESTROY_FAIL,
	PENQUEUE_FAIL,
	REMOVE_FAIL,
	GET_DATA_FAIL,
	SIZE_FAIL,
	ERASE_FAIL
	
}status_t;

status_t TestCreateDestroy();
status_t TestPEnqueue();
status_t TestRemove();
status_t TestCount();
status_t TestClear();
status_t TestErase();

#ifndef NDEBUG
status_t TestPrint();
#endif

static int IntCmpFunc(void *data, void *param);
static int PrintInt(void *data, void *param);
static int IsIlegal(void *data, void *param);

int main()
{
	int stat = SUCCESS;
	
	if (SUCCESS != TestCreateDestroy())
	{
		stat += CREATE_DESTROY_FAIL;
	}
	if (SUCCESS != TestPEnqueue())
	{
		stat += PENQUEUE_FAIL;
	}
	if (SUCCESS != TestRemove())
	{
		stat += REMOVE_FAIL;
	}
	if (SUCCESS != TestCount())
	{
		stat += SIZE_FAIL;
	}
	if (SUCCESS != TestClear())
	{
		stat += SIZE_FAIL;
	}
	if (SUCCESS != TestErase())
	{
		stat += ERASE_FAIL;
	}
	#ifndef NDEBUG
	TestPrint();
	#endif
	return stat;
}


status_t TestCreateDestroy()
{
	pq_t *pq = NULL;
	printf(YELLOW"\n-----------TEST CREATE & DESTROY------------\n\n"RESET);
	pq = PQCreate(IntCmpFunc);
	if (NULL == pq)
	{
		return FAIL;
	}
	printf(BLUE"pq created.\n"RESET);
	
	PQDestroy(pq);
	printf(BLUE"pq destroyed.\n\n"RESET);
	
	return SUCCESS;
}


status_t TestPEnqueue()
{
	void *data = NULL;
	int x3 = 3;
	int x17 = 17;
	int x5 = 5;
	int x66 = 66;
	int x100 = 100;
	
	pq_t *pq = NULL;
	printf(YELLOW"\n----------- TEST PENQUEUE AND DEQUEUE (PQDequeue) ------------\n\n"RESET);
	
	CREATE(pq);
	PENQUEUE(&x3);
	PENQUEUE(&x100);
	PENQUEUE(&x17);
	PENQUEUE(&x5);
	PENQUEUE(&x66);
	printf("In this queue smaill values treated first.\n");
	PDEQUEUE();
	PDEQUEUE();
	PDEQUEUE();
	PDEQUEUE();
	PDEQUEUE();
	
	DESTROY(pq);
	
	return SUCCESS;
}


status_t TestRemove()
{
	void *data = NULL;
	int x100 = 100;
	pq_t *pq = NULL;
	printf(YELLOW"\n----------- TEST REMOVE (PQDequeue)------------\n\n"RESET);
	CREATE(pq);
	PENQUEUE(&x100);
	PDEQUEUE();
	DESTROY(pq);
	return SUCCESS;
}


status_t TestCount()
{
	int x3 = 3;
	pq_t *pq = NULL;
	
	printf(YELLOW"\n----------- TEST COUNT AND ISEMPTY (PQDequeue) ------------\n\n"RESET);
	CREATE(pq);

	printf("The size is %lu\n", PQCount(pq));
	printf("Is empty? %d (0-false, 1-true)\n", PQIsEmpty(pq));
	
	TEST("Size of empty pq\t", PQCount(pq), 0);
	TEST("Is empty for empty\t", PQIsEmpty(pq), 1);
	
	PENQUEUE(&x3);
	printf("The size is %lu\n", PQCount(pq));
	printf("Is empty? %d (0-false, 1-true)\n", PQIsEmpty(pq));
	
	TEST("Size of 1 element pq\t", PQCount(pq), 1);
	TEST("Is empty for not empty\t", PQIsEmpty(pq), 0);
	
	DESTROY(pq);
	return SUCCESS;
}


status_t TestClear()
{
	int x3 = 3;
	int x17 = 17;
	int x5 = 5;
	int x66 = 66;
	int x100 = 100;
	
	pq_t *pq = NULL;
	printf(YELLOW"\n----------- TEST CLEAR ------------\n\n"RESET);
	
	CREATE(pq);
	PENQUEUE(&x3);
	PENQUEUE(&x100);
	PENQUEUE(&x17);
	PENQUEUE(&x5);
	PENQUEUE(&x66);
	printf("Is empty? %d (0-false, 1-true)\n", PQIsEmpty(pq));
	printf("The size is %lu\n", PQCount(pq));
	PQClear(pq);
	printf("Cleared\n");
	printf("Is empty? %d (0-false, 1-true)\n", PQIsEmpty(pq));
	printf("The size is %lu\n", PQCount(pq));
	TEST("Size after clear pq\t", PQCount(pq), 0);
	DESTROY(pq);
	return SUCCESS;
}


status_t TestErase()
{
	size_t i = 0;
	int arr[] = {20, 17, 15, 18};
	void *data = NULL;
	int param = 16;
	pq_t *pq = NULL;
	printf(YELLOW"\n----------- TEST ERASE ------------\n\n"RESET);
	CREATE(pq);
	for (i = 0; i < 4; ++i)
	{
		PQEnqueue(pq, &arr[i]);
		printf(PURPLE"Value %d inserted\n"RESET, arr[i]);
	}
	data = PQErase(pq, IsIlegal, &param);
	printf("Removed the one under 16\n");
	printf("The intruder is %d\n", *(int*)data);
	printf("The size after erase is %lu\n", PQCount(pq));
	TEST("Intruder found\t", *(int*)data, 15);
	DESTROY(pq);
	return SUCCESS;
}


#ifndef NDEBUG
status_t TestPrint()
{
	int x3 = 3;
	int x17 = 17;
	int x100 = 100;
	pq_t *pq = NULL;
	printf(YELLOW"\n----------- TEST PRINT ------------\n\n"RESET);
	
	CREATE(pq);
	PENQUEUE(&x3);
	PENQUEUE(&x100);
	PENQUEUE(&x17);
	printf("The pqueue elements are:\n");
	PQPrint(pq, PrintInt, NULL);
	printf("\n");
	DESTROY(pq);
	return SUCCESS;
}
#endif

static int PrintInt(void *data, void *param)
{
	(void)param;
	printf("%d ", *(int*)data);
	return SUCCESS;
}

/* for PQErase */
/* return true if data < 16 */
static int IsIlegal(void *data, void *param)
{
	return (*(int*)data < *(int*)param) ? 1 : 0;
}

/* for PQCreate */
static int IntCmpFunc(void *p_num1, void *p_num2)
{
	return *(int*)p_num1 - *(int*)p_num2;
}
