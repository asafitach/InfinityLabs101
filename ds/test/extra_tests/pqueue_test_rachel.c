#include <stdlib.h> /* system */
#include <stdio.h> /* printf */

#include "pqueue.h"

#define RED "\033[1;31m" 
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"
#define RESET "\033[0m" 


#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)

typedef enum
{
	SUCCESS = 0,
	CREATE_FAIL = 1,
	PQENQUEUE_FAIL = 2
} test_status_t;


static test_status_t Test();  
  
int main()
{
	int status = SUCCESS;
	
    system("clear");
    
    status = Test();

    return (status); 
}

static int CmpInt(void *data, void *param);
static int IsMatchInt(void *var1, void *var2);
static int PrintInt(void *num1, void *num2);


static test_status_t Test()
{
	int data1 = 7;
	int data2 = 10;
	int data3 = 4;
	void *data = NULL;
	pq_t *pqueue = PQCreate(CmpInt); 
       
    if (NULL == pqueue)
    {
    	return (CREATE_FAIL);
    } 
    
    TEST("PQCreate()", (pqueue == NULL), 0);
	TEST("PQIsEmpty", PQIsEmpty(pqueue), 1);
    
if (0 != PQEnQueue(pqueue, &data1))
    {
    	return (PQENQUEUE_FAIL);
    }
    data = PQPeek(pqueue); 
    TEST("PQEnQueue" , *(int*)data, data1);
    
	if (0 != PQEnQueue(pqueue, &data2))
    {
    	return (PQENQUEUE_FAIL);
    }
    data = PQPeek(pqueue); 
    TEST("PQPeek" , *(int*)data, data2);
    
    if (0 != PQEnQueue(pqueue, &data3))
    {
    	return (PQENQUEUE_FAIL);
    }
    
    data = PQPeek(pqueue); 
    TEST("PQEnQueue" , *(int*)data, data2);
    
    TEST("PQCount", PQCount(pqueue), 3);
    
    printf("PQPrint:\n");
	PQPrint(pqueue, PrintInt, NULL);

	data = PQDeQueue(pqueue);
    TEST("\nPQDeQueue" , *(int*)data, data2);
    
    data = PQErase(pqueue, IsMatchInt, &data1);
    TEST("PQErase" , *(int*)data, data1);
    
    PQClear(pqueue);
    TEST("PQClear", PQIsEmpty(pqueue), 1);
        
    PQDestroy(pqueue);
    
    return (SUCCESS);
}

static int CmpInt(void *data, void *param)
{
	if (((*(int*)data % 5) == 0) && ((*(int*)param % 5) == 0))
	{
		return (0);
	}
	else if ((*(int*)data % 5) == 0)
	{
		return (-1);
	}
	else 
	{
		return (1);
	}
}

static int IsMatchInt(void *var1, void *var2)
{
	return (*(int*)var1 == *(int*)var2);
}

static int PrintInt(void *num1, void *num2)
{
	printf("%d\n", *(int*)num1);
	(void)num2;
	
	return (0);
}

