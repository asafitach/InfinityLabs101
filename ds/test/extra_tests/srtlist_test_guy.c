#include <stdio.h>		/* printf */
#include <string.h>		/* strcmp */
#include "srtlist.h"

#define RED "\033[1;31m"  /* print in red */
#define GREEN "\033[1;32m"    /* print in green */
#define BLUE "\033[1;34m"  /* print in blue */
#define YELLOW "\033[1;33m" /* print in yellow  */
#define PURPLE "\033[1;35m" /* print in purple */
#define RESET "\033[0m" /* reset print color  */


#define TEST(name, expected, real)\
            	(real == expected ? printf(GREEN"%s\tPASS.\n"RESET, name):\
            	 printf(RED"%s\tFAIL.\n"RESET, name))
            	 
#define CREATE(srtlist)\
		do{		srtlist = SrtListCreate(IntCmpFunc);\
				if (NULL == srtlist)\
				{\
					return FAIL;\
				}\
				printf(BLUE"Srtlist created.\n"RESET);\
		  }		while(0)

#define DESTROY(srtlist)\
		do{		SrtListDestroy(srtlist);\
				printf(BLUE"Srtlist destroyed.\n"RESET);\
		  }		while(0)
		
#define INSERT(integer)\
		do{		iterator = SrtListInsert(srtlist, (void*)&integer);\
				data = SrtListGetData(iterator);\
				printf(PURPLE"Value %d inserted\n"RESET, *(int*)data);\
		  }		while(0)
		  
		
typedef enum
{
	SUCCESS,
	FAIL,
	CREATE_DESTROY_FAIL,
	INSERT_FAIL,
	POP_FAIL,
	REMOVE_FAIL,
	GET_DATA_FAIL,
	SIZE_FAIL,
	FIND_FAIL,
	FIND_IF_FAIL,
	BEGIN_FAIL,
	END_FAIL,
	NEXT_FAIL,
	PREV_FAIL,
	FOREACH_FAIL,
	MERGE_FAIL
	
}status_t;

status_t TestCreateDestroy();
status_t TestInsert();
status_t TestRemove();
status_t TestSize();
status_t TestPop();
status_t TestForEach();
status_t TestFind();
status_t TestMerge();
status_t TestMerge2();
status_t TestFindIf();

static int IntCmpFunc(void *data, void *param);
static int PrintSrtlistInt(void *data, void *param);
static void print(srtlist_t *list);
static int IsEqualInt(void *data, void *param);

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
	if (SUCCESS != TestPop())
	{
		stat += POP_FAIL;
	}
	if (SUCCESS != TestForEach())
	{
		stat += FOREACH_FAIL;
	}
	if (SUCCESS != TestMerge())
	{
		stat += MERGE_FAIL;
	}
	if (SUCCESS != TestMerge2())
	{
		stat += MERGE_FAIL;
	}
	if (SUCCESS != TestFind())
	{
		stat += FIND_FAIL;
	}
	if (SUCCESS != TestFindIf())
	{
		stat += FIND_IF_FAIL;
	}
	return stat;
}


status_t TestCreateDestroy()
{
	srtlist_t *srtlist = NULL;
	printf(YELLOW"\n-----------TEST CREATE & DESTROY------------\n\n"RESET);
	srtlist = SrtListCreate(IntCmpFunc);
	if (NULL == srtlist)
	{
		return FAIL;
	}
	printf(BLUE"srtlist created.\n"RESET);
	
	SrtListDestroy(srtlist);
	printf(BLUE"srtlist destroyed.\n\n"RESET);
	
	return SUCCESS;
}


