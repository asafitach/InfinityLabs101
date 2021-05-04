#include <stdio.h>
#include "utility.h"


int main()
{
    double x = 1;
    double y = 3;

    printf("%f raised by %f equal %f\n", x, y, DPower(x, y));

    x = -2;
    y = -2;
    printf("%f raised by %f equal %f\n", x, y, DPower(x, y));
    
    x = 0.5;
    y = -1;
    printf("%f raised by %f equal %f\n", x, y, DPower(x, y));

    x = 4;
    y = 1;
    printf("%f raised by %f equal %f\n", x, y, DPower(x, y));

    x = 4;
    y = 0;
    printf("%f raised by %f equal %f\n", x, y, DPower(x, y));

    return 0;
}