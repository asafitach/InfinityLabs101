#include <stdio.h> /*printf*/
#include <assert.h> /* assert */
#include <string.h> /* strcmp */
#include "srtlist.h"

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
            
int cmp_func(void *data, void *param);               
status_t TestString(); 
static srtlist_t *TestCreate(srtlist_t *srtlist);
static void TestIEmpty(srtlist_t *srtlist, int bol);
static void TestInsert(srtlist_t *srtlist, int data[], int size);
static void TestFind(srtlist_iter_t iterator1, srtlist_iter_t iterator2, int *data);
static void TestGetData(srtlist_iter_t iterator, int *data);
static void TestCount(srtlist_t *srtlist, size_t count);
static void TestRemove(srtlist_t *srtlist, int remove);
static int IntPrint(void *data, void *param);
static int IsEqual(void *data, void *param);
static void TestPop(srtlist_t *srtlist);
static void TestForEach(srtlist_t *srtlist);
static void TestMerge(srtlist_t *dest, srtlist_t *src);

int main()
{    
    printf(MAG"\tTest string:\n"WHIT);
	TEST(MAG"The test complete succesfuly", TestString(), 0); 
    
    return 0; 
}

status_t TestString()
{
	srtlist_t *dest = NULL;
	srtlist_t *src = NULL;	

	int arr[] = {3,100,1,9,2};
	int arr2[] = {4,5,1,6};
	int size = sizeof(arr)/sizeof(int);
	int size2 = sizeof(arr)/sizeof(int);	
			
	dest = TestCreate(dest);
	
	TestIEmpty(dest, 1);

	TestInsert(dest, arr, size);

	TestFind(SrtListBegin(dest), SrtListEnd(dest), (arr + 2));
	TestForEach(dest);
	TestCount(dest, 5);
	TestGetData(SrtListBegin(dest), arr);
	
	TestPop(dest);
	TestCount(dest, 3);
	src = TestCreate(src);
	TestInsert(src, arr2, size2);	
	TestMerge(dest, src);
	TestRemove(dest, 2);
	
	SrtListDestroy(dest);
	SrtListDestroy(src);
	
	return SUCCESS;

}

static srtlist_t *TestCreate(srtlist_t *srtlist)
{
	printf(MAG"Test create:\n"WHIT);		
	srtlist = SrtListCreate(cmp_func);
	TEST_NOT("The doubly list created", srtlist, NULL);
	
	return srtlist;
}
int cmp_func(void *data, void *param)
{
	return (*(int *)data - *(int*)param);	
}

static void TestIEmpty(srtlist_t *srtlist, int bol)
{	
	printf(MAG"Test is empty:\n"WHIT);
	if (1 == bol)
	{
		TEST("The srtlist is empty", SrtListIsEmpty(srtlist), bol);
	}
	else 
	TEST("The srtlist is not empty", SrtListIsEmpty(srtlist), bol);	
}

static void TestInsert(srtlist_t *srtlist, int data[], int size)
{
	int i = 0;	
	
	printf(MAG"Test insert:\n"WHIT);
	
	while(i < size)
	{
		printf ("%d ", *(int *)data + i);
		++i;
	} 
	
	printf ("\n"); 
	i = 0;
	while(i < size)
	{
		SrtListInsert(srtlist, data + i);
		++i;
	} 

}

static void TestFind(srtlist_iter_t iterator1, 
srtlist_iter_t iterator2, int *data)
{
	srtlist_iter_t iterator = NULL;
	
	iterator = SrtListFind(iterator1, iterator2, data);
	printf(MAG"Test find if there is value:\n"WHIT);
	
	printf("Is %d in the list?\n", *(int *)data);		
	TEST("The string found", SrtListGetData(iterator), data);
	
	iterator = SrtListFindIf(iterator1, iterator2, IsEqual, data);	
	printf(MAG"Test find the value:\n"WHIT);
	printf("Serching for %d, ", *(int *)data);	
	TEST("The value found", SrtListGetData(iterator), data);
}

static void TestGetData(srtlist_iter_t iterator, int *data)
{
	iterator = DlistNext(iterator);
	iterator = DlistNext(iterator);
	
	printf(MAG"value %d:\n"WHIT, *(int *)data);	
	TEST("The value found", SrtListGetData(iterator), data);
	iterator = DlistNext(iterator);
}

static void TestCount(srtlist_t *srtlist, size_t count)
{
	printf(MAG"Test Count string:\n"WHIT);
	printf("The srtlist have %lu ", count);	
	TEST("value", SrtListSize(srtlist), count);
}

static void TestRemove(srtlist_t *srtlist, int remove)
{
	srtlist_iter_t iterator = NULL;
	iterator = SrtListBegin(srtlist);

	printf(MAG"Test remove from list:\n"WHIT);
	printf("Test remove, next number in the list %d\n", remove);
	iterator = SrtListRemove(iterator);
	TEST("The srtlist removed the first value",*(int *)SrtListGetData(iterator), remove);

}

static void TestPop(srtlist_t *srtlist)
{
	assert(NULL != srtlist);
	
	printf(MAG"Test pop:\n"WHIT);
	TEST("Pop string in front 1", *(int *)SrtListPopFront(srtlist), 1);	
	TEST("Pop string in back 100", *(int *)SrtListPopBack(srtlist), 100);	
	
}

static void TestForEach(srtlist_t *srtlist)
{
	printf(MAG"Test foreach data:\n"WHIT);				
	SrtListForeach(SrtListBegin(srtlist), SrtListEnd(srtlist), IntPrint, (int *)2);
	printf("\n");
}

static void TestMerge(srtlist_t *dest, srtlist_t *src)
{
	printf(MAG"Test Merge data:\n"WHIT);
	printf(MAG"expected:\n123456\n"WHIT);
	SrtListMerge(dest, src);
	SrtListForeach(SrtListBegin(dest), SrtListEnd(dest), IntPrint, (int *)1);
	printf("\n");								

}
static int IntPrint(void *data, void *param)
{
	param = param;
	printf("%d", *(int *)data);
	
	return 0;
}

static int IsEqual(void *data, void *param)
{
	return *(int *)data == *(int *)param;
}

