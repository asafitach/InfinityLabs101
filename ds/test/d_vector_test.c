#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/

#include "d_vector.h"

#define RED "\033[1;5;31m"
#define GREEN "\033[1;5;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void TestDynamicVector(); 

int main()
{
    system("clear");
    
    TestDynamicVector(); 
    
    return 0; 
}

void TestDynamicVector()
{
    d_vector_t *vector;
    status_t stat = SUCCESS;
    size_t cap = 4;
    void *ptr = NULL;
    int int_item = 5;
    char char_item = 'j';
    float float_item = 3.14;
    char *str = "have a good day";
    typedef struct {
    int x;
    int y;
    } test;
    test struct_item;
    
    
    
    printf(CYAN"\tTest StackCreate\n\n"WHITE); 
    
   
    
    vector = VectorCreate(cap);
    TEST("create vector", (vector ? 1:0) , 1);
     
	stat = VectorPushBack(vector, *(void**)&int_item);
	TEST("push an int", ((stat == SUCCESS) ? 1:0) , 1); 
	
	stat = VectorPushBack(vector, *(void**)&char_item);
	TEST("push a char", ((stat == SUCCESS) ? 1:0) , 1); 

	stat = VectorPushBack(vector, *(void**)&float_item);
	TEST("push a float", ((stat == SUCCESS) ? 1:0) , 1); 

	stat = VectorPushBack(vector, (void*)str);
	TEST("push a string", ((stat == SUCCESS) ? 1:0) , 1); 

	cap = VectorGetCapacity(vector);
	TEST("capacity check", ((cap == 4) ? 1:0) , 1); 
	
	TEST("size check", ((4 == VectorGetSize(vector)) ? 1:0) , 1); 
	
	stat = VectorPushBack(vector, *((void**)(&struct_item)));
	TEST("push a struct", ((stat == SUCCESS) ? 1:0) , 1); 
	
	TEST("Expand check", ((VectorGetCapacity(vector) == 8) ? 1:0) , 1); 
    
    VectorPopBack(vector);
	TEST("pop back", ((VectorGetSize(vector) == 4) ? 1:0) , 1); 
	
	ptr = VectorGetElement(vector, 0);
	TEST("get element", ((*(int*)&ptr == int_item) ? 1:0) , 1); 
    
    VectorSetElement(vector, 1, *(void**)&int_item);
	ptr = VectorGetElement(vector, 1);
	TEST("set element", ((*(int*)&ptr == int_item) ? 1:0) , 1); 
    
	stat = VectorExpand(vector, 20);
	TEST("expand on demand", ((stat == SUCCESS) ? 1:0) , 1); 
	
	stat = VectorShrink(vector);
	TEST("shrink to minimal size", ((stat == SUCCESS) ? 1:0) , 1); 
    
    VectorDestroy(vector);
    
    printf(CYAN"\tEnd Test StackCreate\n\n"WHITE); 
}


