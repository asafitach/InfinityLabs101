#include <stdio.h>		/* printf */
#include <string.h>		/* strcmp */
#include "dllist.h"

#define RED "\033[1;31m"  /* print in red */
#define GREEN "\033[1;32m"    /* print in green */
#define BLUE "\033[1;34m"  /* print in blue */
#define YELLOW "\033[1;33m" /* print in yellow  */
#define PURPLE "\033[1;35m" /* print in purple */
#define RESET "\033[0m" /* reset print color  */


#define TEST(name, expected, real)\
            	(real == expected ? printf(GREEN"%s\tPASS.\n"RESET, name):\
            	 printf(RED"%s\tFAIL.\n"RESET, name))
            	 
#define CREATE(dlist)\
		do{		dlist = DlistCreate();\
				if (NULL == dlist)\
				{\
					return FAIL;\
				}\
				printf(BLUE"Dlist created.\n"RESET);\
		  }		while(0)

#define DESTROY(dlist)\
		do{		DlistDestroy(dlist);\
				printf(BLUE"Dlist destroyed.\n"RESET);\
		  }		while(0)
		
#define INSERT_TO_END(integer)\
		do{		iterator = DlistInsert(DlistEnd(dlist), (void*)integer);\
				data = DlistGetData(iterator);\
				printf(PURPLE"Value %d inserted\n"RESET, *(int*)&data);\
		  }		while(0)
		  
		
typedef enum
{
	SUCCESS,
	FAIL,
	CREATE_DESTROY_FAIL,
	INSERT_FAIL,
	PUSH_POP_FAIL,
	REMOVE_FAIL,
	GET_DATA_FAIL,
	SIZE_FAIL,
	FIND_ONE_FAIL,
	BEGIN_FAIL,
	END_FAIL,
	NEXT_FAIL,
	PREV_FAIL,
	FOREACH_FAIL,
	SPLICE_FAIL,
	IS_SAME_ITER_FAIL
	
}status_t;

status_t TestCreateDestroy();
status_t TestInsert();
status_t TestRemove();
status_t TestSize();
status_t TestPushPop();
status_t TestSplice();
status_t TestForEach();
status_t TestIsSameIter();
status_t TestFindOne();

static int IntCmpLList(void *data, void *param);
static int PrintDListInt(void *data, void *param);
static void print(dlist_t *list);

int main()
{
	int stat = SUCCESS;
	
	if (SUCCESS != TestCreateDestroy())
	{
		stat += CREATE_DESTROY_FAIL;
	}
	if (SUCCESS != TestInsert())
	{
		stat += INSERT_FAIL;
	}
	if (SUCCESS != TestRemove())
	{
		stat += REMOVE_FAIL;
	}
	if (SUCCESS != TestSize())
	{
		stat += SIZE_FAIL;
	}
	if (SUCCESS != TestPushPop())
	{
		stat += PUSH_POP_FAIL;
	}
	if (SUCCESS != TestSplice())
	{
		stat += SPLICE_FAIL;
	}
	if (SUCCESS != TestForEach())
	{
		stat += FOREACH_FAIL;
	}
	if (SUCCESS != TestIsSameIter())
	{
		stat += IS_SAME_ITER_FAIL;
	}
	if (SUCCESS != TestFindOne())
	{
		stat += FIND_ONE_FAIL;
	}
	return stat;
}


status_t TestCreateDestroy()
{
	dlist_t *dlist = NULL;
	printf(YELLOW"\n-----------TEST CREATE & DESTROY------------\n\n"RESET);
	dlist = DlistCreate();
	if (NULL == dlist)
	{
		return FAIL;
	}
	printf(BLUE"Dlist created.\n"RESET);
	
	DlistDestroy(dlist);
	printf(BLUE"Dlist destroyed.\n\n"RESET);
	
	return SUCCESS;
}


