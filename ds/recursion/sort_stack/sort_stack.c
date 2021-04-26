#include "stack.h"


void StackPushBack(stack_t *stack, int *num)
{
    int *bigger = 0;

    if (1 == StackIsEmpty(stack))
    {
        StackPush(stack, (void *)num);
        return;
    }
    bigger = (int *)StackPeek(stack);
    if (*num > *bigger)
    {
        StackPush(stack, (void *)num);
        return;
    }
    StackPop(stack);
    StackPushBack(stack, num);

    StackPush(stack, bigger);
}

void StackSort(stack_t *stack)
{
    int *num = 0;
    if (1 != StackIsEmpty(stack))
    {
        num = (int *)StackPeek(stack);
        StackPop(stack);
        StackSort(stack);
        StackPushBack(stack, num);
    }
}



