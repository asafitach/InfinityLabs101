#include <stdio.h>

#define PRESICE 0.00000000000001 /* max prisice or insert "if" check for number == 0 */
double Sqrt(double number);


int main()
{
    double number = 25;
    printf("sqrt of %f is %f\n", number, Sqrt(number));

    number = 7.25;
    printf("sqrt of %f is %f\n", number, Sqrt(number));

    number = 6;
    printf("sqrt of %f is %f\n", number, Sqrt(number));

    number = 658;
    printf("sqrt of %f is %f\n", number, Sqrt(number));

    number = 0;
    printf("sqrt of %f is %f\n", number, Sqrt(number));

    return (0);
}

double Sqrt(double number)
{
    double root = 0;
    double jump = 100;

    if (0 > number)
    {
        return (-1);
    }

    while ((root * root) != number)
    {
        while ((root * root) < number)
        {
            root += jump;
        }

        root -= jump;
        jump = jump / 10;

        if (PRESICE  > jump)
        {
            return (root);
        }
    }

    return (root);
}