#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strcmp */

#include "dllist.h"

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

#define RED "\033[5;91m"      /* print in red          */
#define GREEN "\033[1;92m"    /* print in green        */
#define MAGEN "\033[1;95m"    /* print in magenta      */
#define YELLOW "\033[1;93m"   /* print in light yellow */
#define BLUE "\033[1;36m"     /* print in blue         */
#define CYAN "\033[1;96m"     /* print in cyan         */
#define LIGHT "\033[2;37m"    /* print in gray         */
#define RESET "\033[1;0m"     /* reset print color     */


/*********************Test and help functions declarations*********************/

static int TestDlist(void);
static dlist_t *TestOne(void);
static dlist_t *TestTwo(void);

static dlist_t *TestCreate(dlist_t *dlist);
static void TestIsEmpty(dlist_t *dlist, int expected);
static dlist_iter_t TestBegin(dlist_t *dlist);
static dlist_iter_t TestInsert(dlist_iter_t iterator, int num);
static dlist_iter_t TestRemove(dlist_t *dlist, dlist_iter_t iterator);
static void TestForEach(dlist_iter_t from, dlist_iter_t to);
static void TestSplice(dlist_t *dlist_1, dlist_t *dlist_2);
static int TestFindMulti(dlist_t *dlist, int num, int expected);
static void TestFindOne(dlist_t *dlist, int num);
static dlist_iter_t TestPushPop(dlist_t *dlist);


/**************************Help functions declarations*************************/

static int PrintNum(void *data, void *param);
static int IntCmpFunc(void *data, void *param);
static dlist_iter_t PushInLoop(char *direction, dlist_t *dlist, size_t num_of_elements);

/*************************************Main*************************************/

int main()
{
	TestDlist();
	return (0);
}

/************************Test functions definition*****************************/

int TestDlist(void)
{
	dlist_t *dlist_2 = NULL;
	dlist_t *dlist_1 = TestOne();
	if (NULL == dlist_1)
	{
		return (1);
	}
	
	dlist_2 = TestTwo();
	if (NULL == dlist_2)
	{
		return (1);
	}
	
	TestSplice(dlist_1, dlist_2);
	
	DlistDestroy(dlist_1);
	DlistDestroy(dlist_2);
	
	printf(YELLOW"\n-----End of Test-----\n\n");
	
	return(0);
}


static dlist_t *TestOne(void)
{
	dlist_t *my_dlist = NULL;
	dlist_iter_t my_iter = NULL;
	dlist_iter_t my_iter2 = NULL;
	
	printf(YELLOW"\n-----Testing Doubly Linked List - Test 1-----\n\n"RESET);
	
	printf(MAGEN"--Creating a list & testing if it is empty--\n\n"RESET);
	
	my_dlist = TestCreate(my_dlist);
	if (NULL == my_dlist)
	{
		return(NULL);
	}
	
	TestIsEmpty(my_dlist, 1);
	
	printf(MAGEN"--Creating an iterator to the beginning--\n\n"RESET);
	
	my_iter = TestBegin(my_dlist);
	
	printf(MAGEN"--Inserting 10--\n\n"RESET);
	
	my_iter2 = TestInsert(my_iter, 10);
	
	TestIsEmpty(my_dlist, 0);
	
	printf(MAGEN"--Testing if list size == 1--\n\n"RESET);
	
	TEST("DlistSize          ", DlistSize(my_dlist), 1);
	
	printf(MAGEN"--Testing DlistPrev, Next, and IsSameIter--\n\n"RESET);
	
	my_iter = DlistPrev(my_iter);
	
	TEST("DlistIsSameIter    ", DlistIsSameIter(my_iter, my_iter2), 1);
	
	TEST("DlistPrev          ", my_iter, my_iter2);

	my_iter = DlistNext(my_iter);
	
	TEST("DlistNext          ", my_iter, DlistEnd(my_dlist));	
	
	printf(MAGEN"--Removing 10 from the list--\n\n"RESET);
	
	my_iter2 = TestRemove(my_dlist, my_iter2);
	
	printf(MAGEN"--Testing if list size == 0--\n\n"RESET);
	
	TEST("DlistSize          ", DlistSize(my_dlist), 0);
		
	my_iter = TestPushPop(my_dlist);
	if (DlistEnd(my_dlist) == my_iter)
	{
		return (NULL);
	}
	
	my_iter = TestBegin(my_dlist);

	printf(MAGEN"--Inserting integers 0, 1 to the list (for splice test)--\n\n"RESET);
	
	my_iter = TestInsert(my_iter, 1);
	
	my_iter = TestInsert(my_iter, 0);
	
	return (my_dlist);
}


