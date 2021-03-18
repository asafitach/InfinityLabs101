#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>/*size_t*/

typedef struct {
	size_t len;
	char flex_array[1];
}user_buff_t;

typedef struct{
	size_t capacity;
	size_t cur_size;
	char arr[capacity];
}cbuff_t;
	


/*Description: The function creates new stack data structure.
@params: The function gets the capacity of the stuck.
@return: The function returns a pointer to the stack.
@errors: If capacity is above ___ the function returns a NULL pointer
*/
cbuff_t *CbuffCreate(const size_t capacity);

/*Description: The function destroys a stuck.
@params: The function gets a pointer to the stuck.
@return: no return value
@errors: Free error
*/
void CbuffDestroy(cbuff_t * cbuff);

/*Description: The function pops the first element from the stack.
@params: The function gets a pointer to the stack.
@return: NA
@errors: NA
*/
void StackPop(stack_t *stack);/*needed?*/

/*Description: The function push new element to the stack.
@params: pointer to the stack and a void pointer.
@return: NA
@errors: NA
*/
user_buff_t *CbuffWrite(cbuff_t *cbuff, user_buff_t buff);

/*Description: The function returns the value of the top most element without deleting that element.
@params: The function gets a pointer to the stuck.
@return: void pointer.
@errors: NA
*/
user_buff_t *CbuffRead(cbuff_t *cbuff, user_buff_t buff);

/*Description: The function returns the number of item in the stack.
@params: The function gets a pointer to the stack.
@return: The function returns the number of items in the stack.
@errors: NA
*/
size_t CbuffSize(cbuff_t *cbuff);

/*Description: The function returns the number of item in the stack.
@params: The function gets a pointer to the stack.
@return: The function returns the number of items in the stack.
@errors: NA
*/
size_t CbuffCountSize (cbuff_t *cbuff);

/*Description: The function tells if the stack is empty.
@params: The function gets a pointer to the stack.
@return: The function returns if the stack is empty or not.
@errors: NA
*/
int CbuffIsEmpty(cbuff_t *cbuff);

/*Description: The function returns the capacity of the stack.
@params: The function gets a pointer to the stack.
@return: The function returns the capacity of the stack.
@errors: NA
*/
size_t StackCapacity(stack_t *stack);

#endif /* __STACK_H__ */