status_t TestInsert()
{
	void *data = NULL;
	dlist_t *dlist = NULL;
	dlist_iter_t iterator = NULL;
	printf(YELLOW"\n----------- TEST INSERT (DlistBegin, DlistEnd, DlistGetData) ------------\n\n"RESET);
	CREATE(dlist);
	
	iterator = DlistInsert(DlistBegin(dlist), (void*)3);
	data = DlistGetData(iterator);
	printf("Real value inserted is %d\n", *(int*)&data);
	printf("Expected value inserted is 3\n");
	TEST("Insert first element to the Begining", 3, *(int*)&data);
	
	iterator = DlistInsert(DlistBegin(dlist), (void*)17);
	data = DlistGetData(iterator);
	printf("Real value inserted is %d\n", *(int*)&data);
	printf("Expected value inserted is 17\n");
	TEST("Insert second element to begining", 17, *(int*)&data);
	
	iterator = DlistInsert(DlistEnd(dlist), (void*)5);
	data = DlistGetData(iterator);
	printf("Real value inserted is %d\n", *(int*)&data);
	printf("Expected value inserted is 5\n");
	TEST("Insert first element to the end ", 5, *(int*)&data);
	
	iterator = DlistInsert(DlistEnd(dlist), (void*)66);
	data = DlistGetData(iterator);
	printf("Real value inserted is %d\n", *(int*)&data);
	printf("Expected value inserted is 66\n");
	TEST("Insert second element to the end", 66, *(int*)&data);
	
	iterator = DlistInsert(iterator, (void*)100);
	data = DlistGetData(iterator);
	printf("Real value inserted is %d\n", *(int*)&data);
	printf("Expected value inserted is 100\n");
	TEST("Insert first element to the middle", 100, *(int*)&data);
	DESTROY(dlist);
	return SUCCESS;
}


status_t TestRemove()
{
	void *data = NULL;
	dlist_t *dlist = NULL;
	dlist_iter_t iterator = NULL;
	printf(YELLOW"\n----------- TEST REMOVE (DlistBegin, DlistEnd, DlistGetData) ------------\n\n"RESET);
	CREATE(dlist);
	
	INSERT_TO_END(3);
	print(dlist);
	iterator = DlistRemove(iterator);
	print(dlist);
	TEST("Remove with DlistRemove(iterator)", iterator, DlistEnd(dlist));

	INSERT_TO_END(3);
	print(dlist);
	iterator = DlistRemove(DlistBegin(dlist));
	print(dlist);
	TEST("Remove with DlistRemove(DlistBegin(dlist))", iterator, DlistEnd(dlist));
	
	INSERT_TO_END(3);
	INSERT_TO_END(4);
	INSERT_TO_END(5);
	
	print(dlist);
	iterator = DlistBegin(dlist);
	iterator = DlistRemove(DlistNext(iterator));
	print(dlist);
	TEST("Remove from the middle ", iterator, DlistPrev(DlistEnd(dlist)));
	
	DESTROY(dlist);
	return SUCCESS;
}


status_t TestSize()
{
	void *data = NULL;
	dlist_t *dlist = NULL;
	dlist_iter_t iterator = NULL;
	
	printf(YELLOW"\n----------- TEST SIZE-ISEMPTY ------------\n\n"RESET);
	CREATE(dlist);

	printf("The size is %lu\n", DlistSize(dlist));
	printf("Is empty? %d (0-false, 1-true)\n", DlistIsEmpty(dlist));
	
	TEST("Size of empty dlist", DlistSize(dlist), 0);
	TEST("Is empty for empty", DlistIsEmpty(dlist), 1);
	
	INSERT_TO_END(3);
	printf("The size is %lu\n", DlistSize(dlist));
	printf("Is empty? %d (0-faINSERT_TO_ENDlse, 1-true)\n", DlistIsEmpty(dlist));
	
	TEST("Size of 1 element dlist", DlistSize(dlist), 1);
	TEST("Is empty for not empty", DlistIsEmpty(dlist), 0);
	
	DESTROY(dlist);
	return SUCCESS;
}


status_t TestPushPop()
{
	size_t i = 0;
	dlist_t *dlist = NULL;
	printf(YELLOW"\n----------- TEST PUSH-POP FRONT-BACK (DlistBegin, DlistEnd, DlistGetData) ------------\n\n"RESET);
	CREATE(dlist);
	
	for (i = 0; i < 4; ++i)
	{
		DlistPushFront(dlist, (void*)i);
		printf(PURPLE"Value %d pushed front\n"RESET, *(int*)&i);
	}
	print(dlist);
	
	DlistPushBack(dlist, (void*)157);
	printf(PURPLE"Value 157 pushed back\n"RESET);
	print(dlist);
	
	DlistPushBack(dlist, (void*)164);
	printf(PURPLE"Value 164 pushed back\n"RESET);
	print(dlist);
	
	DlistPopFront(dlist);
	printf(PURPLE"Pop front\n"RESET);
	print(dlist);
	
	DlistPopBack(dlist);
	printf(PURPLE"Pop back\n"RESET);
	print(dlist);
	
	DESTROY(dlist);
	
	return SUCCESS;
}


