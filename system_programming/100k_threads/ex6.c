#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define SIZE 31000
#define NUM 1000000000


void *ThreadInsertValueInArray(void *index_to_assaign)
{
    int index = *(int *)&index_to_assaign;
    return (NULL);
}

void *SumDivisors(void *number)
{
    size_t num = *(size_t*)&number;
    size_t sum_of_divisors = 0;
    size_t i = 1;

    #pragma omp parallel for
    for(i = 1; i <= num; i++)
    {
        if(0 == num % i)
        {
            sum_of_divisors += i;
        } 
    }


    return (*(void **)&sum_of_divisors);
}

int main()
{
    size_t sum = (size_t)(SumDivisors((void *)NUM));

 
    printf("%lu: sum of dividors\n", sum);

    printf("Done!\n");


    return (0);
}