static dlist_t *TestTwo(void)
{
	dlist_t *my_dlist = NULL;
	dlist_iter_t my_iter = NULL;
	int hits = 0;
	
	printf(YELLOW"\n-----Testing Doubly Linked List - Test 2-----\n\n"RESET);
	
	printf(MAGEN"--Creating a list--\n\n"RESET);
	
	my_dlist = TestCreate(my_dlist);
	if (NULL == my_dlist)
	{
		return(NULL);
	}
	
	printf(MAGEN"--Pushing numbers 1-5 to the front of the list--\n\n"RESET);
	
	my_iter = PushInLoop("front", my_dlist, 5);
	if (DlistEnd(my_dlist) == my_iter)
	{
		return (NULL);
	}
	
	printf(MAGEN"--Pushing numbers 1-5 to the back of the list--\n\n"RESET);
	
	my_iter = PushInLoop("back", my_dlist, 5); 
	if (DlistEnd(my_dlist) == my_iter)
	{
		return (NULL);
	}
	
	printf(MAGEN"--Testing if list size == 10--\n\n"RESET);
	
	TEST("DlistSize          ", DlistSize(my_dlist), 10);
	
	printf(MAGEN"--Searching for the number 1 (in list twice)--\n\n"RESET);
	
	TestFindOne(my_dlist, 1);
	
	printf(MAGEN"--Searching for the number 6 (not in list)--\n\n"RESET);
	
	TestFindOne(my_dlist, 6);
	
	printf(MAGEN"--Searching for multiple nodes containing the number 1--\n\n"RESET);	
		
	hits = TestFindMulti(my_dlist, 1, 2);
	if (-1 == hits)
	{
		return (NULL);
	}
	
	return (my_dlist); 
	
}


static dlist_t *TestCreate(dlist_t *dlist)
{
	dlist = DlistCreate();
	
	TEST_NOT("DlistCreate        ", dlist, NULL);
	
	return(dlist);
}

static void TestIsEmpty(dlist_t *dlist, int expected)
{
	int is_empty = DlistIsEmpty(dlist);
	
	TEST("DlistIsEmpty       ", is_empty, expected);
	
	if (1 == is_empty)
	{
		printf(LIGHT"Doubly Linked list is empty\n\n"RESET);
	}
	else
	{
		printf("Doubly Linked list is not empty\n\n");		
	}
}


static dlist_iter_t TestInsert(dlist_iter_t iterator, int num)
{
	void *num_ptr = *(void **)&num;
	iterator = DlistInsert(iterator, num_ptr);
	
	num_ptr = DlistGetData(iterator);

	TEST("DlistInsert->Get   ", *(int *)&num_ptr, num);
	
	return(iterator);	
}


static dlist_iter_t TestRemove(dlist_t *dlist, dlist_iter_t iterator)
{
	size_t size = 0;
	
	assert(NULL != dlist);
	
	size = DlistSize(dlist);
	iterator = DlistRemove(iterator);
	
	TEST("DlistRemove        ", DlistSize(dlist), size - 1);
	
	return(iterator);
}


static dlist_iter_t TestBegin(dlist_t *dlist)
{
	dlist_iter_t my_iter = DlistBegin(dlist);	
	TEST_NOT("SlistBegin         ", my_iter, NULL);
			
	return(my_iter);
}


static void TestForEach(dlist_iter_t from, dlist_iter_t to)
{
	void *param = NULL;
	DlistForeach(from, to, PrintNum, param);
	printf("\n");
} 


static dlist_iter_t TestPushPop(dlist_t *dlist)
{
	int num = 0;
	void *num_ptr = NULL;
	
	dlist_iter_t my_iter = DlistBegin(dlist);
	my_iter = DlistPushBack(dlist, *(void **)&num);
	if (DlistEnd(dlist) == my_iter)
	{
		return (my_iter);
	}
	
	printf(MAGEN"\n--Pushing Back 0, Pushing Front 1 & Testing with Pop--\n\n");
	
	num = 1;
	my_iter = DlistPushFront(dlist, *(void **)&num);
	if (DlistEnd(dlist) == my_iter)
	{
		return (my_iter);
	}
	
	num_ptr = DlistPopBack(dlist);
	TEST("DlistPush->PopBack ", *(int *)&num_ptr, 0);
	
	num_ptr = DlistPopFront(dlist);
	TEST("DlistPush->PopFront", *(int *)&num_ptr, 1);
	
	TestIsEmpty(dlist, 1);
	
	return(my_iter);	
}


