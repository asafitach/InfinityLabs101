#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 31000
#define NUM 90000000000


void *ThreadInsertValueInArray(void *index_to_assaign)
{
    int index = *(int *)&index_to_assaign;
    return (NULL);
}

void *SumDivisors(void *number)
{
    size_t num = *(size_t*)&number;
    size_t stop = num + 32300;
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
    size_t steps = NUM / SIZE + 1;

    for (index = 0; index < SIZE; ++index)
    {
        pthread_create(&threads_array[index], NULL, SumDivisors, (void *)((index * steps) + 1));
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