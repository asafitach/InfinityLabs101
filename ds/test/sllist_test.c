#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/

#include "s_l_list.h"

#define RED "\033[1;5;31m"
#define GREEN "\033[1;5;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void TestList(); 

int main()
{
    system("clear");
    
    TestList(); 
    
    return 0; 
}


static int CmpFun(const void *data, void *param)
{
    return (!(data == param));
}


void TestList()
{
	void *res = 0;
	char *res_str = "hello";
	slist_t *list = NULL;
	slist_iter_t iter = NULL;
	
    printf(CYAN"\tTest List\n\n"WHITE); 
    
    list = SlistCreate();
    
    TEST("Test create list", (NULL != list) , 1); 
    
	TEST("Test is empty", SlistIsEmpty(list) , 1);
	    
    iter = SlistInsert(SlistBegin(list), (void*) 13);
    
	TEST("Test insert", SlistNext(iter) , SlistEnd(list));
     
	res = SlistGetData(iter);
    
	TEST("Test get data", *(size_t*)&res , 13);
    	
	TEST("Test is empty", SlistIsEmpty(list) , 0);
		
	iter = SlistInsert(SlistNext(iter), (void*) res_str);
    
    TEST("Test insert", SlistNext(iter) , SlistEnd(list));
    
    res = SlistGetData(iter);
    
	TEST("Test get data", (char*)res , res_str);
    
    TEST("Test count and foreach", SlistCount(list) , (size_t)2);

	iter = SlistInsert(SlistNext(iter), (void*) 'c');
    
    TEST("Test insert", SlistNext(iter) , SlistEnd(list));

	iter = SlistInsert(SlistNext(iter), (void*) '9');	
    
    TEST("Test insert", SlistNext(iter) , SlistEnd(list));
    
    res = (void*)13;
    iter = SlistFind(SlistBegin(list), SlistEnd(list), CmpFun, res);

    TEST("Test find", iter, SlistBegin(list));     
    
    SlistSetData(SlistNext(iter), (void*)13);

    TEST("Test set data", SlistGetData(SlistNext(iter)), SlistGetData(SlistBegin(list))); 
    
    iter = SlistRemove(SlistBegin(list));
    
    TEST("Test remove", iter, SlistBegin(list)); 
    
 /*   TEST("receive a pointer", (StackCreate(5)? 1:0) , 1); 
    
    TEST("receive a pointer", (StackCreate(5)? 1:0) , 1); 
    
    TEST("receive a pointer", (StackCreate(5)? 1:0) , 1); 
   */ 
   SlistDestroy(list);
    printf(CYAN"\tEnd Test List\n\n"WHITE); 
}