status_t TestInsert()
{
	void *data = NULL;
	int x3 = 3;
	int x17 = 17;
	int x5 = 5;
	int x66 = 66;
	int x100 = 100;
	
	srtlist_t *srtlist = NULL;
	srtlist_iter_t iterator = NULL;
	printf(YELLOW"\n----------- TEST INSERT (SrtListBegin, SrtListEnd, SrtListGetData) ------------\n\n"RESET);
	CREATE(srtlist);
	
	iterator = SrtListInsert(srtlist, &x3);
	data = SrtListGetData(iterator);
	printf("Real value inserted is %d\n", *(int*)data);
	printf("Expected value inserted is 3\n");
	TEST("Insert element\t", 3, *(int*)data);
	
	iterator = SrtListInsert(srtlist, &x100);
	data = SrtListGetData(iterator);
	printf("Real value inserted is %d\n", *(int*)data);
	printf("Expected value inserted is 100\n");
	TEST("Insert element\t", 100, *(int*)data);
	
	iterator = SrtListInsert(srtlist, &x17);
	data = SrtListGetData(iterator);
	printf("Real value inserted is %d\n", *(int*)data);
	printf("Expected value inserted is 17\n");
	TEST("Insert element\t", 17, *(int*)data);
	
	iterator = SrtListInsert(srtlist, &x5);
	data = SrtListGetData(iterator);
	printf("Real value inserted is %d\n", *(int*)data);
	printf("Expected value inserted is 5\n");
	TEST("Insert element\t", 5, *(int*)data);
	
	iterator = SrtListInsert(srtlist, &x66);
	data = SrtListGetData(iterator);
	printf("Real value inserted is %d\n", *(int*)data);
	printf("Expected value inserted is 66\n");
	TEST("Insert element\t", 66, *(int*)data);
	printf("The list state is:\n");
	print(srtlist);
	DESTROY(srtlist);
	return SUCCESS;
}


status_t TestRemove()
{
	void *data = NULL;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;
	
	srtlist_t *srtlist = NULL;
	srtlist_iter_t iterator = NULL;
	printf(YELLOW"\n----------- TEST REMOVE (SrtListBegin, SrtListEnd, SrtListGetData) ------------\n\n"RESET);
	CREATE(srtlist);
	
	INSERT(x3);
	print(srtlist);
	iterator = SrtListRemove(iterator);
	print(srtlist);
	TEST("Remove with SrtListRemove(iterator)\t\t", iterator, SrtListEnd(srtlist));

	INSERT(x3);
	print(srtlist);
	iterator = SrtListRemove(SrtListBegin(srtlist));
	print(srtlist);
	TEST("Remove with SrtListRemove(SrtListBegin(srtlist))", iterator, SrtListEnd(srtlist));
	
	INSERT(x3);
	INSERT(x4);
	INSERT(x5);
	
	print(srtlist);
	iterator = SrtListBegin(srtlist);
	iterator = SrtListRemove(SrtListNext(iterator));
	print(srtlist);
	TEST("Remove from the middle\t\t\t\t", iterator, SrtListPrev(SrtListEnd(srtlist)));
	
	DESTROY(srtlist);
	return SUCCESS;
}


status_t TestSize()
{
	void *data = NULL;
	int x3 = 3;
	srtlist_t *srtlist = NULL;
	srtlist_iter_t iterator = NULL;
	
	printf(YELLOW"\n----------- TEST SIZE-ISEMPTY ------------\n\n"RESET);
	CREATE(srtlist);

	printf("The size is %lu\n", SrtListSize(srtlist));
	printf("Is empty? %d (0-false, 1-true)\n", SrtListIsEmpty(srtlist));
	
	TEST("Size of empty srtlist\t", SrtListSize(srtlist), 0);
	TEST("Is empty for empty\t", SrtListIsEmpty(srtlist), 1);
	
	INSERT(x3);
	printf("The size is %lu\n", SrtListSize(srtlist));
	printf("Is empty? %d (0-false, 1-true)\n", SrtListIsEmpty(srtlist));
	
	TEST("Size of 1 element srtlist\t", SrtListSize(srtlist), 1);
	TEST("Is empty for not empty\t", SrtListIsEmpty(srtlist), 0);
	
	DESTROY(srtlist);
	return SUCCESS;
}


