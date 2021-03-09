#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strcmp */

#include "s_l_list.h"

/*********************************Test Macros**********************************/

#define TEST(name, real, expected) \
		printf(CYAN"%s %s\n\n", name, real == expected ? \
		GREEN"SUCCESS"RESET : RED"FAIL"RESET)
		
#define TEST_NOT(name, real, expected) \
		printf(CYAN"%s %s\n\n", name, real != expected ? \
		GREEN"SUCCESS"RESET : RED"FAIL"RESET)
		
#define TEST_STR(name, real, expected) \
		printf(CYAN"%s %s\n\n", name, strcmp(real, expected) == 0 ? \
		GREEN"SUCCESS"RESET : RED"FAIL"RESET)

/******************************Color definitions*******************************/

#define RED "\033[1;91m"      /* print in red          */

#define GREEN "\033[1;92m"    /* print in green        */

#define YELLOW "\033[1;35m"   /* print in magenta      */

#define LYELLOW "\033[1;95m"  /* print in light magenta*/

#define CYAN "\033[1;36m"     /* print in cyan         */

#define LIGHT "\033[2;37m"    /* print in gray         */

#define RESET "\033[1;0m"     /* reset print color     */


/*********************Test and help functions declarations*********************/

static slist_t *TestCreate(slist_t *slist);
static void TestIsEmpty(slist_t *slist, int expected);
static void TestCount(slist_t *slist, size_t expected);
static slist_iter_t TestBegin(slist_t *slist);
static slist_iter_t TestInsertIntByGet(slist_iter_t iterator, int num);
static void TestSetIntByGet(slist_iter_t iterator, int num);
static slist_iter_t TestRemove(slist_t *slist, slist_iter_t iterator, int next_num);
static slist_iter_t TestFindInt(slist_t *list, int to_find);

static void TestSetStrByGet(slist_iter_t iterator, char *str);
/* static int StrCmpFunc(const void *data, void *param);
static int PrintStr(void *data, void *param);
static slist_iter_t TestFindStr(slist_t *slist, char *str); */

static void TestPrintIntForEach(slist_iter_t from, slist_iter_t to);
static int PrintNum(void *data, void *param);
static int IntCmpFunc(const void *data, void *param);

/*************************************Main*************************************/

int main()
{
	slist_t *my_list = NULL;
	slist_iter_t my_iter = NULL;
	
	printf(LYELLOW"\n-----Testing Linked List-----\n\n"RESET);
	
	printf(YELLOW"\n-Creating new Linked List, testing Count & IsEmpty-\n\n"RESET);
	
	my_list = TestCreate(my_list);
	
	TestCount(my_list, 0);
	
	TestIsEmpty(my_list, 1);
	
	printf(YELLOW"\n-Creating new beginning iterator-\n\n"RESET);
		
	my_iter = TestBegin(my_list);
	
	printf(YELLOW"\n-Inserting 3 integers - "RESET"10, 4, 2 "YELLOW"testing Count & IsEmpty-\n\n"RESET);
	
	my_iter = TestInsertIntByGet(my_iter, 10);
	
	TestIsEmpty(my_list, 0);	
	
	TestCount(my_list, 1);
	
	my_iter = TestInsertIntByGet(my_iter, 4);
	
	TestCount(my_list, 2);
	
	my_iter = TestInsertIntByGet(my_iter, 2);
	
	TestCount(my_list, 3);
	
	printf(YELLOW"\n-Setting node #2 to hold integer 134-\n\n"RESET);
	
	my_iter = SlistNext(my_iter);
	
	TestSetIntByGet(my_iter, 134);
	
	printf(YELLOW"\n-Using ForEach to print all elements-\n\n"RESET);
	
	TestPrintIntForEach(SlistBegin(my_list), SlistEnd(my_list));
	
	printf(YELLOW"\n-Searching for 10 (found in the last node)-\n\n"RESET);
	
	my_iter = TestFindInt(my_list, 10);
	
	printf(YELLOW"-Searching for 11 (not in list)-\n\n"RESET);
	
	my_iter = TestFindInt(my_list, 11);
	
	printf(YELLOW"\n-Setting node #2 to hold string \"Hello\"-\n\n"RESET);
	
	my_iter = SlistBegin(my_list);
	
	my_iter = SlistNext(my_iter);
	
	TestSetStrByGet(my_iter, "Hello");
	
	printf(YELLOW"\n-Removing 2 items from the list, starting at head-\n\n"RESET);
	
	my_iter = TestBegin(my_list);
	
	my_iter = TestRemove(my_list, my_iter, 134);
	
	my_iter = TestRemove(my_list, my_iter, 10);
	
	printf(YELLOW"\n-Removing the last item in the list & testing IsEmpty-\n\n"RESET);
	
	my_iter = SlistRemove(my_iter);
	
	TestIsEmpty(my_list, 1);
	
	SlistDestroy(my_list);
	
	printf(LYELLOW"\n-----End of Test-----\n\n"RESET);
	
	return (0);
}



