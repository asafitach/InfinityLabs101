#include<stdlib.h>/*malloc,free*/
#include<assert.h>/*assert*/
#include<stddef.h>
#include "string.h" 


/************************************************/
int StrLen (const char *str)
{
	int count = 0;
	while(*(str+count))
	{
		count++;
	}
	return(count);
}

/************************************************/
char *StrCpy ( char *dest, const char *src)
{
    int count=0;
    while(*(src + count))
    {
        *(dest+ count)=*(src + count);
        count++;
    }
    *(dest + count)='\0';
    return( dest);
}

/************************************************/
char *StrChr(const char *str, int c)
{
	size_t i=0;

	while (*(str+i))
	{
		 if(*(str+i)==c)
		 {
		 	return((char*)(str+i));
		 }
		 i++;
	 }
	return (NULL);
 }

