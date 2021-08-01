#include <assert.h>
#include <stdio.h>
#include "utility.h"

void SortBinaryArray(int *arr, size_t size)
{
    int *runner = NULL;

    assert(NULL != arr);

    while (size && 0 == *arr)
    {
        --size;
        ++arr;
    }

    runner = arr + 1;
    size = (size == 0 ) ? 0: size - 1;

    while (size)
    {
        --size;
        if (0 == *runner)
        {
            *arr = 0;
            *runner = 1;
            ++arr;
        }
        ++runner;
    }
}

#define SIZE 500

int main()
{
    int arr[SIZE] = {0};

    GetRandomArray(arr, SIZE, 2);

    PrintArr(arr, SIZE);
    SortBinaryArray(arr, SIZE);
    PrintArr(arr, SIZE);

    return (0);
}