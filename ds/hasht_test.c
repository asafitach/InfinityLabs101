#include <stdio.h> /*printf*/
#include <stdlib.h> /*calloc,free*/
#include <assert.h> /*assert*/
#include <string.h> /*strcmp*/
#include <ctype.h> /*tolower*/


#include "hasht.h"
#include "dllist.h"
#include "utilities.h"

size_t HashByFirstLetter(const void *key);

int PrintWord(void *key, const void *param);

int IsStringMatch(void *data1, void *data2);

void TestCreateDestroy(void);

void TestInsertRemove(void);

void TestSize(void);

void TestForeach(void);

void SpellChecker(int argc, char *argv[]);


int main(int argc, char *argv[])
{

    SpellChecker(argc, argv);

    TestCreateDestroy();

    TestInsertRemove();

    TestSize();

    TestForeach();


    return (0);
}


void TestForeach(void)
{
    hashtable_t *my_table = HashtableCreate(26, HashByFirstLetter, IsStringMatch);

    char data1[] = "Saggi";

    char data2[] = "NotSaggi";

    HashtableInsert(my_table, data1);

    HashtableInsert(my_table, data2);

    HashtableInsert(my_table, "walla");

    HashtableInsert(my_table, "wualla");

    HashtableInsert(my_table, "dov");

    HashtableInsert(my_table, "kuala");

    printf(YELLOW"foreach print test:\n"RESET);

    HashtableForeach(my_table,PrintWord,(void *)NULL);

    HashtableRemove(my_table,"kuala");

    printf(YELLOW"foreach print test after removed kuala:\n"RESET);


    HashtableForeach(my_table,PrintWord,(void *)NULL);



    HashtableDestroy(my_table);

    return;

}

void TestSize(void)
{
    hashtable_t *my_table = HashtableCreate(26, HashByFirstLetter, IsStringMatch);

    char data1[] = "Saggi";

    char data2[] = "NotSaggi";

    TEST_ARE_EQUAL("size0 test", HashtableCount(my_table) , 0);

    TEST_ARE_EQUAL("Isempty test 1", HashtableIsEmpty(my_table) ,1);


    HashtableInsert(my_table, data1);

    TEST_ARE_EQUAL("size1 test", HashtableCount(my_table) , 1);

    TEST_ARE_EQUAL("Isempty test 0", HashtableIsEmpty(my_table) ,0);


    HashtableInsert(my_table, data2);

    TEST_ARE_EQUAL("Isempty test 0", HashtableIsEmpty(my_table) ,0);


    TEST_ARE_EQUAL("size2 test", HashtableCount(my_table) , 2);

    HashtableDestroy(my_table);


}

void TestInsertRemove(void)
{
    hashtable_t *my_table = HashtableCreate(26, HashByFirstLetter, IsStringMatch);

    char data1[] = "Saggi";

    char data2[] = "NotSaggi";


    HashtableInsert(my_table, data1);

    TEST_ARE_EQUAL("Insert+Find Test1", HashtableFind(my_table, data1),data1);

    TEST_ARE_EQUAL("Insert+Find Test2", HashtableFind(my_table, data2),NULL);

    HashtableRemove(my_table, data1);

    TEST_ARE_EQUAL("Remove test 1", HashtableFind(my_table, data1),NULL);


    HashtableDestroy(my_table);


}

void TestCreateDestroy(void)
{
    hashtable_t *my_table = HashtableCreate(26, HashByFirstLetter, IsStringMatch);

    TEST_ARE_EQUAL("test create", (my_table == NULL) , 0);

    HashtableDestroy(my_table);

    return;
}

/*********************HASHFUNCs***************************************************************/
size_t HashByFirstLetter(const void *key)
{
    char *first_char_ptr = (void *) key;
    int first_char = tolower((int)*first_char_ptr) - 'a';

    return first_char;
}


int IsStringMatch(void *data1, void *data2)
{
    return(!strcmp((char *)data1, (char *)data2));
}


int PrintWord(void *key, const void *param)
{
    param = param;

    printf("%s\n" ,(char *)key);

    return 0;
}



size_t TwoDigitsSum(const void *data)
{
    char *string = (char *)data;

    return ((size_t)(tolower(*string) + tolower((int)*(string + 1)) - 'a'));
}

int StrLenVoid(void *data1, void *data2)
{
    return ((strcmp((char *)data1, (char *)data2) == 0) ? 1: 0);
}

void SpellChecker(int argc, char *argv[])
{
    hashtable_t *table = HashtableCreate(26 *27, TwoDigitsSum, StrLenVoid);
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