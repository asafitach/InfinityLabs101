#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include <string.h>
#include <assert.h>

#include "dllist.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void TestCreateIsemptyDestroy();
void TestInsertBeginEndRemove();
void TestPushBackFrontSizePopBackFront();
void TestNextPreSpliceIssameiter();
void TestForeach();
void TestFindMulti();


int main()
{
    system("clear");
    
    TestCreateIsemptyDestroy();
    TestInsertBeginEndRemove();
    TestPushBackFrontSizePopBackFront();
	TestNextPreSpliceIssameiter();
	TestForeach();
	TestFindMulti();

    return (0); 
}

/******************************************************************************/

void TestCreateIsemptyDestroy()
{
	dlist_t *list = NULL;
	int res = 0;
	
    printf(CYAN"\tTest \n\n"WHITE); 
    
    list = DlistCreate();
    TEST(" create ", (list != NULL) , 1); 
  
	res = DlistIsEmpty(list);
    TEST(" is empty ", res , 1); 
      
    printf(CYAN"\tEnd Test \n\n"WHITE); 

	DlistDestroy(list);
}

/******************************************************************************/

void TestInsertBeginEndRemove()
{
	dlist_t *list = NULL;
	dlist_iter_t iter = NULL;
	char *str = "hello!";
	
    printf(CYAN"\tTest \n\n"WHITE); 

	list = DlistCreate();
	
	iter = DlistInsert(DlistEnd(list), (void*)str);	
    
    TEST(" insert + get ", (DlistGetData(iter) == (void*)str) , 1); 
    
    TEST(" end + next + prev ", (DlistNext(iter) == DlistNext(DlistPrev(DlistEnd(list)))) , 1); 

	iter = DlistRemove(iter);    

    TEST(" remove ", (iter == DlistEnd(list)) , 1);     
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 

	DlistDestroy(list);
}

/******************************************************************************/

void TestPushBackFrontSizePopBackFront()
{
	dlist_t *list = NULL;
	char *str = "hello!";
	char *str2 = " world";
	size_t size = 0;
	list = DlistCreate();
	
    printf(CYAN"\tTest \n\n"WHITE); 
    
    DlistPushFront(list, (void*)str);
    DlistPushBack(list, (void*)str2);
    size = DlistSize(list);
    TEST(" push front + back +size ", size , 2); 
    
	    
    DlistPopFront(list);
    DlistPopBack(list);
    size = DlistSize(list);
    TEST(" pop front + back +size ", size , 0);    
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 

	DlistDestroy(list);
}

/******************************************************************************/
int IsEqual(void *data, void *param)
{
	int res = 0;
	char *ptr1 = (char *)data;
	char *ptr2 = (char *)param;
	res = strcmp(ptr1, ptr2);
	return (!res);
}

int PrintList(void *data, void *param)
{
	assert(NULL != param);
	printf("\n%s\n", *(char**)data);

	return(1);
}

int PrintList2(void *data, void *param)
{
	param = DlistGetData((dlist_iter_t)data);
	printf("\n%s\n", *(char**)param);

	return(1);
}

void TestFindMulti()
{
	dlist_t *list = NULL;
	dlist_t *list2 = NULL;
	dlist_iter_t iter = NULL;
	char *str = "hello!";
	char *str2 = " world";
	int count = 0;
	list = DlistCreate();
	list2 = DlistCreate();
	 
	 
    iter = DlistPushFront(list, (void*)str);
    iter = DlistPushFront(list, (void*)str);
	iter = DlistPushFront(list, (void*)str); 
    iter = DlistPushBack(list, (void*)str2);

    printf(CYAN"\tTest \n\n"WHITE); 
    
    iter = DlistFindOne(DlistBegin(list), DlistEnd(list), IsEqual, (void *)str2); 
	TEST(" find one ", (DlistEnd(list) == DlistNext(iter)) , 1); 
    
    count = DlistFindMulti(DlistBegin(list), DlistEnd(list), IsEqual, (void *)str, list2); 
    TEST(" find multi ", count , 3); 

	DlistForeach(DlistBegin(list2), DlistEnd(list2) ,PrintList2, str);	
	
	DlistPopBack(list);
	DlistDestroy(list2);
	list2 = NULL;
	
	list2 = DlistCreate();
    count = DlistFindMulti(DlistBegin(list), DlistEnd(list), IsEqual, (void *)str2, list2); 
    TEST(" find multi with no match ", count , 0); 
        
    printf(CYAN"\tEnd Test \n\n"WHITE); 
    
	DlistDestroy(list);
	DlistDestroy(list2);
}

/******************************************************************************/

void TestNextPreSpliceIssameiter()
{
	dlist_t *list = NULL;
	dlist_t *list2 = NULL;
	dlist_iter_t dest = NULL;
	dlist_iter_t to = NULL;
	dlist_iter_t from = NULL;
	char *str = "hello!";
	char *str2 = " world";
	int res = 0;
	list = DlistCreate();	
	list2 = DlistCreate();

    DlistPushFront(list, (void*)str);
    DlistPushFront(list, (void*)str2);	
    DlistPushFront(list2, (void*)str);
    DlistPushFront(list2, (void*)str2);	
	
    printf(CYAN"\tTest \n\n"WHITE); 
    
	res = DlistIsSameIter(DlistPrev(DlistNext(DlistBegin(list))), DlistBegin(list));
    TEST(" next + prev + is same ", res , 1); 
    
    dest = DlistBegin(list);
    from = DlistBegin(list2);
    to = DlistEnd(list2);
    
    dest = DlistSplice( dest, from, to);
    TEST(" splice + size ", DlistSize(list) , 4); 
    
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 

    DlistDestroy(list);
	DlistDestroy(list2);
}

/******************************************************************************/

	

void TestForeach()
{
	dlist_t *list = NULL;
	char *str = "hello!";
	char *str2 = " world";
	int res = 0;
	list = DlistCreate();	

    DlistPushFront(list, (void*)str);
    DlistPushFront(list, (void*)str2);	
    DlistPushFront(list, (void*)str);
    DlistPushFront(list, (void*)str2);	
    

    
	res = DlistForeach(DlistBegin(list), DlistEnd(list) ,PrintList, str);
    TEST(" print + foreach ", res , 1); 
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 
    
    DlistDestroy(list);
}

/******************************************************************************/



