/*****************        Reviewed by Rachel       **************************/

#ifndef __EX3_H__
#define __EX3_H__

#include <stdint.h>/* uint16_t */


#define IS_LITTLE_ENDIAN  (*(uint16_t *)"\0\xff" != 0)


typedef enum {
LITTLE, 
BIG
}endian;

int IsLittleEndian();

#endif /* __EX2_H__ */

