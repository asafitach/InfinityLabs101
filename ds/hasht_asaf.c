#include <stdlib.h>     /* CR: by convention, you need to write the funcs you used from each lib */
#include <stdio.h>
#include <assert.h>
#include "dllist.h"
#include "hasht.h"

#include "utility.h"

struct hashtable 
{
    dlist_t **hashtable_items; 
    hash_func_t hash_func;
    is_match_t is_match;
    size_t table_size;
};

dlist_t **CreateLists(dlist_t **array, size_t size);

hashtable_t *HashtableCreate(size_t table_size, hash_func_t hash_func, is_match_t is_match)
{
    hashtable_t *table = (hashtable_t *)malloc(sizeof(hashtable_t));
    if (NULL == table)
    {
        return (NULL);
    }

    /* CR: if the asserts wont pass, the malloc wont be free, its better to allocate memory 
            after the asserts */

    assert(NULL != is_match);
    assert(NULL != hash_func);
    assert(0 != table_size);

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
        if (NULL != table->hashtable_items[index])
        {
            DlistDestroy(table->hashtable_items[index]);
        }
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

/* CR: Gil said that geting the right list should be in a separate func as it is used in 
        several different places */

    hash_size = table->table_size;
    hash_index = table->hash_func(data) % hash_size;
    if (NULL == DlistPushFront(table->hashtable_items[hash_index], data))
    {
        return (FAIL);
    }

    return (SUCCESS);
}

void HashtableRemove(hashtable_t *table, void *data)/*what should*/
{
    size_t hash_index = 0;
    dlist_t *list = NULL;

    assert(NULL != table);

    hash_index = table->hash_func(data) % table->table_size;
    list = table->hashtable_items[hash_index];
    DlistRemove(DlistFindOne(DlistBegin(list), DlistEnd(list), table->is_match, data));
}


size_t HashtableCount(const hashtable_t *table)
{
    size_t count = 0;
    size_t index = 0;
    dlist_t *list = NULL;
    
    assert(NULL != table);

    index = table->table_size;

/* CR: if youre using indices, why not use for loop ? */ 

    while (index)
    {
        list = table->hashtable_items[index - 1];
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
    list = table->hashtable_items[hash_index];

    found = DlistFindOne(DlistBegin(list), DlistEnd(list), table->is_match, data);
    return ((found == DlistEnd(list)) ? NULL: ChacingData(list, found));
}

/* CR: you need to pop the node from its place in the list before you can push it back */

void *ChacingData(dlist_t *list, dlist_iter_t go_to_front)
{
    void *data = DlistGetData(go_to_front);
    DlistPushFront(list, data);

    return (data);
}

/* CR: you wrote Size, why not use it? */

int HashtableIsEmpty(const hashtable_t *table)
{
    size_t index = 0;
    int is_empty = 0;

    assert(NULL != table);

    index = table->table_size;
    do
    {
        --index;
        is_empty += DlistIsEmpty(table->hashtable_items[index]);
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
        /* CR: dlist has its own foreach, you could traverse the table and use it. 
               it wont save the time, but it looks better */

        list = table->hashtable_items[index - 1];
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


/*Description: The function returns the hashtable load.
@params: pointer to the hashtable.
@return: double for the load of the hashtable.
@errors:
*/

/* CR: I dont understand what you tried to do here. Load factor is a value of 
        num of elements / num of keys. where did you defined BUFF_SIZE? 
        I think all of that should have been in the test, as it is something the 
        user will wont to do, and not part of the library */

double HashtableLoad(hashtable_t *table)
{
    FILE *fp = NULL;
    char buff[BUFF_SIZE] = {0};

    fp = fopen("/usr/share/dict/words", "r");
    if (NULL == fp)
    {
        return (0.0);
    }

    while (fp != NULL)
    {
        buff = fgets(buff, BUFF_SIZE, fp);
        HashtableInsert(table, (void *)buff);
    }
    
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
