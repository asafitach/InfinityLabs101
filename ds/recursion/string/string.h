#ifndef __STRING_H__
#define __STRING_H__

size_t Strlen(char *string);

size_t StrCmp(char *string1, char *string2);

char* StrCpy(char* destination, const char* source);

char *StrCat(char *destination, const char *source);

char *StrStr(const char *haystack, const char *needle);

#endif /* __STRING_H__ */
