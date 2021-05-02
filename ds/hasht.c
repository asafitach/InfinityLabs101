#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/
#include "hasht.h"


struct hashtable 
{
    dlist_t **hashtable_items; 
    hash_func_t hash_func;
    is_match_t is_match;
    size_t table_size;
};

size_t GetIndex(hashtable_t *table, void *data)
{
    return (table->hash_func(data) % table->table_size);
}

dlist_iter_t FindDlist(hashtable_t *table, dlist_t *dlist,  void *data)
{
    return DlistFindOne(DlistBegin(dlist), DlistEnd(dlist), table->is_match, data);
}

/*****************************************************************************/

hashtable_t *HashtableCreate(size_t table_size, hash_func_t hash_func, is_match_t is_match)
{
    size_t i = 0;
    hashtable_t *hasht = (hashtable_t *)malloc(sizeof(hashtable_t));
    if (NULL == hasht)
    {
        return NULL;
    }

    hasht->hashtable_items = (dlist_t**)malloc(sizeof(dlist_t*) * table_size);
    if (NULL == hasht->hashtable_items)
    {
        free(hasht);
        return NULL;
    }
    hasht->hash_func = hash_func;
    hasht->is_match = is_match;
    hasht->table_size = table_size;

    for (i = 0; i < table_size; ++i)
    {
        hasht->hashtable_items[i] = DlistCreate();
        if (NULL == hasht->hashtable_items)
        {
           hasht->table_size = i - 1;
           HashtableDestroy(hasht);
           return NULL;
        }
    }
    
    return hasht;
}

/*****************************************************************************/

void HashtableDestroy(hashtable_t *hash_table)
{
    size_t i = 0;
    
    for (i = 0; i < hash_table->table_size ; ++i)
    {
        DlistDestroy(hash_table->hashtable_items[i]);
    }

    free(hash_table->hashtable_items);
    hash_table->hashtable_items = NULL;
    free(hash_table);
}

/*****************************************************************************/

status_t HashtableInsert(hashtable_t *table, void *data)
{
    size_t index = 0;
    dlist_iter_t dummy = NULL;
    assert(NULL != table);
    
    index = GetIndex(table, data);
    dummy = DlistEnd(table->hashtable_items[index]);
    return dummy == DlistPushFront(table->hashtable_items[index], data) ? SUCCESS : FAIL;
}

/*****************************************************************************/

size_t HashtableCount(const hashtable_t *table)
{
    size_t i = 0;
    size_t count = 0;
    assert(NULL != table);

    for (i = 0; i < table->table_size; ++i)
    {
        count += DlistSize(table->hashtable_items[i]);
    }
    return count;
}

/*****************************************************************************/

int HashtableIsEmpty(const hashtable_t *table)
{
    assert(NULL != table);
    return (0 == HashtableCount(table) ? 1 : 0); 
}

/*****************************************************************************/

void HashtableRemove(hashtable_t *table, void *data)
{
    size_t index = 0;
    dlist_iter_t to_remove = NULL;
    dlist_t *dlist = NULL;
    dlist_iter_t dummy = NULL;
    assert(NULL != table);

    index = GetIndex(table, data);
    dlist = table->hashtable_items[index];
    to_remove = FindDlist(table, dlist, data);
    dummy = DlistEnd(table->hashtable_items[index]);
    
    if (dummy != to_remove)
    {
        DlistRemove(to_remove);    
    }
}

/*****************************************************************************/

void *HashtableFind(const hashtable_t *table, const void *data)
{
    size_t index = 0;
    void *found = NULL;
    dlist_iter_t begin = NULL;
    dlist_iter_t end = NULL;
    void *return_data = NULL;

    assert(NULL != table);

    index = GetIndex((void*)table, (void*)data);
    begin = DlistBegin(table->hashtable_items[index]);
    end = DlistEnd(table->hashtable_items[index]);
    found = DlistFindOne(begin, end, table->is_match, data); 
    if (found == end)
    {
        return NULL;
    }
    
    /* caching */
    return_data = DlistGetData(found);
    DlistRemove(found);
    HashtableInsert((hashtable_t *)table, return_data);
    
    return return_data;   
}

/*****************************************************************************/

int HashtableForeach(const hashtable_t *table, action_func_t action_func, void *param)
{
    size_t i = 0;
    dlist_iter_t begin = NULL;
    dlist_iter_t end = NULL;
    dlist_t *curr_list = NULL;
    int status = 0;

    assert(NULL != table);

    for (i = 0; i < table->table_size && 0 == status; ++i)
    {
        curr_list = table->hashtable_items[i];
        begin = DlistBegin(curr_list);
        end = DlistEnd(curr_list);
        status = DlistForeach(begin, end, action_func, param);
    }

    return status;
}

/*****************************************************************************/
