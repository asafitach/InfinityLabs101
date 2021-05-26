#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include "s_l_list.h"


#define RED "\033[1;31m"  /* print in red */
#define BLUE "\033[1;34m"  /* print in blue */
#define RESET "\033[0m" /* reset print color  */

#define PRODUCERS 5
#define CONSUMERS 5

slist_t *list;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

volatile int full_elements = 0;
volatile int free_elements = 15;

void *ProducerFunc(void *param);
void *ConsumerFunc(void *param);

int main()
{
    size_t p_index = 0;
    size_t c_index = 0;
    pthread_t prod[PRODUCERS] = {0};
    pthread_t cons[CONSUMERS] = {0};
    list = SlistCreate();
    if (NULL == list)
    {
        return (1);
    }

    for (p_index = 0; p_index < PRODUCERS; ++p_index)
    {
        pthread_create(&prod[p_index], NULL, ProducerFunc, NULL);
    }

    for (c_index = 0; c_index < CONSUMERS; ++c_index)
    {
        pthread_create(&cons[c_index], NULL, ConsumerFunc, NULL);
    }

    sleep(1);
    
    for (p_index = 0; p_index < PRODUCERS; ++p_index)
    {
        pthread_kill(prod[p_index], SIGINT);
    }

    for (c_index = 0; c_index < CONSUMERS; ++c_index)
    {
        pthread_kill(cons[c_index], SIGINT);
    }  

    pthread_mutex_destroy(&mutex);
    SlistDestroy(list);

    return (0);
}


void *ProducerFunc(void *param)
{
    int data = 0;

    while (1)
    {
        pthread_mutex_lock(&mutex);
        __sync_fetch_and_add(&full_elements, 1);
        if (15 > full_elements)
        {
            ++data;
            SlistInsert(SlistBegin(list), *(void **)&data);
            printf(RED"\nprod say %d\n"RESET, data);
            __sync_sub_and_fetch(&free_elements, 1);
        }
        else
        {
            __sync_sub_and_fetch(&full_elements, 1);
        }
        pthread_mutex_unlock(&mutex);
    }

    return (param);
}



void *ConsumerFunc(void *param)
{
    void *data = NULL;

    while (1)
    {
        pthread_mutex_lock(&mutex);
        __sync_add_and_fetch(&free_elements, 1);
        if (15 > free_elements)
        {
            data = SlistGetData(SlistBegin(list));
            SlistRemove(SlistBegin(list));
            printf(BLUE"\ncons say: %d\n"RESET, *(int *)&data);
            __sync_sub_and_fetch(&full_elements, 1);
        }
        else
        {
            __sync_sub_and_fetch(&free_elements, 1);
        }
        pthread_mutex_unlock(&mutex);
    }

    return (param);
}