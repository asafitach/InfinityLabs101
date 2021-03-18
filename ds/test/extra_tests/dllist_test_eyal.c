#include <stdio.h> /*printf*/
#include "dllist.h"

#define TEST_NOT(str, real, expected) (real != expected ?\
							 	  printf(GREEN"%sSUCCESS\n"RESET, str) :\
							 	  printf(RED"%sFAIL\n"RESET, str))

#define TEST(str, real, expected) (real == expected ?\
							 	  printf(GREEN"%sSUCCESS\n"RESET, str) :\
							 	  printf(RED"%sFAIL\n"RESET, str))

#define RED "\033[1;31m"  /* print in red */
#define GREEN "\033[1;32m"    /* print in green */
#define BLUE "\033[1;34m"  /* print in blue */
#define YELLOW "\033[1;33m" /* print in yellow  */
#define PURPLE "\033[1;35m" /* print in purple */
#define RESET "\033[0m" /* reset print color  */

/*****************************************************************************/

static void TestInt();
static void TestInsert(dlist_iter_t iterator, size_t elements);
static void TestGetNext(dlist_iter_t iterator, size_t elements);
static void TestSize(dlist_t *list, size_t elements);
static int IntIsEqualFunc(void *data, void *param);
static void TestFindOne(const dlist_iter_t from, const dlist_iter_t to, 
			  is_equal_func_t is_equal_func, void *param);
static void TestRemove(dlist_iter_t iterator, size_t elements,
					   dlist_t *list);			  
static int PrintInt(void *data, void *param);
static void TestSplice(dlist_iter_t dest, dlist_iter_t from,
					   dlist_iter_t to, dlist_t *list, dlist_t *dest_list);
static void TestPushPop(dlist_t *list);
static void TestFindMulty(dlist_t *list);

/*****************************************************************************/

int main()
{
	TestInt();

	return (0);
}

/*****************************************************************************/

static void TestInt()
{
	
	int elements = 5;
	dlist_t *list = DlistCreate();
	dlist_t *dest_list = DlistCreate();
	dlist_iter_t dest = NULL;
	dlist_iter_t from = NULL;
	dlist_iter_t to = NULL;
	printf(BLUE"\n*******************Int Test**********************\n"RESET);
	
	printf("\n*****Create doubly linked list*****\n");
	TEST_NOT("\nTest if list is NULL: ", list, NULL);
	
	TestInsert(DlistBegin(list), elements);
	TestInsert(DlistBegin(dest_list), elements - 2);

	dest = DlistNext(DlistBegin(dest_list));
	from = DlistNext(DlistBegin(list));
	to = DlistPrev(DlistEnd(list));	
	TestSplice(dest, from, to, list, dest_list);
	
	DlistDestroy(list);
	DlistDestroy(dest_list);
	
	list = DlistCreate();
	TestInsert(DlistBegin(list), elements);
		
	printf(PURPLE"\n****Test Foreach using print****\n"RESET);
	DlistForeach(DlistBegin(list), DlistEnd(list), PrintInt, 0);	
	
	printf(PURPLE"\n****IsEmpty Test****\n"RESET);
	TEST("Test if list is Empty: ", DlistIsEmpty(list), 0);
	
	TestGetNext(DlistBegin(list), elements);
	
	TestSize(list, elements);
	TestFindOne(DlistBegin(list), DlistEnd(list), IntIsEqualFunc, (void *)3);
	TestRemove(DlistBegin(list),elements, list);			  
	
	printf(PURPLE"\n****IsEmpty Test****\n"RESET);
	TEST("Test if list is Empty: ", DlistIsEmpty(list), 1);
	
	DlistDestroy(list);
	list = DlistCreate();
	TestPushPop(list);
	DlistDestroy(list);
	
	list = DlistCreate();
	TestFindMulty(list);
	DlistDestroy(list);
	
	printf(YELLOW"\n\n\n****End of Test****\n\n\n"RESET);
}

/*****************************************************************************/
	
static void TestInsert(dlist_iter_t iterator, size_t elements)
{
	size_t i = 0;
	printf(PURPLE"\n****inserting %lu elements****\n"RESET, elements);
	for (i = 0; i < elements; ++i)
	{
		iterator = DlistInsert(iterator, (void*)i);
		TEST_NOT("element insertion : ", iterator, NULL);
	}
}
	
/*****************************************************************************/
	
static void TestGetNext(dlist_iter_t iterator, size_t elements)
{
	size_t i = 0;
	void *data = NULL;
	printf(PURPLE"\n****geting %lu elements****\n"RESET, elements);
	for (i = 0; i < elements; ++i)
	{
		data = DlistGetData(iterator);
		printf("expected: %ld real: %ld  --->", elements - i - 1, (size_t)data);
		TEST(" ", data, (void*)(elements - i - 1));
		iterator = DlistNext(iterator);
	}	
}

/*****************************************************************************/
	
static void TestSize(dlist_t *list, size_t elements)
{
	size_t size = 0;
	printf(PURPLE"\n****Size Test****\n"RESET);
	size = DlistSize(list);
	printf("expected: %ld real: %ld  --->", elements, size);
	TEST(" ", size, elements);
} 

/*****************************************************************************/
	
static void TestFindOne(const dlist_iter_t from, const dlist_iter_t to, 
			  is_equal_func_t is_equal_func, void *param)
{
	void *data = NULL;
	dlist_iter_t result = DlistFindOne(from, to, is_equal_func, param);
	printf(PURPLE"\nlooking for param: %d\n"RESET, *(int *)&param);
	if (NULL == result)
	{
		printf("the element is not on the list");
		return;
	}
	data = DlistGetData(result);
	TEST("Test if param found : ", data, param);
}

