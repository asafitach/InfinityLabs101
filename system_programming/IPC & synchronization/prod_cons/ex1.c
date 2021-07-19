#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include "s_l_list.h"

#define RED "\033[1;31m"  /* print in red */
#define BLUE "\033[1;34m"  /* print in blue */
#define RESET "\033[0m" /* reset print color  */

#define PRODUCERS 1
#define CONSUMERS 1

volatile unsigned int is_allowed;
volatile unsigned int data = 0;

void *ProducerFunc(void *param);
void *ConsumerFunc(void *param);

int main()
{
    size_t p_index = 0;
    size_t c_index = 0;
    pthread_t prod[PRODUCERS] = {0};
    pthread_t cons[CONSUMERS] = {0};

    for (p_index = 0; p_index < PRODUCERS; ++p_index)
    {
        pthread_create(&prod[p_index], NULL, ProducerFunc, NULL);
    }

    for (c_index = 0; c_index < CONSUMERS; ++c_index)
    {
        pthread_create(&cons[c_index], NULL, ConsumerFunc, NULL);
    }

/*     for (p_index = 0; p_index < PRODUCERS; ++p_index)
    {
        pthread_join(prod[p_index]);
    }

    for (c_index = 0; c_index < CONSUMERS; ++c_index)
    {
        pthread_join(cons[c_index]);
    } */

    sleep(1);

    return (0);
}


void *ProducerFunc(void *param)
{

    while (1)
    {
        if (0 == __sync_val_compare_and_swap(&is_allowed, 0, 1))
        {
            printf(RED"prod say: %u\n", ++data);
            while (1 != __sync_val_compare_and_swap(&is_allowed, 1, 0))
            {
                ;
            }        
        }
    }

    return (param);
}



void *ConsumerFunc(void *param)
{

    while (1)
    {
        if (0 == __sync_val_compare_and_swap(&is_allowed, 0, 1))
        {
            printf(BLUE"cons say: %u\n", data);
            while (1 != __sync_val_compare_and_swap(&is_allowed, 1, 0))
            {
                ;
            }
        }
    }

    return (param);
}