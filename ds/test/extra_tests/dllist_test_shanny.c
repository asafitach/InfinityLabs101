#include <stdio.h> /*printf*/
#include <assert.h> /* assert */
#include <string.h> /* strcmp */
#include "dllist.h"

#define CYAN "\033[1;36m"
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
            
               
status_t TestString(); 
static int StrCmp(void *str1, void *str2);
static int StrPrint(void *data, void *param);
static dlist_t *TestCreate(dlist_t *dlist);
static void TestIEmpty(dlist_t *dlist, int bol);
static void TestSame(dlist_iter_t iterator1, dlist_iter_t iterator2);
static void TestInsert(dlist_iter_t iterator, void *data);
static void TestPushPop(dlist_t *dlist);
static void TestFind(dlist_iter_t iterator1, dlist_iter_t iterator2, void *data);
static void TestCount(dlist_t *dlist);
static void TestSplice(dlist_t *dlist);
static void TestRemove(dlist_t *dlist);
int main()
{    
    printf(MAG"\tTest string:\n"WHIT);
	TEST(MAG"The test complete succesfuly", TestString(), 0); 
    
    return 0; 
}

status_t TestString()
{
	dlist_t *dlist = NULL;
			
	dlist = TestCreate(dlist);
	
	TestIEmpty(dlist, 1);

	TestSame(DlistBegin(dlist), DlistEnd(dlist));
	
	TestInsert(DlistBegin(dlist), (void *)"ecstasy");
		
	TestPushPop(dlist);

	TestFind(DlistBegin(dlist), DlistEnd(dlist), (void *)"ecstasy");
		
	TestCount(dlist);
	
	printf(MAG"Test foreach data:\n"WHIT);				
	printf("Before splise:\n");
	DlistForeach(DlistBegin(dlist), DlistEnd(dlist) , StrPrint, "around");
	printf("\n");
	TestSplice(dlist);
	printf("\n");
	
	TestRemove(dlist);

	DlistDestroy(dlist);

	return SUCCESS;

}

static dlist_t *TestCreate(dlist_t *dlist)
{
	printf(MAG"Test create:\n"WHIT);		
	dlist = DlistCreate();
	TEST_NOT("The doubly list created", dlist, NULL);
	
	return dlist;
}

static void TestIEmpty(dlist_t *dlist, int bol)
{	
	printf(MAG"Test is empty:\n"WHIT);
	if (1 == bol)
	{
		TEST("The dlist is empty", DlistIsEmpty(dlist), bol);
	}
	else 
	TEST("The dlist is not empty", DlistIsEmpty(dlist), bol);	
}

static void TestSame(dlist_iter_t iterator1, dlist_iter_t iterator2)
{
	printf(MAG"Test the same iter:\n"WHIT);
	if (1 == (DlistIsSameIter(iterator1, iterator2)))
	{	
		TEST("They the same",DlistIsSameIter(iterator1, iterator2), 1);
	}
	else
	TEST("They not the same",DlistIsSameIter(iterator1, iterator2), 0);
		
}

static void TestInsert(dlist_iter_t iterator, void *data)
{	
	printf(MAG"Test insert:\n"WHIT);
	iterator = DlistInsert(iterator, data);
	TEST("The new string insert", DlistGetData(iterator), data);
	iterator = DlistInsert(iterator, (void *)"in");
	iterator = DlistInsert(iterator, (void *)"around");
}

static void TestPushPop(dlist_t *dlist)
{
	dlist_iter_t iterator = NULL;
	assert(NULL != dlist);
	
	printf(MAG"Test push front:\n"WHIT);
	iterator = DlistPushFront(dlist, (void *)"hello");
	TEST_NOT("hello value push front", iterator, NULL);	
	printf(MAG"Test push back:\n"WHIT);
	iterator = DlistPushBack(dlist, (void *)"by");
	TEST_NOT("by value push back", iterator, NULL);
	printf(MAG"Test pop back:\n"WHIT);
	TEST("Pop string in front hello", (char *)DlistPopFront(dlist), (void *)"hello");	
	TEST("Pop string in back by", (char *)DlistPopBack(dlist), (void *)"by");	
	
}

static void TestFind(dlist_iter_t iterator1, dlist_iter_t iterator2, void *data)
{
	dlist_iter_t iterator = NULL;
	
	iterator = DlistFindOne(iterator1, iterator2, StrCmp, data);
	printf(MAG"Test find string:\n"WHIT);
	TEST("The string found", DlistGetData(iterator), data);
}

static void TestCount(dlist_t *dlist)
{
	printf(MAG"Test Count string:\n"WHIT);
	TEST("The dlist have 3 value", DlistSize(dlist), 3);
}

static void TestSplice(dlist_t *dlist)
{
	dlist_iter_t iterator2 = NULL;
	dlist_t *dlist2 = NULL;	
		
	dlist2 = TestCreate(dlist2);
	iterator2 = DlistInsert(DlistBegin(dlist2), (void *)"now");
	iterator2 = DlistInsert(iterator2, (void *)"me");
	iterator2 = DlistInsert(iterator2, (void *)"stop");
	iterator2 = DlistInsert(iterator2, (void *)"dont");	
	iterator2 = DlistInsert(iterator2, (void *)"so,");	
	
	DlistSplice(DlistEnd(dlist), DlistBegin(dlist2),  DlistEnd(dlist2));
	printf("After splise dest list:\n");
	printf("Ecpected:\n");
	printf("around in ecstasy so, dont stop me now\n");
	DlistForeach(DlistBegin(dlist), DlistEnd(dlist) , StrPrint, "around");
	DlistDestroy(dlist2);
}

static void TestRemove(dlist_t *dlist)
{
	dlist_iter_t iterator = NULL;
	iterator = DlistBegin(dlist);
	printf(MAG"Test remove string:\n"WHIT);
	TEST("The dlist removed the first value",*(char **)DlistRemove(iterator), (void *)"in");
}
static int StrPrint(void *data, void *param)
{
	param = param;
	printf(YEL"%s "WHIT, *(char **)data);
		
	return 0;
}

static int StrCmp(void *str1, void *str2)
{
	if (0 == strcmp(str1, str2))
	{
		return 1;
	}
	
	return 0;
} 
