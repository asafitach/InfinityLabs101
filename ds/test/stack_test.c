#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include "stack.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)

void TestStack();

int main()
{
	TestStack();
	
	return (0);
}


void TestStack()
{
    stack_t *stack = NULL;
    void *peek = NULL;
    int item_int = 12;
    char item_char = '~';
    float item_float = 3.14;
    char *item_string = "Hello world";
	typedef struct {
	int x;
	char c;
	double d;
	}test; 
	test item_struct;
	item_struct.x = 7;
	item_struct.c = 't';
	item_struct.d = 6.28;

    printf(CYAN"\tTest Stack\n\n"WHITE); 
    
    stack = StackCreate(5);
    
    TEST("StackCreate(5)", (stack ? 1:0) , 1); 
    
    TEST("StackCapacity(stack)", StackCapacity(stack) , 5);
    
    TEST("StackIsEmpty(stack)", StackIsEmpty(stack) , 1);
    
    StackPush(stack, *(void**)&item_int);
    peek = StackPeek(stack);
    
    TEST("StackPush(stack, 12); StackPeek(stack)", *(int*)&peek , item_int);
    
    StackPush(stack, *(void**)&item_char);
    peek = StackPeek(stack);
    
    TEST("StackPush(stack, '~'); StackPeek(stack)", *(char*)&peek , item_char);
    
    StackPush(stack, *(void**)&item_float);
    peek = StackPeek(stack);
    
    TEST("StackPush(stack, 3.14); StackPeek(stack)", *(float*)&peek , item_float);
    
    StackPush(stack, (void*)item_string);
    peek = StackPeek(stack);
    
    TEST("StackPush(stack, string); StackPeek(stack)", (char*)peek , item_string);
    
	StackPush(stack, 	((void*)&item_struct));
    peek = StackPeek(stack);
    
    TEST("StackPush(stack, struct); StackPeek(stack)", (test*)peek , &item_struct);

    StackPop(stack);
    peek = StackPeek(stack);
    
    TEST("StackPop(stack); StackPeek(stack)", (char*)peek , item_string);
    
    TEST("StackSize(stack)", StackSize(stack) , 4);
       
    TEST("StackIsEmpty(stack)", StackIsEmpty(stack) , 0); 
    
    StackDestroy(stack);
     
    printf(CYAN"\tEnd Test Stack\n\n"WHITE); 
}
