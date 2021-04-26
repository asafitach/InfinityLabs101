#include "fibonacci.h"   /* printf */


/********************* Fibonacci *********************************************/

int Fibonacci(int element_index)
{
    int num1 = 0;
    int num2 = 1;

    while (element_index)
    {
        num2 += num1;
        num1 = num2 - num1;
        element_index--;
    }

    return (num2 +num1);
}

/********************* RecursFibonacci ***************************************/

int RecursiveFibonacci(int element_index)
{
    if (1 >= element_index)
    {
        return (element_index);
    }

    return(RecursiveFibonacci(element_index - 1) + RecursiveFibonacci(element_index - 2));
}

/********************* E.O.F. ************************************************/

