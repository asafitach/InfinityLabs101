#include <assert.h>   /* assert */
#include <stddef.h>   /* NULL */
#include <string.h>   /* strncmp */


/********************* StrLen ***************************/

size_t Strlen(char *string)
{
    if (0 == *string)
    {
        return(0);
    }
    return (Strlen(string + 1) + 1);
}

/********************* StrCmp ***************************/

size_t StrCmp(char *string1, char *string2)
{
    if (*string1 == *string2 && 0 != *string1)
    {
        return (StrCmp(string1 + 1, string2 + 1));
    }
    return (*string1 - *string2);
}

/********************* StrCpy ***************************/

char* StrCpy(char* destination, const char* source)
{
    if (0 != *source)
    {
        StrCpy(destination + 1, source + 1);
    }
    
    *destination = *source;
    return (destination);
}

/********************* StrCat ***************************/

char *StrCat(char *destination, const char *source)
{
    if (0 != *source)
    {
        *(destination + strlen(destination)) = *source;
        return(StrCat(destination, source + 1));
    }
    return (destination);
}

/********************* StrStr ***************************/

char *StrStr(const char *haystack, const char *needle)
{
    if ('\0' != *haystack && NULL != haystack)
    {
        if (0 == strncmp((char *)haystack, (char *)needle, strlen(needle)))
        {
            return ((char *)haystack);
        }
        return(StrStr(haystack + 1, needle));
    }
    return (NULL);
}
/********************* E.O.F. ***************************/

