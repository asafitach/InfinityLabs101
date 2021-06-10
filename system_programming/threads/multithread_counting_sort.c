#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_OF_BUFFERS 2
#define LINE_SIZE 50
#define NUM_OF_THREADS 4

void LoadDictionary(char *buff);
size_t LinesInDictionary();

volatile unsigned int g_num_of_thread = 0;

int main()
{
    int index = 0;
    size_t letters = 0;
    pthread_t threads[NUM_OF_THREADS] = {0};
    size_t lines = LinesInDictionary();
    char *buff = (char *)malloc(lines * LINE_SIZE * NUM_OF_BUFFERS);
    if (NULL == buff)
    {
        return (1);
    }

    LoadDictionary(buff);
    letters = strlen(buff);
     for (index = 1; index < NUM_OF_BUFFERS; ++index)
    {
        memcpy(buff + (index * letters), buff, letters);
    } 

    for (index = 0; index < NUM_OF_THREADS; ++index)
    {

    }


    free(buff);

    return (0);
}

void *CountLetters(void *buff)
{
    char *buffer = buff;
    unsigned int thread_num = __sync_fetch_and_add(&g_num_of_thread, 1);
    size_t counter = 0;

    



}


/* void CountingSort(int *arr)
{
	size_t index = 0;
	int tmp = 0;
	int min = 0;
	size_t range = (size_t)RangeOfArr(arr, (int)g_size, &min);
	int *count_array = calloc(sizeof(int), range + 1);
	int *output = (int *)malloc(size * sizeof(int));
	if (NULL == count_array || NULL == output)
	{
		printf("Allocation Failed\n");
		return;
	}
	
	for (index = 0; index < g_size; ++index)
	{
		count_array[arr[index] - min] += 1;
	}
	
	for (index = 1; index <= range; ++index)
	{
		count_array[index] += count_array[index - 1];
	}
	
	 for (index = 0; index < size; ++index)
	 {
	 	tmp = arr[index] - min;
	 	output[count_array[tmp] - 1] = tmp + min;
	 	count_array[tmp] -=1;
	 }
	 
	 ArrCpy(arr, output, size);
	 
	 free(count_array);
	 free(output);
} */


void LoadDictionary(char *buff)
{
    FILE *fp = NULL;
    int status = 0;
    size_t index = 0;
    size_t len = 0;
    char tmp_str[LINE_SIZE] = {0};

    fp = fopen("/usr/share/dict/words", "r");
    if (NULL == fp)
    {
        return ;
    }

    while (0 != fgets(tmp_str, LINE_SIZE, fp))
    {
        strcpy(buff + index, tmp_str);
        index += (strlen(tmp_str) - 1);
    }
    buff[index + 1] = 0;

    fclose(fp);
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

    while (NULL != fgets(buff, 48, fp) )
    {
        ++counter;
    }
    fclose(fp);

    return (counter);
    
}