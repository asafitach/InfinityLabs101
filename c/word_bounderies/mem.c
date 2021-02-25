/*****************        Reviewed by Fei       **************************/
#include <assert.h>
#include "mem.h"

# define WORD 8

size_t Chunk (size_t c)
{
  int i = 0;
  size_t num = 0;
 
  for(i=0; i < WORD; i++)
  {
    num <<= WORD;
    num |= c;
  }
  
  return(num);
}

void *MemSet(void *str, int c, size_t n)
{
	char *str_tmp =(char*) str;
	size_t chunk = Chunk((size_t)(c % BYTE));

	while(n)
	{
		if(((size_t)str_tmp % sizeof(size_t) != 0) || (n < sizeof(size_t)))
		{
			*(char*)str_tmp = c;
			n --;
			str_tmp ++;
		}
		else
		{
			*(size_t*)str_tmp = chunk;
			n -= WORD;
			str_tmp += WORD;
		}
	}
	
	return(str);
}


void *MemCpy(void *dest, const void * src, size_t n)
{
	char *ptr = (char*) dest;
	char *src_tmp = (char*) src;
	assert(ptr);
	assert(src_tmp);
	
	while(n)
	{
		if(n < WORD)
		{
			*(char*)(ptr) = *(src_tmp);
			src_tmp ++;
			ptr ++;
			n --;
		}
		else
		{
			*((size_t*)ptr) = *((size_t*)src_tmp);
			src_tmp += WORD;
			ptr += WORD;
			n -= WORD;
		}
	}
	return(dest);
}


void *MemMove(void *dest, const void *src, size_t n)
{
	char *ptr = (char*) dest;
	char *src_tmp = (char*) src;
	size_t new_n = (size_t)src_tmp-(size_t)dest;
	size_t size = 0;
	
	if((new_n > 0) && (new_n < n))
	{	
		while(n>WORD)
		{
			MemCpy(ptr, src_tmp, WORD);
			ptr += WORD;
			src_tmp += WORD;
			n -= WORD;
		}		
		MemCpy(ptr, src_tmp, n);
	}
	else
	{
		size = n % WORD; 
		if(0 != size)
		{
			MemCpy(ptr + n - size, src_tmp + n - size, size);
			n -= size; 
		}	
		while(n)
		{
			MemCpy(ptr + n - WORD, src_tmp + n - WORD, WORD);
			n -= WORD;
		} 
	}
	
	return (dest);
}










