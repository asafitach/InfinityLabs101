#include <stdio.h> /* printf */
#include <stdlib.h> /* system */
#include <math.h> 	/* pow */



#define RED "\033[1;91m"           /* print in red          */
#define GREEN "\033[1;38;5;47m"    /* print in green        */
#define MAGEN "\033[0;38;5;183m"   /* print in magenta      */
#define YELLOW "\033[1;38;5;220m"  /* print in light yellow */
#define CYAN "\033[0;96m"          /* print in cyan         */
#define LIGHT "\033[2;37m"         /* print in gray         */
#define PURPLE "\033[1;4;38;5;224m"/* print in purple       */
#define RESET "\033[1;0m"          /* reset print color     */

/*****************************************************************************/

#define TEST(name, actual, expected)\
    				printf("%s: %s\n\n", name, actual == expected ?\
     				GREEN"Pass"RESET : RED"Fail"RESET)

#define NOT_TEST(name, actual, expected)\
    				printf("%s: %s\n\n", name, actual != expected ?\
     				GREEN"Pass"RESET : RED"Fail"RESET)
     				
/*****************************************************************************/
						/* Function Declaration */

typedef enum calculator_status
{
    CALC_SUCCESS,                   /*standard mode*/
    CALC_MATH_ERROR,                /*DIVISION by 0 or powering by non natural number*/
    CALC_MEMORY_ALLOCATION_ERROR,   /*while pushing to stack*/
    CALC_SYNTAX_ERROR               /*operator/num/parenthesis not in the right place*/
} calculator_status_t;

static void PrintStatus(char *expression, calculator_status_t status);
calculator_status_t Calculate(const char *expression, double *res);
/*****************************************************************************/
int main()
{
	double res = 0;
	calculator_status_t status = 0;
	char *expression = "2*(2*((1+2)/3))^2";
	printf("-----------------------------------------------");
	status = Calculate(expression, &res);
	PrintStatus(expression, status);
	printf("calculator result (8): %f\n\n", res);
	TEST("status", status, CALC_SUCCESS);
	TEST("result", res, 8);

	printf("-----------------------------------------------");
	expression = "3+(1)";
	status = Calculate(expression, &res);
	PrintStatus(expression, status);
	printf("calculator result (4): %f\n\n", res);
	TEST("status", status, CALC_SUCCESS);
	TEST("result", res, 4);

	printf("-----------------------------------------------");
	expression = "7+8";
	status = Calculate(expression, &res);
	PrintStatus(expression, status);
	printf("calculator result (15): %f\n\n", res);
	TEST("status", status, CALC_SUCCESS);
	TEST("result", res, 15);

	printf("-----------------------------------------------");
	expression = "8+8 * 3+-2^5";
	status = Calculate(expression, &res);
	PrintStatus(expression, status);
	printf("calculator result (0): %f\n\n", res);
	TEST("status", status, CALC_SUCCESS);
	TEST("result", res, 0);

	/*printf("-----------------------------------------------");
	expression = "8+8 * 3-2^";
	status = Calculate(expression, &res);
	PrintStatus(expression, status);
	printf("calculator result (0): %f\n\n", res);
	TEST("status", status, CALC_SYNTAX_ERROR);
	TEST("result", res, 0);
*/
	printf("-----------------------------------------------");
	expression = "2/0";
	status = Calculate(expression, &res);
	PrintStatus(expression, status);
	printf("calculator result (0): %f\n\n", res);
	TEST("status", status, CALC_MATH_ERROR);
	TEST("result", res, 0);

	printf("-----------------------------------------------");
	expression = "8++8 * ((3-2) * 5)";
	status = Calculate(expression, &res);
	PrintStatus(expression, status);
	printf("calculator result (48): %f\n\n", res);
	TEST("status", status, CALC_SUCCESS);
	TEST("result", res, 48);

	printf("-----------------------------------------------");
	expression = "3-2) * 5";
	status = Calculate(expression, &res);
	PrintStatus(expression, status);
	printf("calculator result (0): %f\n\n", res);
	TEST("status", status, CALC_SYNTAX_ERROR);
	TEST("result", res, 0);

	printf("-----------------------------------------------");
	expression = "(4*5";
	status = Calculate(expression, &res);
	PrintStatus(expression, status);
	printf("calculator result (0): %f\n\n", res);
	TEST("status", status, CALC_SYNTAX_ERROR);
	TEST("result", res, 0);

	printf("-----------------------------------------------");
	expression = "2^3 / 5";
	status = Calculate(expression, &res);
	PrintStatus(expression, status);
	printf("calculator result (8/5): %f\n\n", res);
	TEST("status", status, CALC_SUCCESS);
	TEST("result", res, 8.0/5);

	printf("-----------------------------------------------");
	expression = "";
	status = Calculate(expression, &res);
	PrintStatus(expression, status);
	printf("calculator result for empty string (0): %f\n\n", res);
	TEST("status", status, CALC_SYNTAX_ERROR);
	TEST("result", res, 0);

    return 0; 
}

static void PrintStatus(char *expression, calculator_status_t status)
{
    printf(CYAN"\n\t%s\n", expression);
	if (status == CALC_SUCCESS)
	{
		printf(MAGEN"CALC_SUCCESS\n"RESET);
	}
	else if (status == CALC_MATH_ERROR)
	{
		printf(MAGEN"CALC_MATH_ERROR\n"RESET);
	}
	else if (status == CALC_MEMORY_ALLOCATION_ERROR)
	{
		printf(MAGEN"CALC_MEMORY_ALLOCATION_ERROR\n"RESET);
	}
	else if (status == CALC_SYNTAX_ERROR)
	{
		printf(MAGEN"CALC_SYNTAX_ERROR\n"RESET);
	}
}

