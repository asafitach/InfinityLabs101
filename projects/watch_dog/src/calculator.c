#include <string.h> /* strlen */
#include <math.h> /* pow */
#include <stdlib.h> /* strtod */
#include <assert.h> /* assert */
#include "utility.h"
#include "stack.h"
#include "calculator.h"

/************************** enums and typedefs *******************************/
typedef enum state
{
    WAITING_FOR_NUM,                /*next char/s shuld be 0-9 or -, ( */
    WAITING_FOR_OP,                 /*next char shuld be +, -, *, /, ^, =, ), NULL */
    NUM_OF_STATES,
    ERROR                          /*syntext/math/allocation error*/
} state_t;

typedef enum operators/*change by priotrity write switch case*/
{
    CLOSE_PAREN = 1,
    PLUS = 2,
    MINUS = 3,
    MULTI = 4,
    DIVISION = 5,
    POW = 6,
    OPEN_PAREN = 8,
    NUM_OF_OPERATORS = 7
}operators_t;

typedef state_t (*transition_t)(char **input, double *res, calculator_status_t *calc_state);
typedef void (*operation_t)(double num1, double num2);/*return state insert to double *ans */

/************************** globals *****************************************/

/* for every input (ASCII) and stae (WAIT FOR..) returns the right function */
transition_t g_trans_lut[ASCII][NUM_OF_STATES] = {0};
/* for every operators_t returns the function */
operation_t g_op_lut[NUM_OF_OPERATORS] = {0};
stack_t *g_num_stack = NULL;
stack_t *g_op_stack = NULL;

/************************** math functions ***********************************/

void Plus(double num1, double num2)
{
    num1 += num2;
    StackPush(g_num_stack, *(void**)&num1);
}

void Minus(double num1, double num2)
{
    num2 -= num1;
    StackPush(g_num_stack, *(void**)&num2);
}

void Multi(double num1, double num2)
{
    num2 *= num1;
    StackPush(g_num_stack, *(void**)&num2);
}

void Division(double num1, double num2)
{
    num2 /= num1;
    StackPush(g_num_stack, *(void**)&num2);
}

void Pow(double num1, double num2)
{
    num2 = pow(num2, num1);
    StackPush(g_num_stack, *(void**)&num2);
}

void OpenParen(double num1, double num2)
{
    StackPush(g_num_stack, *(void**)&num2);
    StackPush(g_num_stack, *(void**)&num1);
}

/*****************************************************************************/

/* for every operator insertion this function calculates any possible calc' from the stacks */
calculator_status_t SubTotal(operators_t operator)/*change name!!!!!*/
{
    operators_t prev_op = 0;
    operation_t function = NULL;
    void *data = NULL;
	void *data2 = NULL;

    if (1 == StackIsEmpty(g_op_stack) || operator == OPEN_PAREN)/* open paren is like opening new stack frame !! own transition!!*/
    {
        StackPush(g_op_stack, *(void **)&operator);
        return (CALC_SUCCESS);
    }
    
	data = StackPeek(g_op_stack);
    prev_op = *(operators_t *)&data;
    while (prev_op / 2 >= operator / 2 && OPEN_PAREN != prev_op) /**/
    {
        StackPop(g_op_stack);
        function = *g_op_lut[prev_op];
		data = StackPeek(g_num_stack);
        StackPop(g_num_stack);
		data2 = StackPeek(g_num_stack);
        StackPop(g_num_stack);
        if (DIVISION == prev_op && 0 == *(double *)&data2)/*!!*/
        {
            return (CALC_MATH_ERROR);
        }
        function(*(double* )&data, *(double *)&data2);
        if (1 == StackIsEmpty(g_op_stack))
        {
            break;
        }
		data = StackPeek(g_op_stack);
        prev_op = *(operators_t *)&data;
    }
    
    if (operator == CLOSE_PAREN && prev_op == OPEN_PAREN)/* deleting parenthesis */
    {
        StackPop(g_op_stack);
        return (CALC_SUCCESS);
    }


    StackPush(g_op_stack, *(void **)&operator);

    return (CALC_SUCCESS);
}


