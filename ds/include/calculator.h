#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

typedef enum calculator_status
{
    CALC_SUCCESS,                   /*standard mode*/
    CALC_MATH_ERROR,                /*DIVISION by 0 or powering by non natural number*/
    CALC_MEMORY_ALLOCATION_ERROR,   /*while pushing to stack*/
    CALC_SYNTAX_ERROR               /*operator/num/parenthesis not in the right place*/
} calculator_status_t;

/*Description: The function calculates the inserted expression.
@params: The function gets a string (expression) and pointer to double which will contain the answer.
@return: the caculation status.
@errors: No additional errors.
*/
calculator_status_t Calculate(const char *expression, double *res);


#endif /* __CALCULATOR_H__ */
