#include <stdio.h>/*printf*/
#include <pthread.h>/*pthread_create, pthread_join, pthread_deatach*/
#include <unistd.h>/*sleep*/

#define SIZE 100000

size_t global_array_t[SIZE] = {0};

void *ThreadInsertValueInArray(void *index_to_assaign)
{
    size_t index = *(size_t *)&index_to_assaign;
    global_array_t[index] = index;

    return (NULL);
}


int main()
{
    pthread_t threads_array[SIZE] = {0};
    size_t index = 0;

    for (index = 0; index < SIZE; ++index)
    {
         pthread_create(&threads_array[index], NULL, ThreadInsertValueInArray, *(void **)&index);
         pthread_detach(threads_array[index]); 
    }

    for (index = 0 ; index < SIZE; ++index)
    {
        if (index != (size_t)global_array_t[index])
        {
            printf("%lu is not set\n", index);
        }
    }

    printf("Done!\n");

    return (0);
}