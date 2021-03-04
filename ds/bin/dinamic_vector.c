#include <stddef.h>/*size_t*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include "d_vector.h"

# define GROWTH_RATIO 2

struct d_vector 
{
	size_t num_of_elements;
	size_t capacity;
	void **elements;
};


d_vector_t *VectorCreate(size_t init_capacity)
{
	d_vector_t *d_vector = (d_vector_t*) malloc(sizeof(d_vector_t));
	if (d_vector == NULL)
	{
		return NULL; 
	}
	
	d_vector->num_of_elements = 0; 
	d_vector->capacity = init_capacity; 
	d_vector->elements = (void **) malloc((d_vector->capacity) * sizeof(void *)); 
	if (d_vector->elements == NULL)
	{
		free(d_vector); 
		return NULL; 
	}
	
	return d_vector; 	
}


void VectorDestroy(d_vector_t *d_vector)
{
	assert(d_vector); 
	
	free(d_vector->elements); 
	d_vector->elements = NULL; 
	
	free(d_vector); 
	d_vector = NULL; 
}


void VectorPopBack(d_vector_t *d_vector)
{
	assert(d_vector); 
	assert(d_vector->num_of_elements > 0); 
	d_vector->num_of_elements--; 
}


status_t VectorPushBack(d_vector_t *d_vector, const void *item)
{
	status_t status = 0; 
	assert(d_vector); 
	
	if(d_vector->num_of_elements == d_vector->capacity)
	{
		VectorExpand(d_vector, (d_vector->capacity) * GROWTH_RATIO); 
		
		if (status)
		{
			return FAIL; 
		}
	}
	
	d_vector->elements[d_vector->num_of_elements++] = (void *)item; 
	return SUCCESS; 
}


status_t VectorExpand(d_vector_t *d_vector, size_t total_size)
{
	void **tmp_elements = NULL; 
	
	assert(d_vector); 
	
	tmp_elements = realloc(d_vector->elements, sizeof(void *) * total_size); 
	
	if (tmp_elements)
	{
		d_vector->elements = tmp_elements; 
		d_vector->capacity = total_size; 
		return SUCCESS; 
	}

	return FAIL; 
}


void VectorSetElement(const d_vector_t *d_vector, size_t index, const void *item)
{
	assert(d_vector); 
	assert(d_vector->num_of_elements > index); 
	
	d_vector->elements[index] = (void *)item; 
}


void *VectorGetElement(const d_vector_t *d_vector, size_t index)
{
	assert(d_vector); 
	assert(d_vector->num_of_elements > index); 
	
	return d_vector->elements[index]; 
}


size_t VectorGetSize(const d_vector_t *d_vector)
{
	assert(d_vector); 
	return d_vector->num_of_elements; 
}


size_t VectorGetCapacity(const d_vector_t *d_vector)
{
	assert(d_vector); 
	return d_vector->capacity; 
}


status_t VectorShrink(d_vector_t *d_vector)
{
	assert(d_vector); 
	return VectorExpand(d_vector, VectorGetSize(d_vector)); 
}


