#include<stdlib.h>/*malloc,free*/
#include<stddef.h>
#include<assert.h>/*assert*/
#include "string.h"
	
char *StrCat(char *dest, const char *src)
{
	int size= StrLen(src);
	int i=0;
	while(*(src+i))
	{
		*(dest+size+i)=*(src+i);
		i++;
	}
	return(dest);
}
/************************************************/

char *StrnCat(char *dest, const char *src, int num)
{
	int size= StrLen(src);
	int i=0;
	while(*(src+i) && i<num-1)
	{
		*(dest+size+i)=*(src+i);
		i++;
	}
	*(dest+size+i+1)='\0';
	return(dest);
}

/************************************************/

char *StrStr(const char *haystack, const char *needle)
{
	int len_hay=StrLen(haystack);
	int len_needle=StrLen(needle);
	int i=0, j=0, flag=1;
	
	for(i=0; i<len_hay-len_needle;i++)
	{	
	flag=1;
		for(j=0;j<len_needle-1;j++)
		{
			if(*(haystack+i+j)!=*(needle+j))
			{
				flag=0;
			}
		}
		if (flag)
		{
			return((char*)haystack+i);
		}
	
	}
	
	return (NULL);
}

/************************************************/

size_t StrSpn(const char *str1, const char *str2)
{
	size_t len_str1=StrLen(str1);
	size_t len_str2=StrLen(str2);
	size_t i=0, j=0, count=0;
	
	for(i=0; i<len_str1;i++)
	{	
		for(j=0;j<len_str2;j++)
		{
			if(*(str1+i)==*(str2+j))
			{
				count++;
				j=len_str2;
			}
		}

	
	}
	
	return (count);
}


/***************************EOF******************/

