#ifndef __TRIE_H__
#define __TRIE_H__

#include <stddef.h>  /* size_t */

typedef struct trie trie_t;

typedef struct trie_node trie_node_t;

typedef enum trie_status
{
    SUCCESS = 0,
    MALLOC_FAIL,
    PATH_OCCUPIED,
    PATH_INVALID,
    TRIE_FULL
} trie_status_t;


/**********************************************************************/

/*Description: 
@return: 
@errors:  
*/
trie_t *TrieCreate(size_t num_of_input_bits);

/*Description: 
@return: 
@errors:  
*/
void TrieDestroy(trie_t *trie); 

/*Description: 
@return: 
@errors:  
*/
trie_status_t TrieInsert(trie_t *trie, size_t data);

/*Description: 
@return: 
@errors:  
*/
trie_status_t TrieRemove(trie_t *trie, size_t data);

/*Description: 
@return: 
@errors:  
*/
int TrieIsFound(const trie_t *trie, size_t data); 

/*Description: 
@return: 
@errors:  
*/
size_t TrieCount(const trie_t *trie);

/*Description: 
@return: 
@errors:  
*/
trie_status_t TrieNextAvailable(const trie_t *trie, size_t *data);



#endif /* __TRIE_H__ */