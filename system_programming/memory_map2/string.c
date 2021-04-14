#include<stdlib.h>/*malloc,free*/
#include<assert.h>/*assert*/
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

/************************************************/
int ToLower (char chr)
{
if(chr>64 && chr<91)
{
return(chr+32);
}
return(chr);
}

/************************************************/
int StrCaseCmp (const char * str1, const char *str2)
{
	int i=0;
	while(*(str1+i) && *(str2+i) && (ToLower(*(str1+i))==ToLower(*(str2+i))))
	{	
		i++;
	}
return(ToLower(*(str1+i))-ToLower(*(str2+i)));
}
		
/************************************************/	
	/*int i=0, i2=0, ans=0;
	char *str1dup= StrDup (str1);
	char *str2dup= StrDup (str2);

	
	while(*(str1dup+i) && *(str2dup+i))
	{
		if(*(str1dup+i)>64 && *(str1dup+i)<91)
		{
		*(str1dup+i)= *(str1dup+i)+32;
		}
		if(*(str2dup+i)>64 && *(str2dup+i)<91)
		{
		*(str2dup+i)= *(str2dup+i)+32;
		}
		i++;
	}


	for (i2=0;i2<i;i2++)
	{
		if(*(str1dup+i2)!=*(str2dup+i2))
		{
		ans=*(str1+i2)-*(str2+i2);
		free(str1dup);
		free(str2dup);
		return(ans);
		}
	}
	
	if(*(str1dup+i))
	{
		ans=*(str1+i);
		free(str1dup);
		free(str2dup);
		return(ans);
	}
	if(*(str2dup+i))
	{
		ans=-*(str2+i);
		free(str1dup);
		free(str2dup);
		return(ans);
	}
	
		free(str1dup);
		free(str2dup);
	return (0);
	
	}*/
/************************************************/
	
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

