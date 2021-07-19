#ifndef __STRING_H__
#define __STRING_H__

#include<stddef.h>

int StrLen (const char *str);
char *StrCpy ( char *dest, const char *src);
char *StrChr(const char *str, int c);
char *StrnCpy (char *dest, const char *src, size_t size);
char *StrDup(const char *s);
int StrCaseCmp (const char * str1, const char *str2);
char *StrCat(char *dest, const char *src);
int ToLower (char chr);
char *StrnCat(char *dest, const char *src, int num);
char *StrStr(const char *haystack, const char *needle);
size_t StrSpn(const char *str1, const char *str2);

#endif /* __STRING_H__ */
