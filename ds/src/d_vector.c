#include <stdio.h>/* printf */
#include <stdlib.h>/* malloc, realloc, free */
#include <assert.h>/* assert */
#include "d_vector.h"

#define GROWTH_FACTOR (2)

struct d_vector    
{
	size_t num_of_elements;
	size_t capacity;
	void **elements;
};


d_vector_t *VectorCreate(size_t init_capacity)
{
	d_vector_t *d_vector = (d_vector_t*)malloc(sizeof(d_vector_t));
	if (NULL == d_vector)
	{
		printf("Allocation failed");
		return (NULL);
	}
	
	d_vector->capacity = init_capacity;
	d_vector->num_of_elements = 0;
	d_vector->elements = malloc(init_capacity * sizeof(void*));
	if (NULL == d_vector->elements)
	{
		free(d_vector);
		printf("Allocation failed");
		return (NULL);
	}
	
	return (d_vector);
}


void VectorDestroy(d_vector_t *d_vector)
{
	assert(NULL != d_vector);
	free(d_vector->elements);
	d_vector->elements = NULL;
	free(d_vector);
	d_vector = NULL;
}


void VectorPopBack(d_vector_t *d_vector)
{
	assert(NULL != d_vector);
	*(d_vector->elements + d_vector->num_of_elements - 1) = NULL;
	d_vector->num_of_elements--;
}
	


status_t VectorPushBack(d_vector_t *d_vector, const void *item)
{
	status_t stat = SUCCESS;
	assert(NULL != d_vector);
	
	if (d_vector->capacity == d_vector->num_of_elements)
	{
		stat = VectorExpand(d_vector, (d_vector->num_of_elements * 2));
		if (stat == FAIL)
		{
			return (stat);
		}
	}
	
	d_vector->elements[d_vector->num_of_elements] = (void*)item;
	d_vector->num_of_elements++;
	
	return (stat);
}
	

void VectorSetElement(const d_vector_t *d_vector, size_t index, const void *item)
{
	assert(NULL != d_vector);
	assert(d_vector->num_of_elements > index);
	d_vector->elements[index] = (void*)item;
}



void *VectorGetElement(const d_vector_t *d_vector, size_t index)
{
	assert(NULL != d_vector);
	assert(d_vector->num_of_elements > index);
	return (d_vector->elements[index]);
}



size_t VectorGetSize(const d_vector_t *d_vector)
{
	assert(NULL != d_vector);
	return (d_vector->num_of_elements);
}



size_t VectorGetCapacity(const d_vector_t *d_vector)
{
	assert(NULL != d_vector);
	return (d_vector->capacity);
}


status_t VectorExpand(d_vector_t *d_vector, size_t total_size)
{
	void *ptr = NULL;
	assert(NULL != d_vector);
	
	ptr = realloc(d_vector->elements, total_size * sizeof(void*));
	if (NULL == ptr)
	{
		printf("Realloc failed");
		return (FAIL);
	}
	
	d_vector->elements = (void**)ptr;
	d_vector->capacity = total_size;
	
	return (SUCCESS);
}
	



status_t VectorShrink(d_vector_t *d_vector)
{
	assert(NULL != d_vector);
	
	d_vector->elements = realloc(d_vector->elements, d_vector->num_of_elements * sizeof(void*));
	d_vector->capacity = d_vector->num_of_elements;
	
	return (SUCCESS);
}	



