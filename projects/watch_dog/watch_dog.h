#ifndef __WATCH_DOG_H__
#define __WATCH_DOG_H__

#include <stddef.h>  /* size_t */





/*Description: The function creates watch dog (one in this proc and an other on different proc).
@return: 1 if succeded.
@errors: NA.
*/
int WatchDogStart();


/*Description: The function creates a avl_t *tree data structure.
@return: The function returns a pointer to avl_t *tree.
@errors: Returns NULL if malloc fails.
*/
int WatchDogStop();



#endif /* __WATCH_DOG_H__ */
