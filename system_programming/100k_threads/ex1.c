#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 100000

int global_array_t[SIZE] = {0};

void *ThreadInsertValueInArray(void *index_to_assaign)
{
    int index = *(int *)&index_to_assaign;
    global_array_t[index] = index;

    return (NULL);
}


int main()
{
    pthread_t threads_array[SIZE] = {0};
    int index = 0;

    for (index = 0; index < SIZE; ++index)
    {
        pthread_create(&threads_array[index], NULL, ThreadInsertValueInArray, (void *)index);

    }

    sleep(10);

    for (index = 0 ; index < SIZE; ++index)
    {
        if (index != global_array_t[index])
        {
            printf("%d is not set\n", index);
        }
    }

    printf("Done!\n");

    return (0);
}