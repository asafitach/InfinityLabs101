#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h> /* O_CREAT */
#include "s_l_list.h"

#define RED "\033[1;31m"  /* print in red */
#define BLUE "\033[1;34m"  /* print in blue */
#define RESET "\033[0m" /* reset print color  */


#define PRODUCERS 5
#define CONSUMERS 5

slist_t *list;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t *sem;


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

    sem_unlink("/new_sem");
    sem = sem_open("/new_sem" , O_CREAT, 0644, 0);
    if (sem == SEM_FAILED) 
    {
        return(1);
    }    

    /* creating all threads */
    for (p_index = 0; p_index < PRODUCERS; ++p_index)
    {
        pthread_create(&prod[p_index], NULL, ProducerFunc, NULL);
    }
    for (c_index = 0; c_index < CONSUMERS; ++c_index)
    {
        pthread_create(&cons[c_index], NULL, ConsumerFunc, NULL);
    }

    sleep(2);

    /* termination of all threads */
    for (p_index = 0; p_index < PRODUCERS; ++p_index)
    {
        pthread_kill(prod[p_index], SIGTERM);
    }

    for (c_index = 0; c_index < CONSUMERS; ++c_index)
    {
        pthread_kill(cons[c_index], SIGTERM);
    }  

    pthread_mutex_destroy(&mutex);
    SlistDestroy(list);

    return (0);
}


void *ProducerFunc(void *param)
{
    int flag = 0;
    static volatile int data = 0;


    while (1)
    {
        data = (flag == 1) ? data: __sync_add_and_fetch(&data, 1);
        pthread_mutex_lock(&mutex);
        flag = (SlistEnd(list) == SlistInsert(SlistBegin(list), *(void **)&data));
        pthread_mutex_unlock(&mutex);
        if (0 == flag)
        {
            sem_post(sem);
            printf(RED"prod say %d\n"RESET, data);
        }
    }

    return (param);
}


void *ConsumerFunc(void *param)
{
    void *data = NULL;
    slist_iter_t begin = NULL;

    while (1)
    {
        sem_wait(sem);
        pthread_mutex_lock(&mutex);
        begin = SlistBegin(list);
        data = SlistGetData(begin);
        SlistRemove(begin);
        pthread_mutex_unlock(&mutex);
        printf(BLUE"cons say: %d\n"RESET, *(int *)&data);
    }

    return (param);
}