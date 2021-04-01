#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include <string.h>
#include <assert.h>

#include "srtlist.h"

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
	TestFindMulti();
	TestNextPreSpliceIssameiter();
	TestForeach();

    return (0); 
}

/******************************************************************************/

int IntCmp (void *data, void *param)
{
	return (*(int*)data - *(int *)param);
}

int StrCmp (void *data, void *param)
{
	return (strcmp((char *)data, (char *)param));
}

void TestCreateIsemptyDestroy()
{
	srtlist_t *list = NULL;
	
    printf(CYAN"\tTest \n\n"WHITE); 
    
    list = SrtListCreate(StrCmp);
    TEST(" create ", (list != NULL) , 1); 
  
    TEST(" is empty ", SrtListIsEmpty(list) , 1); 

	SrtListDestroy(list);
}

/******************************************************************************/

void TestInsertBeginEndRemove()
{
	srtlist_t *list = NULL;
	srtlist_iter_t iter = NULL;
	char *str = "hello!";

	list = SrtListCreate(StrCmp);
	
	iter = SrtListInsert(list, (void*)str);	
    
    TEST(" insert + get ", (SrtListGetData(iter) == (void*)str) , 1); 

    TEST(" is empty when it isn't' ", SrtListIsEmpty(list) , 0); 
    
    TEST(" end + next + prev ", (SrtListNext(iter) == SrtListNext(SrtListPrev(SrtListEnd(list)))) , 1); 

	iter = SrtListRemove(iter);    

    TEST(" remove ", (iter == SrtListEnd(list)) , 1);     

	SrtListDestroy(list);
}

/******************************************************************************/

void TestPushBackFrontSizePopBackFront()
{
	srtlist_t *list = NULL;
	char *str = "hello!";
	char *str2 = " world";
	list = SrtListCreate(StrCmp);
    
    SrtListInsert(list, (void*)str);
    SrtListInsert(list, (void*)str2);
    
    TEST(" insert + size ", SrtListSize(list) , 2); 
    	
	    
    SrtListPopFront(list);
    SrtListPopBack(list);

    TEST(" pop front + back + size ", SrtListSize(list) , 0);    

	SrtListDestroy(list);
}

/*************************tool functions***************************************/
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
	param = param;
	printf("\n%s\n", *(char**)&data);

	return(1);
}

int PrintList2(void *data, void *param)
{
	param = param;
	printf("\n%s\n", (char*)data);
	return(1);
}
/******************************************************************************/
int IsMatch(void *data, void *param)
{
	return (!StrCmp(data, param));
}

void TestFindMulti()
{
	srtlist_t *list = NULL;
	srtlist_t *list2 = NULL;
	srtlist_iter_t iter = NULL;
	char *str = "hello!";
	char *str2 = "world";
	list = SrtListCreate(StrCmp);
	list2 = SrtListCreate(StrCmp);
	 
	 
    iter = SrtListInsert(list, (void*)str);
    iter = SrtListInsert(list, (void*)str);
	iter = SrtListInsert(list, (void*)str); 
    iter = SrtListInsert(list, (void*)str2);
    
    iter = SrtListFind(SrtListBegin(list), SrtListEnd(list), (void *)str2); 
	TEST(" find ", (SrtListEnd(list) == SrtListNext(iter)) , 1); 

    iter = SrtListFindIf(SrtListBegin(list), SrtListEnd(list), IsMatch, (void *)str2); 
	TEST(" find if ", (SrtListEnd(list) == SrtListNext(iter)) , 1); 

	SrtListForeach(SrtListBegin(list2), SrtListEnd(list2) ,PrintList2, str);	
	  
	SrtListDestroy(list);
	SrtListDestroy(list2);
}

/******************************************************************************/

void TestNextPreSpliceIssameiter()
{
	srtlist_t *list = NULL;
	srtlist_t *list2 = NULL;
	char *str = "hello!";
	char *str2 = " world";
	list = SrtListCreate(StrCmp);	
	list2 = SrtListCreate(StrCmp);

    SrtListInsert(list, (void*)str);
    SrtListInsert(list, (void*)str2);	
    SrtListInsert(list2, (void*)str);
    SrtListInsert(list2, (void*)str2);	
	

   

    TEST(" next + prev ", (SrtListPrev(SrtListNext(SrtListBegin(list))) == SrtListBegin(list)) , 1); 
    
    SrtListMerge(list, list2);
    printf("%lu", SrtListSize(list2));
    TEST(" merge + size ", SrtListSize(list) , 4); 
    
    SrtListDestroy(list);
	SrtListDestroy(list2);
}

/******************************************************************************/
	

void TestForeach()
{
	srtlist_t *list = NULL;
	char *str = "hello!";
	char *str2 = " world";
	int res = 0;
	list = SrtListCreate(StrCmp);	

    SrtListInsert(list, (void*)str);
    SrtListInsert(list, (void*)str2);	
    SrtListInsert(list, (void*)str);
    SrtListInsert(list, (void*)str2);	
    
	res = SrtListForeach(SrtListBegin(list), SrtListEnd(list) ,PrintList, str);
    TEST(" print + foreach ", res , 1); 
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 
    
    SrtListDestroy(list);
}

/******************************************************************************/