status_t TestPop()
{
	int i = 0;
	int arr[] = {0, 1, 2, 3};
	
	srtlist_t *srtlist = NULL;
	printf(YELLOW"\n----------- TEST POP FRONT-BACK (SrtListBegin, SrtListEnd, SrtListGetData) ------------\n\n"RESET);
	CREATE(srtlist);
	
	for (i = 0; i < 4; ++i)
	{
		SrtListInsert(srtlist, &arr[i]);
		printf(PURPLE"Value %d inserted\n"RESET, arr[i]);
	}
	print(srtlist);
	
	SrtListPopFront(srtlist);
	printf(PURPLE"Pop front\n"RESET);
	print(srtlist);
	
	SrtListPopBack(srtlist);
	printf(PURPLE"Pop back\n"RESET);
	print(srtlist);
	printf(RED"Please note if the lists are printed as expected\n"RESET);
	DESTROY(srtlist);
	
	return SUCCESS;
}


status_t TestForEach()
{
	size_t i = 0;
	int arr[] = {0, 1, 2, 3};
	srtlist_t *srtlist = NULL;
	printf(YELLOW"\n----------- TEST FOR EACH ------------\n\n"RESET);
	CREATE(srtlist);

	for (i = 0; i < 4; ++i)
	{
		SrtListInsert(srtlist, &arr[i]);
		printf(PURPLE"Value %d inserted\n"RESET, arr[i]);
	}
	
	printf("print list elements with SrtlistForeach:\n");
	if (SUCCESS != SrtListForeach(SrtListBegin(srtlist), SrtListEnd(srtlist), PrintSrtlistInt, NULL))
	{
		return FAIL;
	}
	printf("\n");
	printf(RED"Please note if the lists are printed as expected\n"RESET);
	DESTROY(srtlist);
	
	return SUCCESS;
}


status_t TestMerge()
{
	int i = 0;
	int arr[] = {101, 102, 103, 304, 505};
	int arr2[] = {0, 400, 200, 300, 100, 500};
	
	srtlist_t *srtlist1 = NULL;
	srtlist_t *srtlist2 = NULL;
	
	printf(YELLOW"\n----------- TEST MERGE ------------\n\n"RESET);
	CREATE(srtlist1);

	for (i = 0; i < 5; ++i)
	{
		SrtListInsert(srtlist1, &arr[i]);
		printf(PURPLE"Value %d inserted\n"RESET, arr[i], RESET);
	}
	printf("srtlist1 content:\n");
	print(srtlist1);
	
	CREATE(srtlist2);
	for (i = 0; i < 6; ++i)
	{
		SrtListInsert(srtlist2, &arr2[i]);
		printf(PURPLE"Value %d inserted\n"RESET, arr2[i],RESET);
	}
	printf("srtlist2 content:\n");
	print(srtlist2);
	
	printf("\nResult of merge srtlist1 into srtlist2\n");
	SrtListMerge(srtlist2, srtlist1);
	
	printf("\nsrtlist1 content after splice:\n");
	print(srtlist1);
	printf("\nsrtlist2 content after splice:\n");
	print(srtlist2);
	
	TEST("Extected size of srtlist1\t", SrtListSize(srtlist1), 0);
	TEST("Expected size of dsrtlist2\t", SrtListSize(srtlist2), 11);

	printf(RED"Please note also if the lists are printed as expected\n"RESET);
	DESTROY(srtlist1);
	DESTROY(srtlist2);

	return SUCCESS;
}