/*****************************************************************************/
	
static int IntIsEqualFunc(void *data, void *param)
{
    return (data == param);
}

/*****************************************************************************/

static void TestRemove(dlist_iter_t iterator, size_t elements, dlist_t *list)
{
	size_t i = 0;
	size_t size = 0;
	printf(PURPLE"\n****removing %lu elements****\n"RESET, elements);
	for (i = 0; i < elements; ++i)
	{
		iterator = DlistRemove(iterator);
		size = DlistSize(list);
		printf("size after removal expected: %ld, real: %ld --->",
			    							size, elements - i - 1);
		TEST(" ", size, elements - i - 1);
	}
}

/*****************************************************************************/

static int PrintInt(void *data, void *param)
{
	param = param;
	printf(GREEN"%d "RESET, *(int*)data);
	return(0);
}

/*****************************************************************************/

static void TestSplice(dlist_iter_t dest, dlist_iter_t from,
					   dlist_iter_t to, dlist_t *list, dlist_t *dest_list)
{
	printf(PURPLE"\n****Splice Test****\n"RESET);
	printf("dest pre-splise: ");
	DlistForeach(DlistBegin(dest_list), DlistEnd(dest_list), PrintInt, 0);	
	printf("list pre-splise: ");	
	DlistForeach(DlistBegin(list), DlistEnd(list), PrintInt, 0);	
	DlistSplice(dest, from, to);
	printf("\nexcpected dest: 2 3 2 1 1 0   excpected list: 4 0\n");
	printf("real dest:      ");
	DlistForeach(DlistBegin(dest_list), DlistEnd(dest_list), PrintInt, 0);	
	printf("  real list:      ");	
	DlistForeach(DlistBegin(list), DlistEnd(list), PrintInt, 0);	
}

/*****************************************************************************/

static void TestPushFront(dlist_t *list, size_t param)
{
	void *data = NULL;
	DlistPushFront(list, (void*)param);
	data = DlistGetData(DlistBegin(list));
	printf("expected: %ld real: %ld  --->", param, (size_t)data);
	TEST(" ", (size_t)data, param);
}

/*****************************************************************************/

static void TestPushBack(dlist_t *list, size_t param)
{
	void *data = NULL;
	DlistPushBack(list, (void*)param);
	data = DlistGetData(DlistPrev(DlistEnd(list)));
	printf("expected: %ld real: %ld  --->", (size_t)param, (size_t)data);
	TEST(" ", (size_t)data, param);
}	

/*****************************************************************************/

static void TestPushPop(dlist_t *list)
{
	void *data = NULL;
	printf(PURPLE"\n****PushPop Test****\n"RESET);
	
	TestPushFront(list, 1);
	TestPushFront(list, 2);
	TestPushBack(list, 3);	
	
	data = DlistPopBack(list); 
	printf("expected: %ld real: %ld  --->", (size_t)3, (size_t)data);
	TEST(" ", (size_t)data, 3);
	
	data = DlistPopFront(list); 
	printf("expected: %ld real: %ld  --->", (size_t)2, (size_t)data);
	TEST(" ", (size_t)data, 2);
	
	data = DlistPopFront(list); 
	printf("expected: %ld real: %ld  --->", (size_t)1, (size_t)data);
	TEST(" ", (size_t)data, 1);
	
	if (DlistIsEmpty(list) == 0)
	{
		printf(RED"list should be empty ---> FAIL"RESET);
	}
}

/*****************************************************************************/
static void TestFindMulty(dlist_t *list)
{
	size_t i = 0;
	int found = 0;
	dlist_iter_t from = NULL;
	dlist_iter_t to = NULL;
	dlist_t *dest = DlistCreate();
	printf(PURPLE"\n****FindMulti Test****\n"RESET);
		
	for (i = 0; i < 10; ++i)
	{
		DlistPushFront(list, (void *)(i / 2));
	}
	for (i = 10; i > 0; --i)
	{
		DlistPushFront(list, (void *)(i / 2));
	}
	from = DlistBegin(list);
	to = DlistEnd(list);
	
	printf(PURPLE"The original list: "RESET);
	DlistForeach(DlistBegin(list), DlistEnd(list), PrintInt, 0);
	printf(PURPLE"Begin to End Test: "RESET);
	
	found = DlistFindMulti(from, to, IntIsEqualFunc, (void*)3, dest);
	printf("\n\nexpected: %d real: %d  --->", 4, found);
	TEST(" ", found, 4);
	printf(PURPLE"\nTest if dest nodes pointing to correct data :");
	TEST("", DlistGetData(DlistGetData(DlistBegin(dest))), (void*)3);
	
	DlistDestroy(dest);
	dest = DlistCreate();
	printf(PURPLE"\nMiddle Test: "RESET);
	
	for (i = 0; i < 2; ++i)
	{
		from = DlistNext(from);
		to = DlistPrev(to);
	}
	
	found = DlistFindMulti(from, to, IntIsEqualFunc, (void*)1, dest);
	printf("\n\nexpected: %d real: %d  --->", 3, found);
	TEST(" ", found, 3);
	printf(PURPLE"\nThe destenation list :");
	TEST("", DlistGetData(DlistGetData(DlistBegin(dest))), (void*)1);
		
	DlistDestroy(dest);
}
	