status_t TestSplice()
{
	size_t i = 0;
	dlist_t *dlist1 = NULL;
	dlist_t *dlist2 = NULL;
	
	dlist_iter_t iter = NULL;
		
	dlist_iter_t from = NULL;
	dlist_iter_t to = NULL;
	dlist_iter_t dest = NULL;
	
	printf(YELLOW"\n----------- TEST SPLICE ------------\n\n"RESET);
	CREATE(dlist1);
	CREATE(dlist2);
	for (i = 0; i < 6; ++i)
	{
		iter = DlistPushBack(dlist1, (void*)i);
		if (4 == i)
		{
			dest = iter;
		}
		printf(PURPLE"Value %d pushed front\n"RESET, *(int*)&i);
	}
	printf("dlist1:\n");
	print(dlist1);
	
	for (i = 0; i < 6; ++i)
	{
		iter = DlistPushBack(dlist2, (void*)(i*100));
		if (1 == i)
		{
			from = iter;
		}
		if (4 == i)
		{
			to = iter;
		}
		printf(PURPLE"Value %d pushed front\n"RESET, *(int*)&i);
	}
	printf("dlist2:\n");
	print(dlist2);
	
	printf("\nSplice with dest = 4, from = 100, t0 = 400\n");
	DlistSplice(dest, from, to);
	printf("\ndlist1 after splice:\n");
	print(dlist1);
	printf("\ndlist2 after splice:\n");
	print(dlist2);
	
	DESTROY(dlist1);
	DESTROY(dlist2);

	return SUCCESS;
}


status_t TestForEach()
{
	size_t i = 0;
	dlist_t *dlist = NULL;
	printf(YELLOW"\n----------- TEST FOR EACH ------------\n\n"RESET);
	CREATE(dlist);

	for (i = 0; i < 4; ++i)
	{
		DlistPushBack(dlist, (void*)i);
		printf(PURPLE"Value %d pushed front\n"RESET, *(int*)&i);
	}
	
	printf("print list elements with DlistForeach:\n");
	if (SUCCESS != DlistForeach(DlistBegin(dlist), DlistEnd(dlist), PrintDListInt, NULL))
	{
		return FAIL;
	}
	printf("\n");
	DESTROY(dlist);
	
	return SUCCESS;
}


status_t TestIsSameIter()
{
	dlist_t *dlist = NULL;
	dlist_iter_t iterator1 = NULL;
	dlist_iter_t iterator2 = NULL;
	dlist_iter_t iterator3 = NULL;
	
	printf(YELLOW"\n----------- TEST FOR EACH ------------\n\n"RESET);
	CREATE(dlist);

	iterator1 = DlistPushBack(dlist, (void*)7);
	printf(PURPLE"Value 7 pushed front\n"RESET);
	iterator2 = DlistPushBack(dlist, (void*)7);
	printf(PURPLE"Value 7 pushed front\n"RESET);
	iterator3 = DlistPushBack(dlist, (void*)5);
	printf(PURPLE"Value 3 pushed front\n"RESET);
	
	TEST("Is same iter for same iterator's data   ", DlistIsSameIter(iterator1, iterator2), 1);
	TEST("Is same iter for different iterator's data", DlistIsSameIter(iterator2, iterator3), 0);
	printf("*PASS if all pushed elements printed\n");
	DESTROY(dlist);

	return SUCCESS;
}


status_t TestFindOne()
{
	size_t i = 0;
	void *x = NULL;
	dlist_iter_t iterator = NULL;
	dlist_t *dlist = NULL;
	printf(YELLOW"\n----------- TEST FIND ONE ------------\n\n"RESET);
	CREATE(dlist);
	for (i = 0; i < 4; ++i)
	{
		DlistPushBack(dlist, (void*)i);
		printf(PURPLE"Value %d pushed front\n"RESET, *(int*)&i);
	}
	
	printf("Print element with data=2:\n ");
	iterator = DlistFindOne(DlistBegin(dlist), DlistEnd(dlist), IntCmpLList, (void*)2);
	x = DlistGetData(iterator);
	printf("%d\n", *(int*)&x);
	
	TEST("Find element with data=2   ", *(int*)&x, 2);
	
	DESTROY(dlist);
	return SUCCESS;
}


static void print(dlist_t *list)
{
	void *data = NULL;
    dlist_iter_t iter = NULL;
    iter = DlistBegin(list);
    printf("Head --> ");
    
    while (NULL != DlistNext(iter))
    {
    	data = DlistGetData(iter);
        printf("%d --> ", *(int *)&data);
        iter = DlistNext(iter);
    }
    
    printf("Tail ");
    printf("\n");
}

static int PrintDListInt(void *data, void *param)
{
	(void)param;
	printf("%d ", *(int*)data);
	return SUCCESS;
}

static int IntCmpLList(void *data, void *param)
{
	return (*(int*)&data == *(int*)&param) ? 0 : 1;
}

