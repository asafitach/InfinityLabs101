#include <stdio.h> /* printf */ 

#include <stdlib.h> /*system*/



#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[1;36m"
#define RESET "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)


typedef enum calculator_status
{
    CALC_SUCCESS,                   /*standard mode*/
    CALC_MATH_ERROR,                /*DIVISION by 0 or powering by non natural number*/
    CALC_MEMORY_ALLOCATION_ERROR,   /*while pushing to stack*/
    CALC_SYNTAX_ERROR               /*operator/num/parenthesis not in the right place*/
} calculator_status_t;


calculator_status_t Calculate(const char *expression, double *res);

int main()
{
    double res = 0;

    printf(CYAN"\nCalculate Test\n"RESET);

    res = 0;
    printf(YELLOW"\n7+8\n"RESET);
    if ((CALC_SUCCESS == Calculate("7+8", &res)) && (15 == res))
    {
        printf(GREEN"pass\n"RESET);
    }
    else
    {
        printf(RED"failed\n"RESET);
    }

    res = 0;
    printf(YELLOW"\n8+8 * 3+-2^5\n"RESET);
    if ((CALC_SUCCESS == Calculate("8+8 * 3+-2^5", &res)) && (0 == res))
    {
        printf(GREEN"pass\n"RESET);
    }
    else
    {
        printf(RED"failed\n"RESET);
    }

    res = 0;
    printf(YELLOW"\n8+8 * 3-2^\n"RESET);
    if ((CALC_SYNTAX_ERROR == Calculate("8+8 * 3-2^", &res)) && (0 == res))
    {
        printf(GREEN"pass\n"RESET);
    }
    else
    {
        printf(RED"failed\n"RESET);
    }

    res = 0;
    printf(YELLOW"\n2/0\n"RESET);
    if ((CALC_MATH_ERROR == Calculate("2/0", &res)) && (0 == res))
    {
        printf(GREEN"pass\n"RESET);
    }
    else
    {
        printf(RED"failed\n"RESET);
    }

    res = 0;
    printf(YELLOW"\n8++8 * ((3-2) * 5)\n"RESET);
    if ((CALC_SUCCESS == Calculate("8++8 * ((3-2) * 5)", &res)) && (48 == res))
    {
        printf(GREEN"pass\n"RESET);
    }
    else
    {
        printf(RED"failed\n"RESET);
    }

    res = 0;
    printf(YELLOW"\n3-2) * 5\n"RESET);
    if ((CALC_SYNTAX_ERROR == Calculate("3-2) * 5", &res)) && (0 == res))
    {
        printf(GREEN"pass\n"RESET);
    }
    else
    {
        printf(RED"failed\n"RESET);
    } 

    printf(CYAN"\nEnd\n"RESET);

    return (0);
}
