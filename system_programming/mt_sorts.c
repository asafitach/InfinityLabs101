#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
/* 
threads     time
4           real	0m4.274s user	0m0.752s sys	0m2.125s




 */

#define MAX_WORD 50
#define DUP 4
#define THREADS 8


void PrintDict(char **buff);
void LoadDictionary(char **buff);
void RandomizeDictionary(char **buff);
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
    RandomizeDictionary(buff);
    
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

void RandomizeDictionary(char **buff)
{
    char *tmp = NULL;
    size_t index = 0;
    size_t random_index = 0;

    qsort(buff, g_word_count, sizeof(char *), random);
/* 
    for (index = 0; index < g_word_count; ++index)
    {
        tmp = buff[index];
        random_index = rand() % g_word_count - 1;
        buff[index] = buff[random_index];
        buff[random_index] = tmp;
    }
 */}


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

void Merge(char **left_arr, int left_len, char **right_arr, int right_len)/*/maby use runner !!!*/
{
	int left_runner = 0;
	int right_runner = 0;
	int *tmp_index = NULL;

	int *tmp_arr = (int *)malloc(sizeof(int) * (left_len + right_len));
	if (NULL == tmp_arr)
	{
		return;
	}
	tmp_index = tmp_arr;

	assert(NULL != left_arr);
	assert(NULL != right_arr);

	while (left_runner < left_len && right_runner < right_len)
	{
		if (left_arr[left_runner] <= right_arr[right_runner])
		{
			*tmp_index = left_arr[left_runner];
			++left_runner;
		}
		else
		{
			*tmp_index = right_arr[right_runner];
			++right_runner;
		}
		++tmp_index;
	}

	while (left_runner < left_len)
	{
		*tmp_index = left_arr[left_runner];
		++left_runner;
		++tmp_index;
	}
	while (right_runner < right_len)
	{
		*tmp_index = right_arr[right_runner];
		++right_runner;
		++tmp_index;
	}

	ArrCpy(left_arr, tmp_arr, left_len + right_len);
	free(tmp_arr);
}

void MergeSort(void *param)
{
    char **buff = (char **)param;
    size_t size = DUP *g_word_count; 


	MergeSort(buff, size / 2);
	MergeSort(arr + (size / 2), size - (size / 2));

	Merge(arr ,size / 2, arr + (size / 2), size - (size / 2));
}