operators_t SwitchOperatorToEnum(char operator)/* return the enum which include the operator's priority */
{
    switch (operator)
    {
    case '+':
        return(PLUS);
    case '-':
        return(MINUS);    
    case '*':
        return(MULTI);
    case '/':
        return(DIVISION);
    case '^':
        return(POW);
    case '(':
        return(OPEN_PAREN);
    case ')':
        return(CLOSE_PAREN);
    }
    return (0);
}

/************************* transitions ***************************************/

state_t InsertNum(char **input, double *result, calculator_status_t *calc_state)/*change to handle !!*/
{
    char *ptr = NULL;
    double num =  strtod(*input, &ptr);

    assert(NULL != result);

    if (ptr == *input)
    {
        *result = 0;
        *calc_state = CALC_SYNTAX_ERROR;
        return (ERROR);
    }

    StackPush(g_num_stack, *(void **)&num);

    *input = ptr;
    return (WAITING_FOR_OP);
}

/*****************************************************************************/

state_t InsertOp(char **input, double *result, calculator_status_t *calc_state)/*can be dismissed*/
{
   char *exp = *input;

   assert(NULL != calc_state);
   assert(NULL != result);

    *calc_state = SubTotal(SwitchOperatorToEnum(**input));

    if (')' == **input)/*!!make transition*/
    {
        *input = exp + 1;
        return (WAITING_FOR_OP);
    }
    *input = exp + 1;

    return (WAITING_FOR_NUM);
}

/*****************************************************************************/

state_t ProceedNum(char **input, double *result, calculator_status_t *calc_state)
{
    char *next_char = *input;
    assert(NULL != calc_state);
    assert(NULL != result);
    *input = next_char + 1;
    return (WAITING_FOR_NUM);
}

state_t ProceedOp(char **input, double *result, calculator_status_t *calc_state)
{
    char *next_char = *input;
    assert(NULL != calc_state);
    assert(NULL != result);
    *input = next_char + 1;
    return (WAITING_FOR_OP);
}

state_t Error(char **input, double *result, calculator_status_t *calc_state)
{
    assert(NULL != input);
    *result = 0;
    *calc_state = CALC_SYNTAX_ERROR;
    return (ERROR);
}
/************************* init luts ******************************************/

void InitTransition(void)
{
    size_t index = 0;
    for (index = 0; index < ASCII; ++index)
    {
        g_trans_lut[index][WAITING_FOR_NUM] = Error;/*flip input state!!!*/
        g_trans_lut[index][WAITING_FOR_OP] = Error;
    }

    for (index = '0'; index <= '9'; ++index)
    {
        g_trans_lut[index][WAITING_FOR_NUM] = InsertNum;
    }

    for (index = ')'; index <= '+'; ++index)
    {
        g_trans_lut[index][WAITING_FOR_OP] = InsertOp;
    }

    g_trans_lut[0][WAITING_FOR_OP] = InsertOp;
    g_trans_lut['('][WAITING_FOR_NUM] = InsertOp;/*open brac trans!!!*/
    g_trans_lut[')'][WAITING_FOR_OP] = InsertOp;
    g_trans_lut['-'][WAITING_FOR_OP] = InsertOp;
    g_trans_lut['-'][WAITING_FOR_NUM] = InsertNum;
    g_trans_lut['+'][WAITING_FOR_OP] = InsertOp;
    g_trans_lut['+'][WAITING_FOR_NUM] = InsertNum;
    g_trans_lut['/'][WAITING_FOR_OP] = InsertOp;
    g_trans_lut['^'][WAITING_FOR_OP] = InsertOp;
    g_trans_lut[' '][WAITING_FOR_OP] = ProceedOp;
    g_trans_lut[' '][WAITING_FOR_NUM] = ProceedNum;
}

