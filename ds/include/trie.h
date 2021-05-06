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

/*Description: the function creates a trie ds.
@return: return pointer to trie ds.
@errors:  MALLOC FAIL return NULL.
*/
trie_t *TrieCreate(size_t num_of_input_bits);

/*Description: the function destroy a trie ds.
@return: void
@errors: N/A
*/
void TrieDestroy(trie_t *trie); 

/*Description: the function insert a new node to a trie ds.
@return: trie_status_t
@errors: MALLOC_FAIL
*/
trie_status_t TrieInsert(trie_t *trie, size_t data);

/*Description: the function removes a node in a trie ds.
@return: trie_status_t
@errors:  N/A
*/
trie_status_t TrieRemove(trie_t *trie, size_t data);

/*Description: the function finds a data in a trie ds.
@return: 1 if find, 0 if not.
@errors: N/A
*/
int TrieIsFound(const trie_t *trie, size_t data); 

/*Description: the function returns the number of datas in a trie ds.
@return: number of datas
@errors: N/A
*/
size_t TrieCount(const trie_t *trie);

/*Description: the function returns the next avlaiable data that\
is most similar to the requsted data in a trie ds.
@return: trie_status_t
@errors: MALLOC_FAIL
*/
trie_status_t TrieNextAvailable(const trie_t *trie, size_t *data);



#endif /* __TRIE_H__ */