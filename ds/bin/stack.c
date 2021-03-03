#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "stack.h"

struct stack
{
	size_t top;
	size_t capacity;
	void **array;
};

stack_t *StackCreate(size_t capacity);
void StackDestroy(stack_t *stack);
void StackPop(stack_t *stack);
void StackPush(stack_t *stack, void *item);
void *StackPeek(const stack_t *stack);
size_t StackSize(const stack_t *stack);
int StackIsEmpty(const stack_t *stack);
size_t StackCapacity(const stack_t *stack);

stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = (stack_t *)malloc(1 * sizeof(stack_t));
	
	stack->capacity = capacity;
	stack->top = 0; /* index 0 */
	
	stack->array = (void**)malloc(capacity * sizeof(void*));
	if(NULL == stack->array)
	{
		return NULL;
	}
	
	return stack;
}

void StackPush(stack_t *stack, void *item)
{	
	assert(NULL != stack);
	
	stack->array[stack->top] = item;
	stack->top++;
}

void* StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(stack->top > 0);
	
	return stack->array[stack->top - 1];
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(stack->top > 0);
	
	stack->top--;
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	
	return stack->top;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->top == 0 ? 1 : 0);
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	
	return stack->capacity;
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	
	free(stack->array);
	free(stack);
}
