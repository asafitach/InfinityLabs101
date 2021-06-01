#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_BUFFERS 2
#define LINE_SIZE 50
#define NUM_OF_LINES 102500

void PrintDict(char **buff);
void LoadDictionary(char *buff);
void DestroyBuffer(char **buff, size_t index);
char *CreateBuffer(size_t num_of_lines);
void DestroyBufferArray(char ***buff_array, size_t buffers);
void CopyBuff(char **dest, char **src);
size_t LinesInDictionary();




int main()
{
    int index = 0;
    size_t letters = 0;
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

    printf("%s", buff);

/*     PrintDict(*buff);
    DestroyBufferArray(buff, NUM_OF_BUFFERS); */
    free(buff);

    return (0);
}

void DestroyBufferArray(char ***buff_array, size_t buffers)
{
    while (buffers)
    {
        DestroyBuffer(buff_array[buffers - 1], NUM_OF_LINES);
        --buffers;
    }
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

/* 
char *CreateBuffer(size_t num_of_lines)
{
    size_t index = 0;
    char *buff = (char *)malloc(num_of_lines * LINE_SIZE);
    if (NULL == buff)
    {
        return (NULL);
    }

    for (index = 0; index < num_of_lines; ++index)
    {
        buff[index] = (char *)malloc(LINE_SIZE);
        if (NULL == buff[index])
        {
            DestroyBuffer(buff, index);
            return(NULL);
        }
    }

    return (buff);
} */

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
        strncpy(*dest, *src, 255);
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

    while (NULL != fgets(buff, 48, fp) )
    {
        ++counter;
    }
    fclose(fp);

    return (counter);
    
}