#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


#define MAX_WORD 50
#define DUP 3
#define THREADS 4

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
        CopyBuff(buff + (index * g_word_count) + 1, buff);
    }

    DestroyBuffer(buff, g_word_count * DUP);

    for (index = 0; index < THREADS; ++ index)
    {
        pthread_create(threads + index, NULL, CountLettersInWord, (void *)buff);
    }

    for (index = 0; index < THREADS; ++ index)
    {
        pthread_join(threads[index], NULL);
    }

    for (index = 1; index < MAX_WORD; ++index)
    {
        g_count_lut[index] += g_count_lut[index - 1];
    }

    CountingMerge(buff);
    PrintDict(buff);
    

    return (0);
}



void *CountLettersInWord(void *buffer)
{
    char **buff = (char **)buffer;
    size_t thread = __sync_fetch_and_add(&g_thread_num, 1);
    size_t section = g_word_count / THREADS;
    size_t count_lut[MAX_WORD] = {0};
    size_t index = 0;


    buff += (section) * thread;

    while (section && NULL != *buff)
    {
        ++count_lut[strlen(*buff)];
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
    char **dup_buff = (char **)malloc(sizeof(char *) * g_word_count);
    if (NULL == dup_buff)
    {
        return (NULL);
    }

    for (index = 0; index < g_word_count; ++index)
    {
        dup_buff[g_count_lut[strlen(buff[index])] - 1] = buff[index];
    }

    for (index = 0; index < g_word_count; ++index)
    {
        buff[index] = dup_buff[index];
    }

    free(dup_buff);

    return (buff);
}


char **CreateBuffer(size_t num_of_lines)
{
    size_t index = 0;
    char **buff = (char **)malloc(num_of_lines * sizeof(char *));
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
    size_t len = 0;

    fp = fopen("/usr/share/dict/words", "r");
    if (NULL == fp)
    {
        return ;
    }

    while (EOF != fscanf(fp, "%s", buff[index]))
    {
        len = strlen(buff[index]);
        if (len > 0 && ' ' < buff[index][0])
        {
/*             buff[index][len - 1] = '\0'; */ 
            ++index;
        }
    }
    buff[index + 1] = 0;

    fclose(fp);
}

void PrintDict(char **buff)
{
    printf("|Dictionary print:|\n\n");
    while (0 != *buff)
    {
        printf("%s\n", *buff);
        ++buff;
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

    while (NULL != fgets(buff, 48, fp))
    {
        ++counter;
    }
    fclose(fp);

    return (counter);
    
}
