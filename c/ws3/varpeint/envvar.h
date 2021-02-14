#ifndef __VARPRINT_H__
#define __VARPRINT_H__

#include<stddef.h>

size_t Count(char **arr);
void ArrayOfEnvVar(char **dest, char **src);
void ToLowerToAll(char **env_arr, size_t size);
void PrintAll(char **env_arr, size_t size);
void Free(char **multi_arr, size_t size);

#endif /* __VARPRINT_H__ */
