#include <stdlib.h>
#include <assert.h>
#include "cbuff.h"

#define PAD 7

struct cbuff
{
	size_t capacity;
	size_t write;
	size_t read;
	char data[1];
};

/******************************************************************************/

cbuff_t *CbuffCreate(size_t capacity)
{
	cbuff_t *cbuff = (cbuff_t *)malloc(sizeof(cbuff_t) + capacity - PAD);
	
	if (NULL == cbuff)
	{
		return (NULL);
	}
	
	cbuff->capacity = capacity;
	cbuff->write = 0;
	cbuff->read = 0;
	
	return (cbuff);
}

/******************************************************************************/

void CbuffDestroy(cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	
	free(cbuff);
	cbuff = NULL;
}

/******************************************************************************/

ssize_t CbuffRead(cbuff_t *cbuff, void * dest, size_t num_of_bytes)
{
	char tmp = 0;
	size_t index = 0;
	assert(cbuff != NULL);
	
	
	if (1 == CbuffIsEmpty(cbuff))
	{
		return (0);
	}
	
	while (num_of_bytes >  0 && (cbuff->read != cbuff->write))
	{
		tmp = cbuff->data[cbuff->read];
		*((char*)dest + index) = tmp;
		cbuff->read = (cbuff->read + 1) % cbuff->capacity;
		index++;
		num_of_bytes--;
	}
	
	if (num_of_bytes >  0)
	{
		tmp = cbuff->data[cbuff->read];
		*((char*)dest + index) = tmp;
		index++;
	}
	
	return (index);
}
	
/******************************************************************************/

ssize_t CbuffWrite(cbuff_t *cbuff, const void *src, size_t num_of_bytes)
{
	size_t index = 0;
	
	assert(NULL != cbuff);
	if (0 == num_of_bytes && 1 == CbuffIsEmpty(cbuff)) 
	{
		return(0);
	}
	
	if (1 == CbuffIsEmpty(cbuff))
	{
		cbuff->data[cbuff->write] = *((char *)src + index);
		index++;
		num_of_bytes--;
		cbuff->write++;	
			if (num_of_bytes == 0)
			{
				return (1);
			}		
		cbuff->data[cbuff->write] = *((char *)src + index);
		index++;
		num_of_bytes--;
	}	
	
			
	while (num_of_bytes > 0 && 0 < CbuffFreeSpace(cbuff))
	{
		cbuff->write = (cbuff->write + 1) % cbuff->capacity;
		cbuff->data[cbuff->write] = *((char *)src + index);
		index++;
		num_of_bytes--;
	}

	if (cbuff->read == cbuff->write)
	{
		cbuff->write = (cbuff->write == 0) ? cbuff->capacity: cbuff->write;
		cbuff->write--;
	}

	return (index);
}
		
/******************************************************************************/

size_t CbuffFreeSpace(const cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	return (cbuff->capacity -CbuffCountFull(cbuff));
}

/******************************************************************************/

size_t CbuffCountFull(const cbuff_t *cbuff)
{
	int count = cbuff->write - cbuff->read;

	assert(NULL != cbuff);
	
	if(0 == count)
	{
		return (0);
	}
	
	if(0 > count)
	{
		count = cbuff->capacity + count;
	}
	
	return (count + 1);
}

/******************************************************************************/

int CbuffIsEmpty(const cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	return ((cbuff->read == cbuff->write) ? 1 : 0);
}

/***********************************E.O.F**************************************/
