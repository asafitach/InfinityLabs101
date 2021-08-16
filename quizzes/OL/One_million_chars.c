#include <stdio.h>

#define ALL_ASCII 256
from git hub

void PrintLut(size_t lut[])
{
    int index = 1;
    size_t times = 0;

    for (index = 1; index < ALL_ASCII; ++index)
    {
        times = lut[index];
        if (10 == index)
        {
            printf("char new line occure %lu times\n" , times);
            lut[index] = 0;           
        }
        else if (0 != times)
        {
            printf("char %c occure %lu times\n", index , times);
            lut[index] = 0;
        }
    }
}

void LutOfTimes(char chr)
{
    static size_t lut[ALL_ASCII] = {0};
    size_t index = 0;

    if ('0' == chr)
    {
        PrintLut(lut);
    }
    else
    {
        lut[chr] +=1;
    }
}
