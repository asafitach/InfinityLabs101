#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h> /* O_CREAT */
#include "queue.h"

#define RED "\033[1;31m"  /* print in red */
#define BLUE "\033[1;34m"  /* print in blue */
#define RESET "\033[0m" /* reset print color  */


#define PRODUCERS 3
#define CONSUMERS 3

queue_t *queue = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t *occupied_space;
sem_t *free_space;



void *ProducerFunc(void *param);
void *ConsumerFunc(void *param);

int main()
{
    size_t p_index = 0;
    size_t c_index = 0;
    pthread_t prod[PRODUCERS] = {0};
    pthread_t cons[CONSUMERS] = {0};
    queue = QueueCreate();
    if (NULL == queue)
    {
        return (1);
    }

    sem_unlink("/full_sem");
    sem_unlink("/empty_sem");

    occupied_space = sem_open("/full_sem" , O_CREAT, 0644, 0);
    if (occupied_space == SEM_FAILED) 
    {
        return(1);
    }

    free_space = sem_open("/empty_sem" , O_CREAT, 0644, 10);
    if (free_space == SEM_FAILED) 
    {
        return(1);
    }
        

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

    pthread_mutex_destroy(&mutex);
    sem_unlink("/full_sem");
    sem_unlink("/empty_sem");    
    QueueDestroy(queue);

    return (0);
}


void *ProducerFunc(void *param)
{
    int flag = 0;
    static volatile int data = 0;
/*     int free_val = 0;
    int full_val = 0; */


    while (1)
    {
        sem_wait(free_space);
        pthread_mutex_lock(&mutex);
        data = (flag == 1) ? data: __sync_add_and_fetch(&data, 1);
        if (0 == Enqueue(queue, *(void **)&data))
        {   
            flag = 1;
            sem_post(free_space);
        }
        else
        {
            flag = 0;
            sem_post(occupied_space);
/*             sem_getvalue(free_space, &free_val);
            sem_getvalue(occupied_space, &full_val);
            printf(RED"prod say %d free %d full %d\n"RESET, data, free_val, full_val); */
            printf(RED"prod say %d\n"RESET, data);
        }
        pthread_mutex_unlock(&mutex);
    }

    return (param);
}


void *ConsumerFunc(void *param)
{
    void *data = NULL;
/*     int free_val = 0;
    int full_val = 0; */

    while (1)
    {
        sem_wait(occupied_space);
        pthread_mutex_lock(&mutex);
        data = QueuePeek(queue);
        Dequeue(queue);
/*         sem_getvalue(free_space, &free_val);
        sem_getvalue(occupied_space, &full_val);
        printf(BLUE"cons say %d free %d full %d\n"RESET, *(int *)&data, free_val, full_val); */
        printf(BLUE"cons say %d\n"RESET, *(int *)&data);
        pthread_mutex_unlock(&mutex);
        sem_post(free_space);
    }

    return (param);
}