status_t TestMerge2()
{
	int i = 0;
	int arr[] = {101, 102, 103};
	int arr2[] = {0, 1};
	
	srtlist_t *srtlist1 = NULL;
	srtlist_t *srtlist2 = NULL;
	
	printf(YELLOW"\n----------- TEST MERGE2 ------------\n\n"RESET);
	CREATE(srtlist1);

	for (i = 0; i < 3; ++i)
	{
		SrtListInsert(srtlist1, &arr[i]);
		printf(PURPLE"Value %d inserted\n"RESET, arr[i], RESET);
	}
	printf("srtlist1 content:\n");
	print(srtlist1);
	
	CREATE(srtlist2);
	for (i = 0; i < 2; ++i)
	{
		SrtListInsert(srtlist2, &arr2[i]);
		printf(PURPLE"Value %d inserted\n"RESET, arr2[i],RESET);
	}
	printf("srtlist2 content:\n");
	print(srtlist2);
	
	printf("\nResult of merge srtlist1 into srtlist2\n");
	SrtListMerge(srtlist2, srtlist1);
	
	printf("\nsrtlist1 content after splice:\n");
	print(srtlist1);
	printf("\nsrtlist2 content after splice:\n");
	print(srtlist2);
	
	TEST("Extected size of srtlist1\t", SrtListSize(srtlist1), 0);
	TEST("Expected size of dsrtlist2\t", SrtListSize(srtlist2), 5);

	printf(RED"Please note also if the lists are printed as expected\n"RESET);
	DESTROY(srtlist1);
	DESTROY(srtlist2);

	return SUCCESS;
}


status_t TestFind()
{
	size_t i = 0;
	void *x = NULL;
	int arr[] = {0, 1, 2, 3};
	int x_dummy = 7;
	srtlist_iter_t iterator = NULL;
	srtlist_t *srtlist = NULL;
	printf(YELLOW"\n----------- TEST FIND ------------\n\n"RESET);
	CREATE(srtlist);
	for (i = 0; i < 4; ++i)
	{
		SrtListInsert(srtlist, &arr[i]);
		printf(PURPLE"Value %d inserted\n"RESET, arr[i]);
	}
	
	iterator = SrtListFind(SrtListBegin(srtlist), SrtListEnd(srtlist), &arr[2]);
	x = DlistGetData(iterator);
	TEST("Succeed finding value 2  \t", *(int*)x, 2);
	
	iterator = SrtListFind(SrtListBegin(srtlist), SrtListEnd(srtlist), &x_dummy);
	TEST("Failure finding value 7  \t", iterator, SrtListEnd(srtlist));
	DESTROY(srtlist);
	return SUCCESS;
}


status_t TestFindIf()
{
	size_t i = 0;
	void *x = NULL;
	int arr[] = {0, 1, 2, 3};
	int x_dummy = 7;
	srtlist_iter_t iterator = NULL;
	srtlist_t *srtlist = NULL;
	printf(YELLOW"\n----------- TEST FIND IF ------------\n\n"RESET);
	CREATE(srtlist);
	for (i = 0; i < 4; ++i)
	{
		SrtListInsert(srtlist, &arr[i]);
		printf(PURPLE"Value %d inserted\n"RESET, arr[i]);
	}
	
	iterator = SrtListFindIf(SrtListBegin(srtlist), SrtListEnd(srtlist),IsEqualInt, &arr[2]);
	x = DlistGetData(iterator);
	TEST("Succeed finding value 2  \t", *(int*)x, 2);
	
	iterator = SrtListFindIf(SrtListBegin(srtlist), SrtListEnd(srtlist),IsEqualInt, &x_dummy);
	TEST("Failure finding value 7  \t", iterator, SrtListEnd(srtlist));
	DESTROY(srtlist);
	return SUCCESS;
}

static void print(srtlist_t *list)
{
	void *data = NULL;
    srtlist_iter_t iter = NULL;
    srtlist_iter_t end = NULL;
    
    end = SrtListEnd(list);
    iter = SrtListBegin(list);
    printf("Head --> ");
    
    while (end != iter)
    {
    	data = SrtListGetData(iter);
        printf("%d --> ", *(int*)data);
        iter = SrtListNext(iter);
    }
    
    printf("Tail ");
    printf("\n");
}

static int PrintSrtlistInt(void *data, void *param)
{
	(void)param;
	printf("%d ", *(int*)data);
	return SUCCESS;
}

static int IntCmpFunc(void *p_num1, void *p_num2)
{
	return *(int*)p_num1 - *(int*)p_num2;
}

static int IsEqualInt(void *data, void *param)
{
	return (*(int*)&data == *(int*)&param) ? 1 : 0;
}

