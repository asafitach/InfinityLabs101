/*****************        Reviewed by Fei       **************************/
#include "mem.h"


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

void *MemSet(void *src, int c, size_t n)
{
	char *str =(char*) src;
	size_t chunk = Chunk((size_t)(c % BYTE));

	while(n)
	{
		if(((size_t)str % sizeof(size_t) != 0) || (n < sizeof(size_t)))
		{
			*(char*)str = c;
			n --;
			str ++;
		}
		else
		{
			*(size_t*)str = chunk;
			n -= WORD;
			str += WORD;
		}
	}
	
	return(src);
}

size_t WordChunk(char *src)
{
  int i = 0;
  size_t num = 0;
 
  for(i=0; i < WORD;  i++)
  {
    num <<= WORD;
    num |= (size_t)(*(src+WORD -i -1) % BYTE);
  }
  
  return(num);
}	


void *MemCpy(void *dest, const void * source, size_t n)
{
	char *ptr = (char*) dest;
	char *src = (char*) source;
	const size_t N = n;
	
	while(n)
	{
		if(((size_t)ptr % sizeof(size_t) != 0) || n < sizeof(size_t))
		{
			*(ptr) = *(src + N - n);
			ptr ++;
			n --;
		}
		else
		{
			*(size_t*)ptr = WordChunk(src + N - n);
			ptr += WORD;
			n -= WORD;
		}
	}
	return(dest);
}


void *MemMove(void *str1, const void *str2, size_t n)
{
	char *ptr = (char*) str1;
	char *src = (char*) str2;
	size_t new_n = (size_t)str2-(size_t)str1;
	size_t size = 0;
	
	if((new_n > 0) && (new_n < n))
	{
		MemCpy(str1, str2, new_n);
	}
	else
	{
		while(n)
		{
			size = (n > WORD) ? (WORD):(n);
			MemCpy(ptr + n - size, src + n - size, size);
			n -= size;
		} 
	}
	
	return (str1);
}










