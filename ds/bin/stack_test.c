#include <stdio.h> /* printf */
#include <stdlib.h> /* system */
#include <string.h> /* strcpy */

#include "stack.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
 
typedef struct
{
	char *first_name;
	char *last_name;
	size_t age;
	
} person_t;    

void TestStackInt(); 
void TestStackFloat();
void TestStackStruct();

int main()
{
    system("clear"); 
    TestStackInt(); 
    TestStackFloat();
    TestStackStruct();
    
    return 0; 
}

void TestStackInt()
{
	stack_t *stack = NULL;
	void *val = NULL;
	void *res = NULL;
	
    printf(CYAN"\tTest Stack for int Values\n\n"WHITE);  
    
    stack =  StackCreate(5);
    
    TEST("StackCreate(5)", (stack ? 1:0) , 1);      
	TEST("StackEmpty(stack)", (StackIsEmpty(stack)? 1:0) , 1);
	TEST("StackCapacity(stack)", (StackCapacity(stack)) , 5);
	TEST("StackSize(stack)", (StackSize(stack)) , 0);
	
	val = (void*)4;
	StackPush(stack, (val));
	res = StackPeek(stack);
	TEST("StackPush(stack, 4)", *((int*)&res) , 4);
	
	val = (void*)11;
	StackPush(stack, (val));
	res = StackPeek(stack);
	TEST("StackPush(stack, 11)", *((int*)&res) , 11);
	
	res = StackPeek(stack);
	TEST("StackPeek(stack)", *((int*)&res) , 11);
	
	StackPop(stack);
	res = StackPeek(stack);
	TEST("StackPop(stack)", *((int*)&res) , 4);
	
	TEST("StackSize(stack)", (StackSize(stack)? 1:0) , 1);
	TEST("StackIsEmpty(stack)", (StackIsEmpty(stack)? 1:0) , 0);
	
	StackDestroy(stack);
	
    printf(CYAN"\t\tEnd Test\n\n"WHITE); 
}
void TestStackFloat()
{
	stack_t *stack = NULL;
	void *val = NULL;
	void *res = NULL;
	float f = 0.0;
	
    printf(CYAN"\tTest Stack for float Values\n\n"WHITE);  
    
    stack =  StackCreate(6);
    
    TEST("StackCreate(6)", (stack ? 1:0) , 1);      
	TEST("StackEmpty(stack)", (StackIsEmpty(stack)? 1:0) , 1);
	TEST("StackCapacity(stack)", (StackCapacity(stack)) , 6);
	TEST("StackSize(stack)", (StackSize(stack)) , 0);
	
	f = 5.5;
	val = *((void**)&f);
	StackPush(stack, (val));
	res = StackPeek(stack);
	TEST("StackPush(stack, 5.5)", *((float*)&res) , 5.5);
	
	f = 10.0;
	val = *((void**)&f);
	StackPush(stack, (val));
	res = StackPeek(stack);
	TEST("StackPush(stack, 10.0)", *((float*)&res) , 10.0);
	
	res = StackPeek(stack);
	TEST("StackPeek(stack)", *((float*)&res) , 10.0);
	
	StackPop(stack);
	res = StackPeek(stack);
	TEST("StackPop(stack)", *((float*)&res) , 5.5);
	
	TEST("StackSize(stack)", (StackSize(stack)? 1:0) , 1);
	TEST("StackIsEmpty(stack)", (StackIsEmpty(stack)? 1:0) , 0);
	
	StackDestroy(stack);
	
    printf(CYAN"\t\tEnd Test\n\n"WHITE); 
}

void TestStackStruct()
{
	stack_t *stack = NULL;
	void *val1 = NULL;
	void *val2 = NULL;
	void *res = NULL;
	
	person_t person1 = {"Eden", "Atar", 25};
	person_t person2 = {"AAAA", "BBBB", 32};
	val1 = &person1;
	val2 = &person2;
	
    printf(CYAN"\tTest Stack for int Values\n\n"WHITE);  
    
    stack =  StackCreate(2);
    
    TEST("StackCreate(5)", (stack ? 1:0) , 1);      
	TEST("StackEmpty(stack)", (StackIsEmpty(stack)? 1:0) , 1);
	TEST("StackCapacity(stack)", (StackCapacity(stack)) , 2);
	TEST("StackSize(stack)", (StackSize(stack)) , 0);
	
	
	StackPush(stack, (val1));
	res = StackPeek(stack);
	TEST("StackPush(stack, &person1)", (person_t*)res, &person1);
	
	StackPush(stack, (val2));
	res = StackPeek(stack);
	TEST("StackPush(stack, &person2)", (person_t*)res, &person2);
	
	res = StackPeek(stack);
	TEST("StackPeek(stack)", (person_t*)res, &person2);
	
	StackPop(stack);
	res = StackPeek(stack);
	TEST("StackPop(stack)", (person_t*)res, &person1);
	
	TEST("StackSize(stack)", (StackSize(stack)? 1:0) , 1);
	TEST("StackIsEmpty(stack)", (StackIsEmpty(stack)? 1:0) , 0);
	
	StackDestroy(stack);
	
    printf(CYAN"\t\tEnd Test\n\n"WHITE); 
}