/*****************************************************************************/

void InitOperation(void)
{
    g_op_lut[PLUS] = Plus;/*!!!  + */
    g_op_lut[MINUS] = Minus;
    g_op_lut[MULTI] = Multi;
    g_op_lut[DIVISION] = Division;
    g_op_lut[POW] = Pow;
    g_op_lut[OPEN_PAREN] = OpenParen;
    g_op_lut[CLOSE_PAREN] = OpenParen;


}

/*********************** last calculation ************************************/

calculator_status_t ToatalSum(double *res)
{
    double num1 = 0;
    double num2 = 0;
    void *void_num1 = NULL;
    void *void_num2 = NULL;
    void *operator = NULL;
    operation_t function = NULL;

    if (1 == StackIsEmpty(g_op_stack))
    {
        void_num1 = StackPeek(g_num_stack);
        *res = *(double *)&void_num1;
        return (CALC_SUCCESS);
    }
    else if (StackSize(g_num_stack) != StackSize(g_op_stack) + 1)
    {
        *res = 0;
        return (CALC_SYNTAX_ERROR);
    }
    else
    {
        void_num2 = StackPeek(g_num_stack);
        StackPop(g_num_stack);
        void_num1 = StackPeek(g_num_stack);
        StackPop(g_num_stack);
        operator = StackPeek(g_op_stack);
        StackPop(g_op_stack);
    }

    while(1)
    {
        num1 = *(double *)&void_num1;
        num2 = *(double *)&void_num2;
        if (OPEN_PAREN == *(operators_t *)&operator || CLOSE_PAREN == *(operators_t *)&operator)
        {
            *res = 0;
            return (CALC_SYNTAX_ERROR);
        }
        else if (DIVISION == *(operators_t *)&operator && 0 == num2)
        {
            *res = 0;
            return (CALC_MATH_ERROR);
        }
        else if (POW == *(operators_t *)&operator && (num2 != (int)num2))
        {
            *res = 0;
            return (CALC_MATH_ERROR);
        }
        function = *g_op_lut[*(operators_t *)&operator];
        function(num2, num1);
        void_num2 = StackPeek(g_num_stack);
        StackPop(g_num_stack);
        if (1 == StackIsEmpty(g_num_stack))
        {
            break;
        }
        void_num1 = StackPeek(g_num_stack);
        StackPop(g_num_stack);
        operator = StackPeek(g_op_stack);
        StackPop(g_op_stack);
    }

    if (0 == StackIsEmpty(g_op_stack))
    {
        *res = 0;
        return (CALC_SYNTAX_ERROR);
    }

    *res = *(double *)&void_num2;
    return (CALC_SUCCESS);
}
/*****************************************************************************/

calculator_status_t Calculate(const char *expression, double *res)
{
    char *current_char = (char*)expression;
    state_t state = WAITING_FOR_NUM;
    calculator_status_t calc_state = CALC_SUCCESS;
    transition_t trans = NULL;

    InitTransition();
    InitOperation();

    g_num_stack = StackCreate(strlen(expression));
    g_op_stack = StackCreate(strlen(expression));

    if (NULL == g_op_stack || NULL == g_num_stack)/* beak into 2 !!! */
    {
        return (CALC_MEMORY_ALLOCATION_ERROR);
    }

    while (0 != *current_char && CALC_SUCCESS == calc_state)
    {
        trans = g_trans_lut[(size_t)*current_char][state];
        state = trans(&current_char, res, &calc_state);
    }

    if (state != WAITING_FOR_OP)
    {
        *res = 0;
        calc_state = CALC_SYNTAX_ERROR;
    }

    if (CALC_SUCCESS == calc_state)/*why there is string left*/
    {
        calc_state = ToatalSum(res);/*can be the handler to NULL */
    }
    

    StackDestroy(g_num_stack);
    StackDestroy(g_op_stack);

    return (calc_state);
}

/************************** E.O.F. *******************************************/