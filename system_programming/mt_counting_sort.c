#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
/* 
threads     time
4           real	0m4.274s user	0m0.752s sys	0m2.125s
5           real	0m4.716s user	0m0.747s sys	0m2.451s
6           real	0m4.634s user	0m0.733s sys	0m2.547s
7           real	0m4.412s user	0m0.680s sys	0m2.298s
8           real	0m4.553s user	0m0.762s sys	0m2.377s
9           real	0m4.694s user	0m0.716s sys	0m2.365s
10          real	0m4.907s user	0m0.719s sys	0m2.573s
11          real	0m4.893s user	0m0.819s sys	0m2.474s
12          real	0m4.898s user	0m0.869s sys	0m2.436s

 */

#define MAX_WORD 50
#define DUP 200
#define THREADS 12


void PrintDict(char **buff);
void LoadDictionary(char **buff);
void DestroyBuffer(char **buff, size_t index);
char **CreateBuffer(size_t num_of_lines);
void CopyBuff(char **dest, char **src);
void *CountLettersInWord(void *buffer);
size_t LinesInDictionary();
void *CountLettersInWord(void *buffer);
char **CountingMerge(char **buff);




size_t g_thread_num = 0;
size_t g_word_count = 0;
size_t g_count_lut[MAX_WORD] = {0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;



int main()
{
    int index = 0;
    char **buff = NULL;
    pthread_t threads[THREADS] = {0};


    g_word_count = LinesInDictionary();


    buff = CreateBuffer(g_word_count * DUP);
    if (NULL == buff)
    {
        return (1);
    }

    LoadDictionary(buff);
    
    for (index = 1; index < DUP; ++index)
    {
        CopyBuff(buff + (index * (g_word_count )) , buff);
    }

    for (index = 0; index < THREADS; ++index)
    {
        pthread_create(threads + index, NULL, CountLettersInWord, (void *)buff);
    }

    for (index = 0; index < THREADS; ++index)
    {
        pthread_join(threads[index], NULL);
    }

    g_count_lut[0] = 0;
    for (index = 1; index < MAX_WORD; ++index)
    {
        g_count_lut[index] += g_count_lut[index - 1];
    }

    CountingMerge(buff);
    PrintDict(buff);

    DestroyBuffer(buff, g_word_count * DUP);

    return (0);
}



void *CountLettersInWord(void *buffer)
{
    char **buff = (char **)buffer;
    size_t thread = __sync_fetch_and_add(&g_thread_num, 1);
    size_t section = g_word_count  * DUP / THREADS;
    size_t count_lut[MAX_WORD] = {0};
    size_t index = 0;

    buff += (section) * thread;
    if (thread + 1 == THREADS)
    {
        section = (g_word_count * DUP) - (section * (THREADS - 1));
    }


    while (section)
    {
        if (NULL != *buff)
        {
            ++count_lut[strlen(*buff)];
            --section;
        }
            ++buff;
    }

    pthread_mutex_lock(&mutex);
    for (index = 0; index < MAX_WORD; ++index)
    {
        g_count_lut[index] += count_lut[index];
    }
    pthread_mutex_unlock(&mutex);

    return (NULL);
}


char **CountingMerge(char **buff)
{
    size_t index = 0;
    size_t len = 0;
    char **dup_buff = (char **)malloc(sizeof(char *) * g_word_count * DUP);
    if (NULL == dup_buff)
    {
        return (NULL);
    }

    for (index = 0; index < (g_word_count * DUP); ++index)
    {
        if (NULL != buff[index])
        {
            len = strlen(buff[index]);
            dup_buff[g_count_lut[len - 1]] = buff[index];
            ++g_count_lut[len - 1];
        }
    }

    for (index = 0; index < g_word_count * DUP; ++index)
    {
        buff[index] = dup_buff[index];
    }

    free(dup_buff);

    return (buff);
}


char **CreateBuffer(size_t num_of_lines)
{
    size_t index = 0;
    char **buff = (char **)malloc(num_of_lines  * sizeof(char *));
    if (NULL == buff)
    {
        return (NULL);
    }

    for (index = 0; index < num_of_lines; ++index)
    {
        buff[index] = (char *)malloc(MAX_WORD);
        if (NULL == buff[index])
        {
            DestroyBuffer(buff, index);
            return(NULL);
        }
    }

    return (buff);
}

void DestroyBuffer(char **buff, size_t index)
{
    while (index)
    {
        free(buff[index - 1]);
        --index;
    }

    free(buff);

    return;
}

void LoadDictionary(char **buff)
{
    FILE *fp = NULL;
    size_t index = 0;

    fp = fopen("/usr/share/dict/words", "r");
    if (NULL == fp)
    {
        return ;
    }

    while (EOF != fscanf(fp, "%s", buff[index]))
    {
        index = ('A' <= *buff[index]) ? index + 1: index;
    }
    buff[index + 1] = 0;

    fclose(fp);
}

void PrintDict(char **buff)
{
    size_t counter = 0;
    printf("|Dictionary print:|\n\n");
    while (counter < g_word_count * DUP )
    {
        if (0 != *buff)
        {
        printf("%s\n", *buff);
        }
        ++buff;
        ++counter; 
    }
    printf("|Dictionary end|\n");
}

void CopyBuff(char **dest, char **src)
{
    while (0 != *src)
    {
        strcpy(*dest, *src);
        ++src;
        ++dest;
    }
}

size_t LinesInDictionary()
{
    FILE *fp = NULL;
    char buff[100] = {0};
    size_t counter = 0;

    fp = fopen("/usr/share/dict/words", "r");
    if (NULL == fp)
    {
        return 0;
    }

    while (EOF != fscanf(fp, "%s", buff))
    {
        ++counter;
    }
    fclose(fp);

    return (counter);
    
}
