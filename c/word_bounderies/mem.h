/*****************        Reviewed by Fei       **************************/

#ifndef __EX_H__
#define __EX_H__

#define WORD (8)
#define BYTE (256)

#include <stddef.h>

void *MemSet( void *src, int c, size_t n);
void *MemCpy(void *dest, const void * source, size_t n);
void *MemMove(void *str1, const void *str2, size_t n);



#endif /* __EX1_H__ */
