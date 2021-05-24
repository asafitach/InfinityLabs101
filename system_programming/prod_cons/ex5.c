#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h> /* O_CREAT */
#include <signal.h>


#define RED "\033[1;31m"  /* print in red */
#define BLUE "\033[1;34m"  /* print in blue */
#define RESET "\033[0m" /* reset print color  */

#define PRODUCERS 1
#define CONSUMERS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
sem_t *semaphore = NULL;
volatile unsigned int msg_g = 0;


void *ProducerFunc(void *param);
void *ConsumerFunc(void *param);

int main()
{
    size_t p_index = 0;
    size_t c_index = 0;
    pthread_t prod[PRODUCERS] = {0};
    pthread_t cons[CONSUMERS] = {0};


    semaphore = sem_open("/ex5", O_CREAT, 0644, 0);
    if (SEM_FAILED == semaphore)
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

    sleep(5);
    
    for (p_index = 0; p_index < PRODUCERS; ++p_index)
    {
        pthread_kill(prod[p_index], SIGINT);
    }

    for (c_index = 0; c_index < CONSUMERS; ++c_index)
    {
        pthread_kill(cons[c_index], SIGINT);
    }  

    pthread_mutex_destroy(&mutex);
    sem_unlink("/ex5");
    pthread_cond_destroy(&condition);

    return (0);
}


void *ProducerFunc(void *param)
{
    int data = 0;
    int index = 0;

    while (1)
    {
        ++data;
        pthread_mutex_lock(&mutex);
        msg_g = data;
        printf(RED"\nprod say %d\n"RESET, data);
        pthread_mutex_unlock(&mutex);
        for (index = 0; index < CONSUMERS; ++index)
        {
            sem_wait(semaphore);
        }
        pthread_cond_broadcast(&condition);
    }

    return (param);
}



void *ConsumerFunc(void *param)
{
    unsigned int data = 0;

    while (1)
    {
        pthread_mutex_lock(&mutex);
        sem_post(semaphore);
        data = msg_g;
        printf(BLUE"\ncons say: %u\n"RESET, data);
        pthread_cond_wait(&condition, &mutex);
        pthread_mutex_unlock(&mutex);
    }

    return (param);
}