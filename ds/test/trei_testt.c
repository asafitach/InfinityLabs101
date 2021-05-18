#include <stdio.h> /*printf*/
#include <stdlib.h> /*calloc,free*/
#include <assert.h> /*assert*/

#include "trie.h"
#include "utilities.h"

void PrintTrie(trie_t *trie);

void TestCreateDestroy(void);
void TestInsertRemove(void);
void TestIsFound(void);
void TestNextAvailable(void);



void PrintTrie(trie_t *trie);

int main(void)
{
    TestCreateDestroy();
    TestInsertRemove();
    TestIsFound();
    TestNextAvailable();

    return(0);
}

void TestNextAvailable(void)
{
    size_t i  = 0;
    trie_t *trie = TrieCreate(4);

    
    size_t next = 1;
    int status = 0;

    printf(YELLOW"print test:\n"RESET);
    for(i = 0; i < 16; i++)
    {
        printf("test %ld : %d\n" ,i, TrieInsert(trie, i));
    }

    printf(YELLOW"Next Availble tests::\n"RESET);

    status = TrieNextAvailable(trie, &next);

    TEST_ARE_EQUAL("next available on a full trie", next,1);

    TEST_ARE_EQUAL("STATUS TRIE IS FULL", status,TRIE_FULL);

    next = 1;

        TrieInsert(trie, 1);

    TrieRemove(trie, 2);

    status = TrieNextAvailable(trie, &next);

    TEST_ARE_EQUAL("removed 2, find the next of 1 (2)", next,2);


    TEST_ARE_EQUAL("status test", status,0);

    TrieInsert(trie, 1);

    next = 2;

    TrieNextAvailable(trie, &next);

    TEST_ARE_EQUAL("request 2 (2 is available)", next,2);

    next = 3;

    status = TrieNextAvailable(trie, &next);


    TEST_ARE_EQUAL("request 3 : PATH_OCCUPIED", status ,PATH_OCCUPIED);
    printf("%lu   %d \n\n", next, status);

    TrieRemove(trie, 12);

    next = 5;
       printf("insert 4 status: %d ", TrieInsert(trie, 4));


    status = TrieNextAvailable(trie, &next);

    TEST_ARE_EQUAL("request 3 after removing 12, should get 12", next ,12);

    printf("%lu\n" ,next);

    next = 3;

    TrieRemove(trie, 11);

    status = TrieNextAvailable(trie, &next);


    TEST_ARE_EQUAL("request 3 after removing 11, should get 11", next ,11);

    TrieRemove(trie, 10);

    next = 3;
    status = TrieNextAvailable(trie, &next);

    TEST_ARE_EQUAL("request 3 after removing 10, should get 10", next ,10);

   printf("%lu\n" ,next);
    next = 3;
    TrieRemove(trie, 9);

    status = TrieNextAvailable(trie, &next);

    TEST_ARE_EQUAL("request 3 after removing 9, should get 9", next ,9);

   printf("%lu\n" ,next);

    next = 3;
    TrieRemove(trie, 4);

    status = TrieNextAvailable(trie, &next);

    TEST_ARE_EQUAL("request 3 after removing 4, should get 4", next ,4);
   printf("%lu\n" ,next);


}

void TestIsFound(void)
{
    trie_t *trie = TrieCreate(4);

    TrieInsert(trie, 14);

    printf(YELLOW"IsFound Tests\n"RESET);

    TEST_ARE_EQUAL("find 14", TrieIsFound(trie, 14), 1);
    TEST_ARE_EQUAL("find 15", TrieIsFound(trie, 15), 0);
    TEST_ARE_EQUAL("find 13", TrieIsFound(trie, 13), 0);
   
    TrieInsert(trie, 13);
    TEST_ARE_EQUAL("find 13", TrieIsFound(trie, 13), 1);


    TrieDestroy(trie);
}

void TestInsertRemove(void)
{
    size_t i = 0;
    trie_t *trie1 = TrieCreate(4);
    trie_t *trie2 = TrieCreate(4);

    trie_status_t status;

    printf(YELLOW"Insert&Remove Test\n"RESET);

    TEST_ARE_EQUAL("count 0 test", TrieCount(trie1), 0);
    

    for(i = 0; i < 15; i++)
    {
        TrieInsert(trie1, i);
    }


    TEST_ARE_EQUAL("count 15 test", TrieCount(trie1), 15);

    /*printf("%ld\n" ,TrieCount(trie1));*/

    TEST_ARE_EQUAL("insert 15", TrieInsert(trie1, 15), SUCCESS);

    TEST_ARE_EQUAL("count 16 test", TrieCount(trie1), 16);

    TEST_ARE_EQUAL("Trie Full Test", TrieInsert(trie1, 12), TRIE_FULL);

    TEST_ARE_EQUAL("count 16 test2 after full", TrieCount(trie1), 16);


    status = TrieInsert(trie2, 12);

    TEST_ARE_EQUAL("Insert 12 SUCCESS", status, SUCCESS);

    status = TrieInsert(trie2, 12);

    TEST_ARE_EQUAL("Insert 12 PATH_OCCUPIED", status, PATH_OCCUPIED);

    status = TrieInsert(trie2, 13);

    TEST_ARE_EQUAL("Insert 13 SUCCESS", status, SUCCESS);

    PrintTrie(trie2);


    printf(YELLOW"remove test\n"RESET);

    TEST_ARE_EQUAL("find 13 before remove", TrieIsFound(trie2, 13), 1);

    status = TrieRemove(trie2, 13);

    TEST_ARE_EQUAL("dont find 13 AFTER remove", TrieIsFound(trie2, 13), 0);

    status = TrieRemove(trie2, 13);

    PrintTrie(trie2);

    TEST_ARE_EQUAL("Insert 13 again", TrieInsert(trie2, 13), 0);



    TEST_ARE_EQUAL("Try to remove 13, status invalid path:", status, 3);


    TrieDestroy(trie1);
    TrieDestroy(trie2);

    return;
}

void TestCreateDestroy(void)
{
    trie_t *trie = TrieCreate(8);
    trie_status_t status = SUCCESS;
    size_t data = 0;

    printf(YELLOW"Create&Destroy Test\n"RESET);
    TEST_ARE_EQUAL("Create Test", (trie != NULL), 1);

    TrieInsert(trie, data);
    status = TrieNextAvailable(trie, &data);
    printf("%lu   %d\n\n", data, status);
    

    TrieDestroy(trie);

    return;
}







