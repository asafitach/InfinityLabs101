#ifndef __HASHT_H__
#define __HASHT_H__

#include <stddef.h>  /* size_t */
/*#include "utility.h"
*/
typedef enum status
{
	SUCCESS = 0,
	FAIL = 1
} status_t;


typedef struct hashtable hashtable_t;

typedef size_t (*hash_func_t)(const void *key);
typedef int (*action_func_hash_t)(void *key, const void *param);
typedef int (*is_match_t)(void *data1, void *data2);


/* Description: The function creates a new hashtable.
@return: pointer to the new hashtable.
@errors: malloc failure. */  
hashtable_t *HashtableCreate(size_t table_size, hash_func_t hash_func, is_match_t is_match);


/* Description: The function frees all the elements in the hashtable and destroys the hashtable management struct.
@params: pointer to the hashtable management struct. */
void HashtableDestroy(hashtable_t *hash_table);


/* Description: The functions inserts a new element to the hashtable.
@params: pointer to the hashtable and data to insert.
@return: status_tdlist_iter_t
@errors: malloc failure. */
status_t HashtableInsert(hashtable_t *table, void *data);


/* Description: The function removes an item from the hashtable.
@params: pointer to the hashtable and data to remove.
@return: void.
@errors: */
void HashtableRemove(hashtable_t *table, void *data);


/* Description: The function returns the number of items stored in the hashtable.
@params: pointer to the hashtable.
@return: The function returns the number of items in the hashtable.
@errors: */
size_t HashtableCount(const hashtable_t *table);


/* Description: The function searches for the given element in the hashtable.
@params: pointer to the hashtable.
@return: void *data to the data if found, else NULL.
@errors: */
void *HashtableFind(const hashtable_t *table, const void *data); 


/* Description: The function checks if hashtable is currently empty. 
@params: pointer to the hashtable.
@return: BOOLEAN
@errors: */
int HashtableIsEmpty(const hashtable_t *table);


/*Description: The function invokes the provided action function for all the elements in the hashtable. 
@params: function pointer and void *param.
@return: int, 0 for success, 1 if one of the actions has failed.
@errors: */
int HashtableForeach(const hashtable_t *table, action_func_hash_t action_func, void *param);


/*Description: The function returns the hashtable load.
@params: pointer to the hashtable.
@return: double for the load of the hashtable.
@errors:
*/
double HashtableLoad(hashtable_t *table);

/*Description: The function returns the hashtable standard deviation.
@params: pointer to the hashtable.
@return: double for the standard deviation of the hashtable elements.
@errors:
*/
double HashSD(hashtable_t *table);

void HashtableLoadSpell(hashtable_t *table);

void SpellChecker(int argc, char *argv[]);

#endif /* __HASHT_H__ */

