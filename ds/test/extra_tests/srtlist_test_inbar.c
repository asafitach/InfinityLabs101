#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strcmp */

#include "srtlist.h" 

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

/**************************Test functions declarations*************************/

static srtlist_t *TestOne(int *array);
static srtlist_t *TestTwo(int *array);

static srtlist_t *TestCreate(srtlist_t *srtlist);
static int IntCmpFunc(void *data, void *param);
static void TestIsEmpty(srtlist_t *srtlist, int expected);
static void TestGetData(srtlist_iter_t iterator, int expected);
static srtlist_iter_t TestRemove(srtlist_t *srtlist, srtlist_iter_t iterator);
static void TestPop(char direction, srtlist_t *srtlist, int expected);
static void TestFind(srtlist_t *srtlist, int *to_find);
static void TestForEach(srtlist_iter_t from, srtlist_iter_t to, srtlist_t *srtlist);
static void TestFindIf(srtlist_t *srtlist, int num);

/**************************Help functions declarations*************************/

static int PrintNum(void *data, void *param);
static srtlist_iter_t InsertArray(srtlist_t *srtlist, int *array, size_t length);
srtlist_iter_t InsertInt(srtlist_t *srtlist, int *to_insert);
void PrintList(srtlist_t *srtlist);
static int IsIntMatch(void *data, void *param);

/************************************Main**************************************/

int main()
{
	int array1[] = {3, 4, 1, 5, 2};
	int array2[] = {0, -3, 8, 1, -10, 3};
	
	srtlist_t *srtlist_1 = TestOne(array1);
	srtlist_t *srtlist_2 = TestTwo(array2);
	
	printf(YELLOW"\n-----Testing Merge - List 1 & 2-----\n\n"RESET);
	
	printf(MAGEN"--Before Merge--\n\n"RESET);
	printf("List 1: ");
	PrintList(srtlist_1); 
	
	printf("List 2: ");
	PrintList(srtlist_2); 
	
	printf(MAGEN"\n--Merge Result--\n\n"RESET);
	SrtListMerge(srtlist_1, srtlist_2);
	PrintList(srtlist_1); 
	
	TEST(RESET"\nTesting list 1 size: "CYAN"SrtListMerge", SrtListSize(srtlist_1), 8);
	TEST(RESET"Testing list 2 size: "CYAN"SrtListMerge", SrtListSize(srtlist_2), 0);
	
	SrtListDestroy(srtlist_1);
	SrtListDestroy(srtlist_2);
	
	printf(YELLOW"\n-----End of Test-----\n\n");
	
	return(0);
}

/**************************Test functions definitions**************************/

static srtlist_t *TestOne(int *array)
{
	srtlist_t *my_srtlist = NULL;
	srtlist_iter_t my_iter = NULL;

	printf(YELLOW"\n-----Testing Sorted List - Test 1-----\n\n"RESET);
	
	printf(MAGEN"--Creating a list & testing if it is empty--\n\n"RESET);
	my_srtlist = TestCreate(my_srtlist);
	if (NULL == my_srtlist)
	{
		return (NULL);
	}
	TestIsEmpty(my_srtlist, 1);
	
	my_iter = SrtListBegin(my_srtlist);
	TEST("SrtListBegin    ", my_iter, SrtListEnd(my_srtlist));
	
	printf(MAGEN"\n--Inserting numbers--\n"RESET);
	printf(CYAN"Insert: --> 3 --> 4 --> 1 --> 5 --> 2\n\n"RESET);
	my_iter = InsertArray(my_srtlist, array, 5);
	printf(MAGEN"\n--Printing List--\n"RESET);
	PrintList(my_srtlist);
	
	TEST("SrtListSize     ", SrtListSize(my_srtlist), 5);
	
	printf(MAGEN"\n--Getting data at last node-- \n"RESET);
	my_iter = SrtListPrev(SrtListEnd(my_srtlist));
	TestGetData(my_iter, 5);
	
	printf(MAGEN"\n--Removing node 2-- \n"RESET);
	TestRemove(my_srtlist, SrtListNext(SrtListBegin(my_srtlist)));
	PrintList(my_srtlist);
	
	printf(MAGEN"\n--Popping from Head-- \n"RESET);
	TestPop('f', my_srtlist, 1);
	PrintList(my_srtlist);
	
	printf(MAGEN"\n--Popping from Tail-- \n"RESET);
	TestPop('b', my_srtlist, 5);
	PrintList(my_srtlist);

	return (my_srtlist);	
}


static srtlist_t *TestTwo(int *array)
{
	srtlist_t *my_srtlist = NULL;
	srtlist_iter_t my_iter = NULL;

	printf(YELLOW"\n-----Testing Sorted List - Test 2-----\n\n"RESET);
	
	printf(MAGEN"--Creating a list & testing if it is empty--\n\n"RESET);
	my_srtlist = TestCreate(my_srtlist);
	if (NULL == my_srtlist)
	{
		return (NULL);
	}
	TestIsEmpty(my_srtlist, 1);
	my_iter = SrtListBegin(my_srtlist);
	
	printf(MAGEN"\n--Inserting numbers--\n"RESET);
	printf(CYAN"Insert: 0 --> -3 --> 8 --> 1 --> -10 --> 3\n\n"RESET);
	my_iter = InsertArray(my_srtlist, array, 6);
	printf(MAGEN"\n--Printing List--\n"RESET);
	PrintList(my_srtlist);
	
	printf(MAGEN"\n--Searching for number 3 (in list)--\n"RESET);
	TestFindIf(my_srtlist, 3);
	
	printf(MAGEN"\n--Searching for number 15 (not in list)--\n"RESET);
	TestFindIf(my_srtlist, 15);
	
	TEST("SrtListSize     ", SrtListSize(my_srtlist), 6);
	
	printf(MAGEN"\n--Searching for pointer for an array member in list--\n"RESET);
	TestFind(my_srtlist, array + 1);
	
	PrintList(my_srtlist);
	printf(MAGEN"\n--Printing list using ForEach--\n"RESET);
	TestForEach(SrtListBegin(my_srtlist), SrtListEnd(my_srtlist), my_srtlist);
	my_iter = my_iter;
	
	TestIsEmpty(my_srtlist, 0);
	
	return (my_srtlist);
}


