#include <assert.h>/* assert */
#include <stdlib.h>/* malloc free */
#include <stdio.h>/* printf */
#include "stack.h"

struct stack
{
	size_t top;
	size_t capacity;
	void **array;
};


stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = (stack_t*) malloc(sizeof(stack_t));
	stack->array = (void**)malloc(capacity * sizeof(void*));
	if(NULL == stack)
	{
		printf("Allocation Failed");
		return (NULL);
	}
	if(NULL == stack->array)
	{
		free(stack);
		printf("Allocation Failed");
		return (NULL);
	}
	
	stack->top = 0;
	stack->capacity = capacity;
	
	return (stack);
}


void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	free(stack->array);
	free(stack);
}


void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(0 != stack->top);
	stack->top--;
}


void StackPush(stack_t *stack, void *item)
{
	assert(NULL != stack);
	assert(stack->top < stack->capacity);
	stack->array[stack->top] = item;
	stack->top++;
}


void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(0 < stack->top);
	return (stack->array[stack->top-1]);
}


size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	return (stack->top);
}


int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	return (0 == stack->top);
}


size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	return(stack->capacity);
}