/***********************Helper functions definition****************************/

static int IntCmpFunc(const void *data, void *param)
{
	int data_int = (*(int *)&data);
	int patam_int = (*(int *)&param);
	
	return (!(data_int == patam_int));
}
/* static int StrCmpFunc(const void *data, void *param)
{
	char *data_char = (char *)data;
	char *param_char = (char *)param;
	int result = strcmp(data_char, param_char);
	return (result);
} */

static int PrintNum(void *data, void *param)
{
	(void)param;
	printf("%d, ", *(int *)data);
	return (0);
}

/* static int PrintStr(void *data, void *param)
{
	(void)param;
	printf("%s, ", (char *)data);
	return (0);
} */

/************************Test functions definitions****************************/

static slist_t *TestCreate(slist_t *slist)
{
	slist = SlistCreate();
	TEST_NOT("SlistCreate", slist, NULL);
	return(slist);
}



static void TestIsEmpty(slist_t *slist, int expected)
{
	int is_empty = SlistIsEmpty(slist);
	
	TEST("SlistIsEmpty", is_empty, expected);
	
	if (1 == is_empty)
	{
		printf(LIGHT"Linked list is empty\n\n"RESET);
	}
	else
	{
		printf("Linked list is not empty\n\n");		
	}
}



static void TestCount(slist_t *slist, size_t expected)
{
	size_t count = SlistCount(slist);
	assert(NULL != slist);	
	
	TEST("SlistCount", count, expected);
}



static slist_iter_t TestBegin(slist_t *slist)
{
	slist_iter_t my_iter = NULL;
	assert(NULL != slist);
	
	my_iter = SlistBegin(slist);
	TEST_NOT("SlistBegin", my_iter, NULL);
			
	return(my_iter);
}



static slist_iter_t TestInsertIntByGet(slist_iter_t iterator, int num)
{
	void *num_ptr = *(void **)&num;
	iterator = SlistInsert(iterator, num_ptr);
	
	num_ptr = SlistGetData(iterator);

	TEST("SlistInsert(test by SlistGet)", *(int *)&num_ptr, num);
	
	return(iterator);	
}



static void TestSetIntByGet(slist_iter_t iterator, int num)
{
	void *num_ptr = *(void **)&num;
	SlistSetData(iterator, num_ptr);
	
	num_ptr = SlistGetData(iterator);

	TEST("SlistSetData", *(int *)&num_ptr, num);	
}



static void TestSetStrByGet(slist_iter_t iterator, char *str)
{
	void *str_ptr = (void *)str;
	SlistSetData(iterator, str_ptr);
	
	str_ptr = SlistGetData(iterator);
	
	printf("%s\n", (char *)str_ptr);
}



static slist_iter_t TestRemove(slist_t *slist, slist_iter_t iterator, int next_num)
{
	/* void *num_ptr = NULL; */
	size_t count = 0;
	
	assert(NULL != slist);
	
	count = SlistCount(slist) - 1;
	iterator = SlistRemove(iterator);
	/* num_ptr = SlistGetData(iterator); */
	next_num = next_num;

	/* TEST("SlistRemove(test by SlistGet)", *(int *)&num_ptr, next_num); */
	TEST("SlistRemove", SlistCount(slist), count);
	
	return(iterator);
}





static void TestPrintIntForEach(slist_iter_t from, slist_iter_t to)
{
	void *param = NULL;
	SlistForeach(from, to, PrintNum, param);
	printf("\n");
} 


static slist_iter_t TestFindInt(slist_t *slist, int num)
{
	slist_iter_t res_iter = NULL;
	void *num_ptr = *(void **)&num;
	void *res_ptr = NULL;
	
	assert(NULL != slist);
	
	res_iter = SlistFind(SlistBegin(slist), SlistEnd(slist), 
						IntCmpFunc, num_ptr);
	if (SlistEnd(slist) != res_iter)
	{
		res_ptr = SlistGetData(res_iter);
		TEST("SlistFind",*(int *)&res_ptr ,num);
	}
	else
	{
		printf("Item Not Found\n");
	}
	
	return(res_iter);
} 


/* static slist_iter_t TestFindStr(slist_t *slist, char *str)
{
	slist_iter_t res_iter = NULL;
	void *str_ptr = (void *)str;
	void *res_ptr = NULL;
	
	assert(NULL != slist);
	
	res_iter = SlistFind(SlistBegin(slist), SlistEnd(slist), 
						StrCmpFunc, str_ptr);
	if (SlistEnd(slist) != res_iter)
	{
		res_ptr = SlistGetData(res_iter);
		TEST_STR("SlistFind",(char *)res_ptr ,str);
	}
	else
	{
		printf("Item Not Found\n");
	} 
	
	return(res_iter); 
}  */