static void TestFind(srtlist_t *srtlist, int *to_find)
{
	srtlist_iter_t res_iter = NULL;
	void *res_ptr = NULL;
	
	res_iter = SrtListFind(SrtListBegin(srtlist), SrtListEnd(srtlist), to_find);
						
	if (SrtListEnd(srtlist) != res_iter)
	{
		res_ptr = SrtListGetData(res_iter);
		TEST("SrtListFind     ", res_ptr, to_find);
	}
	else
	{
		printf("Item Not Found\n\n");
	}
}


static void TestFindIf(srtlist_t *srtlist, int num)
{
	srtlist_iter_t res_iter = NULL;
	void *res_ptr = NULL;
	
	res_iter = SrtListFindIf(SrtListBegin(srtlist), SrtListEnd(srtlist), 
	IsIntMatch, &num);
					
	if (SrtListEnd(srtlist) != res_iter)
	{
		res_ptr = SrtListGetData(res_iter);
		TEST("SrtListFindIf   ", *(int *)res_ptr, num);
	}
	else
	{
		printf("Item Not Found\n\n");
	}
}


static void TestGetData(srtlist_iter_t iterator, int expected)
{
	void *data = SrtListGetData(iterator);
	printf("Expected: %d\nData is:  %d\n", expected, *(int *)data);
	TEST("SrtListGetData  ", *(int *)data, expected);
}


static void TestPop(char direction, srtlist_t *srtlist, int expected)
{
	void *data = NULL;
	if ('b' == direction)
	{
		data = SrtListPopBack(srtlist);
		TEST("SrtListPopBack  ", *(int *)data, expected);	
	}
	if ('f' == direction)
	{
		data = SrtListPopFront(srtlist);
		TEST("SrtListPopFront ", *(int *)data, expected);	
	}
}


static void TestForEach(srtlist_iter_t from, srtlist_iter_t to, srtlist_t *srtlist)
{
	size_t num = 0;
	void *param = &num;
	SrtListForeach(from, to, PrintNum, param);
	TEST("\nSrtListForeach  ", SrtListSize(srtlist), *(size_t *)param);
	printf("\n");
} 


static srtlist_t *TestCreate(srtlist_t *srtlist)
{
	srtlist = SrtListCreate(IntCmpFunc);
	
	TEST_NOT("SrtListCreate   ", srtlist, NULL);
	
	return(srtlist);
}


static srtlist_iter_t TestRemove(srtlist_t *srtlist, srtlist_iter_t iterator)
{
	size_t size = 0;
	
	assert(NULL != srtlist);
	
	size = SrtListSize(srtlist);
	iterator = SrtListRemove(iterator);
	
	TEST("SrtListRemove   ", SrtListSize(srtlist), size - 1);
	
	return(iterator);
}


static void TestIsEmpty(srtlist_t *srtlist, int expected)
{
	int is_empty = SrtListIsEmpty(srtlist);
	
	TEST("SrtListIsEmpty  ", is_empty, expected);
	
	if (1 == is_empty)
	{
		printf(LIGHT"Sorted list is empty\n\n"RESET);
	}
	else
	{
		printf("Sorted list is not empty\n\n");		
	}
}


/**************************Help functions definitions**************************/

static int IntCmpFunc(void *data, void *param)
{	
	return (*(int *)data - *(int *)param);
}


static int PrintNum(void *data, void *param)
{
	size_t *tmp = (size_t *)param;
	++(*tmp);
	printf("%d  ", *(int *)data);
	return (0);
}


void PrintList(srtlist_t *srtlist)
{
    srtlist_iter_t iter = SrtListBegin(srtlist);
    void *data = NULL;
    size_t size = SrtListSize(srtlist);
    
    printf("Head --> ");
    
    while (0 < size)
    {
        data = SrtListGetData(iter);
        
        printf("%d --> ", *(int *)data);
        
        iter = SrtListNext(iter);
        size--;
    }
    
    printf("Tail\n");
}


static int IsIntMatch(void *data, void *param)
{
	return (*(int *)data == *(int *)param);
}


srtlist_iter_t InsertInt(srtlist_t *srtlist, int *to_insert)
{
	srtlist_iter_t iterator = SrtListInsert(srtlist, to_insert);
	return (iterator);
}


static srtlist_iter_t InsertArray(srtlist_t *srtlist, int *array, size_t length)
{
	size_t i = 0;
	srtlist_iter_t iterator = NULL;
	
	while (length > i)
	{
		iterator = SrtListInsert(srtlist, array + i);	
		TEST_NOT("SrtListInsert   ", iterator, NULL);
		++i;
	}
	return (iterator);
}

