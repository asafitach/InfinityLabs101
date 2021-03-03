#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>/*size_t*/


typedef struct stack stack_t;

/*Description: The function creates new stack data structure.
@params: The function gets the capacity of the stuck.
@return: The function returns a pointer to the stack.
@errors: If capacity is above ___ the function returns a NULL pointer
*/
stack_t *StackCreate(size_t capacity);

/*Description: The function destroys a stuck.
@params: The function gets a pointer to the stuck.
@return: The fanction returns NULL pointer.
@errors: Free error
*/
void StackDestroy(stack_t *stack);

/*Description: The function pops the first element from the stack.
@params: The function gets a pointer to the stuck.
@return: The function returns a void pointer to the top of the stack.
@errors: 
*/
void StackPop(stack_t *stack);

/*Description: The function push new element to the stack.
@params: 
@return: 
@errors: 
 */

void StackPush(stack_t *stack, void *item); /* return value ? */

/*Description: The function 
@params: The function gets a pointer to the stuck.
@return: 
@errors: 
*/
void *StackPeek(const stack_t *stack);

/*Description: The function 
@params: The function gets a pointer to the stack.
@return: The function returns the number of items in the stack.
@errors: 
*/
size_t StackSize(const stack_t *stack);

/*Description: The function tells if the stack is empty.
@params: The function gets a pointer to the stack.
@return: The function returns if the stack is empty or not.
@errors: 
*/
int StackIsEmpty(const stack_t *stack);

/*Description: The function 
@params: The function gets a pointer to the stack.
@return: The function returns the capacity of the stack.
@errors: 
*/
size_t StackCapacity(const stack_t *stack);

#endif /* __STACK_H__ */
