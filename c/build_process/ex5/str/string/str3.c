#include<stdlib.h>/*malloc,free*/
#include<assert.h>/*assert*/
#include<stddef.h>
#include "string.h"

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
