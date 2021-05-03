#ifndef __SORTS_H__
#define __SORTS_H__

#include <stddef.h>  /* size_t */

void BubbleSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

void RadixSort(int *arr, size_t size);

void CountingSort(int *arr, size_t size);

int *BinarySearch(int *arr, int array_size, int num);

int *RecursiveBinarySearch(int *arr, int array_size, int num);

void MergeSort(int *arr, size_t size);/*recursive*/

void Qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));

#endif /*__SORTS_H__*/
