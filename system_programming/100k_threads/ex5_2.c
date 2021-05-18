#include <stdio.h>/*printf*/
#include <pthread.h>/*pthread_create, pthread_join, pthread_deatach*/
#include <unistd.h>/*sleep*/

#define SIZE 1
#define NUM 1000000000
#define STEP  ((NUM / SIZE) + 1)



void *SumDivisors(void *number)
{
    size_t num = *(size_t*)&number;
    size_t stop = num + STEP;
    size_t sum_of_divisors = 0;

    if (stop > NUM)
    {
        stop = NUM;
    }
    

    for(; num <= stop; num++)
    {
        if(0 == NUM % num)
        {
            sum_of_divisors += num;
        } 
    }


    return (*(void **)&sum_of_divisors);
}

int main()
{
    pthread_t threads_array[SIZE] = {0};
    size_t index = 0;
    void *data = NULL;
    size_t sum = 0;
    

    for (index = 0; index < SIZE; ++index)
    {
        pthread_create(&threads_array[index], NULL, SumDivisors, (void *)((index * STEP) + 1));
    }

    for (index = 0; index < SIZE; ++index)
    {
        pthread_join(threads_array[index], &data);
        sum += (size_t)data;

    } 
 
    printf("%lu: sum of dividors\n", sum);

    printf("Done!\n");


    return (0);
}