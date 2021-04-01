#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include <string.h>
#include <assert.h>

#include "pqueue.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"

#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void TestCreateIsemptyDestroy();
void TestEnqueuePeekIsemptyCount();
void TestDeQueue();
void TestNextPreSpliceIssameiter();
void TestForeach();
void TestFindMulti();


int main()
{
    system("clear");
    
    TestCreateIsemptyDestroy();
    TestEnqueuePeekIsemptyCount();
    TestDeQueue();
	TestFindMulti();
	TestNextPreSpliceIssameiter();
	TestForeach();

    return (0); 
}

/******************************************************************************/

int StrCmp (void *data, void *param)
{
	return (strcmp((char *)param, (char *)data));
}

void TestCreateIsemptyDestroy()
{
	pq_t *pq = NULL;
	
    printf(CYAN"\tTest \n\n"WHITE); 
    
    pq = PQCreate(StrCmp);
    TEST(" create ", (pq != NULL) , 1); 
  
    TEST(" is empty ", PQIsEmpty(pq) , 1); 

	PQDestroy(pq);
}

/******************************************************************************/

void TestEnqueuePeekIsemptyCount()
{
	pq_t *pq = NULL;
	char *str = "hello!";

	pq = PQCreate(StrCmp);
	
	PQEnQueue(pq, (void*)str);	
    
    TEST(" insert + peek ", (PQPeek(pq) == (void*)str) , 1); 

    TEST(" is empty when it isn't' ", PQIsEmpty(pq) , 0); 

	PQClear(pq);    

    TEST(" remove ", PQCount(pq) , 0);     

	PQDestroy(pq);
}

/******************************************************************************/

void TestDeQueue()
{
	pq_t *pq = NULL;
	char *str = "hello!";
	char *str2 = " world";
	pq = PQCreate(StrCmp);
    
    PQEnQueue(pq, (void*)str);
    PQEnQueue(pq, (void*)str2);
    
    TEST(" insert + size ", PQCount(pq) , 2); 
    	
	    
    PQDeQueue(pq);

    TEST(" insert + size ", PQDeQueue(pq), (void *)str2); 
    
    TEST(" pop front + back + size ", PQCount(pq) , 0);    

	PQDestroy(pq);
}

/*************************tool functions***************************************/
int IsEqual(void *data, void *param)
{
	int res = 0;
	char *ptr1 = (char *)data;
	char *ptr2 = (char *)param;
	res = strcmp(ptr1, ptr2);
	return (!res);
}

int PrintList2(void *data, void *param)
{
	param = param;
	printf("\n%s\n", (char*)data);
	return(0);
}
/******************************************************************************/
int IsMatch(void *data, void *param)
{
	return (!StrCmp(data, param));
}

void TestFindMulti()
{
	/*pq_t *pq = NULL;
	pq_t *pq2 = NULL;
	char *str = "hello!";
	char *str2 = "world";
	pq = PQCreate(StrCmp);
	pq2 = PQCreate(StrCmp);
	 
	 
    PQEnQueue(pq, (void*)str);
    PQEnQueue(pq, (void*)str);
	PQEnQueue(pq, (void*)str); 
    PQEnQueue(pq, (void*)str2);


	  
	PQDestroy(pq);
	PQDestroy(pq2);
*/}

/******************************************************************************/

void TestNextPreSpliceIssameiter()
{

}

/******************************************************************************/
	

void TestForeach()
{
	pq_t *pq = NULL;
	char *str = "hello!";
	char *str2 = " world";
	pq = PQCreate(StrCmp);	

    PQEnQueue(pq, (void*)str);
    PQEnQueue(pq, (void*)str2);	
    PQEnQueue(pq, (void*)str);
    PQEnQueue(pq, (void*)str2);	

#ifndef NDEBUG
	PQPrint(pq, PrintList2, (void *)str2);
#endif
	
    TEST("\n erase ", PQErase(pq, IsMatch, (void *)str2) , (void *)str2); 

#ifndef NDEBUG
    PQPrint(pq, PrintList2, (void *)str2);
#endif    	

    printf(CYAN"\tEnd Test \n\n"WHITE); 
    
	PQDestroy(pq);
}

/******************************************************************************/



