#include <stdlib.h>/* malloc free */
#include <stdio.h>/* fgets */
#include <assert.h>/* assert */
#include <string.h> /* strlen */
#include <ctype.h> /*tolower*/
#include "dllist.h"
#include "hasht.h"

struct hashtable 
{
    dlist_t **hashtable_items; 
    hash_func_t hash_func;
    is_match_t is_match;
    size_t table_size;
};

dlist_t **CreateLists(dlist_t **array, size_t size);
void *ChacingData(dlist_t *list, dlist_iter_t go_to_front);
dlist_t *HashGetList(const hashtable_t *table, size_t index);

hashtable_t *HashtableCreate(size_t table_size, hash_func_t hash_func, is_match_t is_match)
{
    hashtable_t *table = NULL;

    assert(NULL != is_match);
    assert(NULL != hash_func);
    assert(0 != table_size);

    table = (hashtable_t *)malloc(sizeof(hashtable_t));
    if (NULL == table)
    {
        return (NULL);
    }

    table->hashtable_items = (dlist_t **)malloc(table_size * sizeof(dlist_t *));
    if (NULL == table->hashtable_items)
    {
        free(table);
        return (NULL);
    }

    if (NULL == CreateLists(table->hashtable_items, table_size))
    {
        free(table->hashtable_items);
        free(table);
        return (NULL);
    }

    table->hash_func = hash_func;
    table->table_size = table_size;
    table->is_match = is_match;

    return (table);
}


void HashtableDestroy(hashtable_t *table)
{
    size_t index = 0;
    size_t size = 0;

    assert(NULL != table);

    size = table->table_size;
    for (index = 0; index < size; ++index)
    {   
        DlistDestroy(HashGetList(table, index));   
    }

    free(table->hashtable_items);
    free(table);
    table = NULL;
}


status_t HashtableInsert(hashtable_t *table, void *data)
{
    size_t hash_index = 0;
    size_t hash_size = 0;

    assert(NULL != table);

    hash_size = table->table_size;
    hash_index = table->hash_func(data) % hash_size;
    if (NULL == DlistPushFront(HashGetList(table, hash_index), data))
    {
        return (FAIL);
    }

    return (SUCCESS);
}

void HashtableRemove(hashtable_t *table, void *data)
{
    size_t hash_index = 0;
    dlist_t *list = NULL;
    dlist_iter_t to_remove = NULL;

    assert(NULL != table);

    hash_index = table->hash_func(data) % table->table_size;
    list = HashGetList(table, hash_index);
    to_remove = DlistFindOne(DlistBegin(list), DlistEnd(list), table->is_match, data);
    if (DlistEnd(list) != to_remove)
    {
        DlistRemove(to_remove);
    }
}


size_t HashtableCount(const hashtable_t *table)
{
    size_t count = 0;
    size_t index = 0;
    dlist_t *list = NULL;
    
    assert(NULL != table);

    index = table->table_size;

    while (index)
    {
        list = HashGetList(table, index - 1);
        count += DlistSize(list);
        --index;
    }

    return (count);
}


void *HashtableFind(const hashtable_t *table, const void *data)
{
    dlist_t *list = NULL;
    dlist_iter_t found = NULL;
    size_t hash_index = 0;

    assert(NULL != table);

    hash_index = table->hash_func((void *)data) % table->table_size;
    list = HashGetList(table, hash_index);

    found = DlistFindOne(DlistBegin(list), DlistEnd(list), table->is_match, data);
    return ((found == DlistEnd(list)) ? NULL: ChacingData(list, found));
}

void *ChacingData(dlist_t *list, dlist_iter_t go_to_front)
{
    void *data = DlistGetData(go_to_front);
    DlistRemove(go_to_front);
    DlistPushFront(list, data);

    return (data);
}


int HashtableIsEmpty(const hashtable_t *table)
{
    size_t index = 0;
    size_t is_empty = 0;

    assert(NULL != table);

    index = table->table_size;
    do
    {
        --index;
        is_empty += DlistIsEmpty(HashGetList(table, index));
    }while (index);

    return ((is_empty == table->table_size) ? 1: 0);
}


int HashtableForeach(const hashtable_t *table, action_func_hash_t action_func, void *param)
{
    /*int res = 0;*/
    size_t index = 0;
    size_t elements = 0;
    dlist_t *list = NULL;
    dlist_iter_t node = NULL;

    assert(NULL != table);
    assert(NULL != action_func);

    index = table->table_size;
    while (index)
    {
        list = HashGetList(table, index - 1);
        elements = DlistSize(list);
        node = DlistBegin(list);
        while (0 != elements)
        {
            if (0 != action_func(DlistGetData(node), param))
            {
                return (1);
            }
            node = DlistNext(node);
            --elements;
        }
        --index;
    }
    return (0);
}


void HashtableLoadSpell(hashtable_t *table)
{
    FILE *fp = NULL;
    status_t status = SUCCESS;
    char *buff = NULL;/* !!! */

    fp = fopen("/usr/share/dict/words", "r");
    if (NULL == fp)
    {
        return ;
    }

    buff = (char *)malloc(48);
    while (NULL != fgets(buff, 48, fp) )
    {
        buff[strlen(buff) - 1] = '\0';
        if (NULL != buff && SUCCESS == status)
        {
            status = HashtableInsert(table, (void *)buff);
        }
        buff = (char *)malloc(48);
    }
    fclose(fp);

    return;
    
}

/*Description: The function returns the hashtable standard deviation.
@params: pointer to the hashtable.
@return: double for the standard deviation of the hashtable elements.
@errors:
*/
double HashSD(hashtable_t *table);

dlist_t **CreateLists(dlist_t **array, size_t size)
{
    size_t index = size;

    do
    {
        array[index - 1] = DlistCreate();
        --index;
    } while (index && NULL != array[index]);

    if (NULL != array[index])
    {
        return (array);
    }
    
    while(index != size)
    {
        free(array[index]);
        ++index;
    }
    
    return (NULL);
}

dlist_t *HashGetList(const hashtable_t *table, size_t index)
{
    return (table->hashtable_items[index]);
}

size_t HashFuncSum2Letter(const void *data)
{
    char *string = (char *)data;

    return ((size_t)(tolower(*string) + tolower((int)*(string + 1)) - 'a'));
}

int StrCmpVoid(void *data1, void *data2)
{
    return ((strcmp((char *)data1, (char *)data2) == 0) ? 1: 0);
}

/* */
void SpellChecker(int argc, char *argv[])
{
    hashtable_t *table = HashtableCreate(26 *27, HashFuncSum2Letter, StrCmpVoid);
    int index = 0;

    HashtableLoadSpell(table);

    for (index = 1; index < argc; ++index)
    {
        if (NULL == HashtableFind(table, (void *)argv[index]))
        {
            printf("%s >>>is not a word<<<\n", argv[index]);
        }
        else
        {
            printf("%s is a word\n", argv[index]);
        }
    }


}