static int TestFindMulti(dlist_t *dlist, int num, int expected)
{
	void *num_ptr = *(void **)&num;
	int hits = 0;
	void *hit_iter = NULL;
	dlist_t *hit_list = DlistCreate();
	if (NULL == hit_list)
	{
		return (-1);
	}
	
	hits = DlistFindMulti(DlistBegin(dlist), DlistEnd(dlist), IntCmpFunc, num_ptr, hit_list);
	if (-1 == hits)
	{
		return (hits);
	}
	
	printf("testing if hits == 2:                             ");
	TEST("DlistFindMulti", hits, expected);
	
	printf("testing if hit list size == number of hits:       ");
	TEST("DlistFindMulti", hits, (int)DlistSize(hit_list));
	
	hit_iter = DlistGetData(DlistBegin(hit_list));
	num_ptr = DlistGetData(*(dlist_iter_t *)&hit_iter);
	
	printf("testing if hits are stored correctly in hit list: ");
	TEST("DlistFindMulti", num, *(int *)&num_ptr);
	
	/* add more elaborate testing for the hit list */
	
	DlistDestroy(hit_list);
	
	return(hits);
}


static void TestFindOne(dlist_t *dlist, int num)
{
	dlist_iter_t res_iter = NULL;
	void *num_ptr = *(void **)&num;
	void *res_ptr = NULL;
	
	res_iter = DlistFindOne(DlistBegin(dlist), DlistEnd(dlist), 
						IntCmpFunc, num_ptr);
						
	if (DlistEnd(dlist) != res_iter)
	{
		res_ptr = DlistGetData(res_iter);
		TEST("DlistFind          ",*(int *)&res_ptr ,num);
	}
	else
	{
		printf("Item Not Found\n\n");
	}
}


static void TestSplice(dlist_t *dlist_1, dlist_t *dlist_2)
{
	dlist_iter_t dest_iter = DlistNext(DlistBegin(dlist_1));
	dlist_iter_t from_iter = DlistNext(DlistBegin(dlist_2));
	dlist_iter_t to_iter = DlistEnd(dlist_2);
	
	printf(YELLOW"\n-----Testing DlistSplice-----\n\n");
	printf(MAGEN"--List 1 contains--\n\n"RESET);
	
	TestForEach(DlistBegin(dlist_1), DlistEnd(dlist_1));
	
	printf(MAGEN"\n--List 2 contains--\n\n"RESET);

	TestForEach(DlistBegin(dlist_2), DlistEnd(dlist_2));
	
	printf(MAGEN"\n--Splicing as follows:--\n\n"RESET);
	
	printf("0 dest-> 1 \n5 from-> 4  3  2  1  1  2  3  4  5 ->to\n");
	
	dest_iter = DlistSplice(dest_iter, from_iter, to_iter);
	

	printf(MAGEN"\n--Result:--\n\n"RESET"");
	
	printf(CYAN"Expected: \n");
	printf("0  4  3  2  1  1  2  3  4  5  1\n"RESET);
	
	TestForEach(DlistBegin(dlist_1), DlistEnd(dlist_1));

	
	TEST(RESET"\nTesting size of List1: "CYAN"DlistSplice", DlistSize(dlist_1), 11);
	TEST(RESET"Testing size of List2: "CYAN"DlistSplice", DlistSize(dlist_2), 1);
}


/************************Help functions definition*****************************/

static int PrintNum(void *data, void *param)
{
	(void)param;
	printf("%d  ", *(int *)data);
	return (0);
}


static int IntCmpFunc(void *data, void *param)
{
	int data_int = (*(int *)&data);
	int patam_int = (*(int *)&param);
	
	return (data_int == patam_int);
}


static dlist_iter_t PushInLoop(char *direction, dlist_t *dlist, size_t num_of_elements)
{
	size_t num = 1;
	void *num_ptr = NULL;
	dlist_iter_t iterator = NULL;
	
	if ('f' == *direction)
	{
		while (num <= num_of_elements)
		{
			num_ptr = *(void **)&num;
			iterator = DlistPushFront(dlist, num_ptr);
			if (DlistEnd(dlist) == iterator)
			{
				return (iterator);
			}
			++num;
		}	
		num_ptr = DlistGetData(DlistBegin(dlist));
		TEST("DlistPushFront     ", *(size_t *)&num_ptr, num_of_elements);
	}
	
	if ('b' == *direction)
	{
		while (num <= num_of_elements)
		{
			num_ptr = *(void **)&num;
			iterator = DlistPushBack(dlist, num_ptr);
			if (DlistEnd(dlist) == iterator)
			{
				return (iterator);
			}
			++num;
		}
		num_ptr = DlistGetData(DlistPrev(DlistEnd(dlist)));
		TEST("DlistPushBack      ", *(size_t *)&num_ptr, num_of_elements);
	}
	
	return (iterator);
}

