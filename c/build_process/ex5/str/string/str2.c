#include<stdlib.h>/*malloc,free*/
#include<stddef.h>
#include<assert.h>/*assert*/
#include "string.h"

/************************************************/ 
 char *StrnCpy (char *dest, const char *src, size_t size)
{
	size_t i =0;
	while ((*src)&&(i<size))
	{
		*(dest+i)=*(src+i);
		i++;
	}
	while(i<size)
	{
		*(dest+i)='\0';
		i++;
	}
		*(dest+i)='\0';
	return(dest);
}

/************************************************/
char *StrDup(const char *s)
{
	size_t size =StrLen(s);
	char *ptr= (char*)malloc((size*(sizeof(char))));
	assert(NULL!=ptr);
	ptr= StrCpy(ptr, s);
	return((char*)ptr);
}

