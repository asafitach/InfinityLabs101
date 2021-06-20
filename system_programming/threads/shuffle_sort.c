#include <stdio.h> 	/* printf, fopen ... */
#include <string.h> /* strcmp */
#include <stdlib.h>
#include <sys/types.h> /* ssize_t */
#include <pthread.h>
#include <sys/time.h>

#define DUP 100
#define THREADS 16

static int g_steps = 1;

typedef struct dict_sort
{
    char **dictionary;
    size_t size;
} dict_sort_t;

/*****************************************************************************/
                    /* Functions Declaration */

static void LoadDictionary(char **dictionary, size_t size);
static size_t GetTableSize();
static void PrintDictionary(char **dictionary, size_t size);
int RandCompareFunc(const void *data1, const void *data2);
int StrCmp(const void *data1, const void *data2);
static void *ThreadSubSort(void *param);
static int Merge(char **sub_arr1, char **sub_arr2, size_t size1, size_t size2);
static void *ThreadMerge(void *param);
static void SortPartOfArray(char **dictionary, dict_sort_t **dict_sort, size_t total_words);
static void MergeArray(dict_sort_t **dict_sort);

/*****************************************************************************/
int main()
{
    size_t num_of_words = 0;
    size_t total_words = 0;
    char **dictionary = NULL;
    dict_sort_t **dict_sort = NULL;
    struct timeval start = {0};
    struct timeval end = {0};

    /* calculate num of words in a dictionary */
    num_of_words = GetTableSize();
    total_words = num_of_words * DUP;

    /* Create file with shuffle dictionary */
    dictionary = malloc(total_words * sizeof(char *));
    if (NULL == dictionary)
	{
		return (1);
	}
    LoadDictionary(dictionary, num_of_words);
    qsort(dictionary, total_words, sizeof(char *), RandCompareFunc);

    gettimeofday(&start, NULL);
    /* Each thread sort part of the dictionary */
    dict_sort = (dict_sort_t **)malloc(THREADS * sizeof(dict_sort_t *));
    SortPartOfArray(dictionary, dict_sort, total_words);

    /* Merge the subs-sorted arrays of the dictionary and print */
    MergeArray(dict_sort);
    gettimeofday(&end, NULL);
    printf("Num of dictionaries: %d, Num o f threads: %d\n", DUP, THREADS);
    printf("took %lu us\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
    /* PrintDictionary(dictionary, total_words); */

    return (0);
}

/*****************************************************************************/

static void SortPartOfArray(char **dictionary, dict_sort_t **dict_sort, size_t total_words)
{
    size_t i = 0;
    pthread_t threads[THREADS] = {0};
    size_t size = total_words / THREADS;
    size_t reminder = total_words % THREADS;

    for (i = 0; i < THREADS; ++i)
    {
        dict_sort[i] = malloc(sizeof(dict_sort_t));
        dict_sort[i]->dictionary = dictionary + (size * i);
        dict_sort[i]->size = size;
    }
    dict_sort[i - 1]->size += reminder;

    for (i = 0; i < THREADS; ++i)
    {
        pthread_create(&threads[i], NULL, ThreadSubSort, dict_sort[i]);
    }
	for (i = 0; i < THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }
}

/*****************************************************************************/

static void MergeArray(dict_sort_t **dict_sort)
{
    size_t i = 0;
    pthread_t threads[THREADS] = {0};
    size_t num_of_threads = THREADS / 2;
    size_t num_of_dict_to_jump = 2;

    while (num_of_threads)
    {
        for (i = 0; i < THREADS; i = i + num_of_dict_to_jump)
        {
            pthread_create(&threads[i], NULL, ThreadMerge, dict_sort + i);
        }
        for (i = 0; i < THREADS; i = i + num_of_dict_to_jump)
        {
            pthread_join(threads[i], NULL);
        }
        g_steps *= 2;
        num_of_threads /= 2;
        num_of_dict_to_jump *= 2;
    }
}

/*****************************************************************************/

static int Merge(char **sub_arr1, char **sub_arr2, size_t size1, size_t size2)
{
	size_t total_size = size1 + size2;
	char **runner1 = sub_arr1, **runner2 = sub_arr2;
	char **tmp_ruuner = NULL;
	char **sorted_tmp = malloc(total_size * sizeof(char *));
	if (NULL == sorted_tmp)
	{
		return (-1);
	}

	tmp_ruuner = sorted_tmp;
	while (runner1 < sub_arr1 + size1 && runner2 < sub_arr2 + size2)
	{
		if (0 > strcmp(*runner1, *runner2))
		{
            *tmp_ruuner = *runner1;
			++runner1;
		}
		else
		{
            *tmp_ruuner = *runner2;
			++runner2;
		}

		++tmp_ruuner;
	}

	while (runner1 < sub_arr1 + size1)
	{
        *tmp_ruuner = *runner1;
		++runner1;
		++tmp_ruuner;
	}
	while (runner2 < sub_arr2 + size2)
	{
        *tmp_ruuner = *runner2;
		++runner2;
		++tmp_ruuner;
	}

	tmp_ruuner = sorted_tmp;
	while (total_size)
	{
		*sub_arr1 = *tmp_ruuner;
		++sub_arr1;
		++tmp_ruuner;
		--total_size;
	}

	free(sorted_tmp);
	return (0);
}

/*****************************************************************************/

static void *ThreadMerge(void *param)
{
    dict_sort_t **dict_sort1 = (dict_sort_t **)param;
    dict_sort_t **dict_sort2 = dict_sort1 + g_steps;

    Merge((*dict_sort1)->dictionary, (*dict_sort2)->dictionary, (*dict_sort1)->size, (*dict_sort2)->size);
    (*dict_sort1)->size += (*dict_sort2)->size;

    return (NULL);
}

static void *ThreadSubSort(void *param)
{
    dict_sort_t *thread = (dict_sort_t *)param;
    qsort(thread->dictionary, thread->size, sizeof(char *), StrCmp);
    return (NULL);
}

/*****************************************************************************/

int StrCmp(const void *data1, const void *data2)
{
    return (strcmp(*(const char **)data1, *(const char **)data2));
}


int RandCompareFunc(const void *data1, const void *data2)
{
    (void)data1;
    (void)data2;
    return (rand() % 2 == 0 ? 1 : -1);
}

/*****************************************************************************/

static void LoadDictionary(char **dictionary, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	char word[25] = {0};
    int word_length = 0;


	for (j = 0; j < DUP; ++j)
	{
		FILE *fptr = fopen("/usr/share/dict/words", "r");
		if (NULL == fptr)
		{
			return;
		}
		for (i = 0; i < size; ++i)
		{
            fgets(word, 25, fptr);
			word_length = strlen(word);
			dictionary[i + j * size] = malloc(word_length + 1);
            word[word_length - 1] = '\0';
			strcpy(dictionary[i + j * size], word);
		}
		fclose(fptr);
	}
}

/*****************************************************************************/

static size_t GetTableSize()
{
	FILE *fptr = NULL;
	size_t num_of_words = 0;
	char word[25] = {0};

	fptr = fopen("/usr/share/dict/words", "r");
	if (NULL == fptr)
	{
		return (0);
	}

    while (fgets(word, 25, fptr))
    {
        ++num_of_words;
    }

	fclose(fptr);

	return (num_of_words);
}

/*****************************************************************************/

static void PrintDictionary(char **dictionary, size_t size)
{
    size_t i = 0;
    for(i = 0; i < size; i++)
    {
        printf("%s\n", dictionary[i]);
    }
}