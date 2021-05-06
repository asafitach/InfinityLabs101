#include <stdio.h>   /* printf */
#include <stdlib.h>   /* free remove later !!!! */

#include "trie.h"

/***********************color macros for printf*********************************/

#define RED "\033[1;31m"  /* print in red */

#define GREEN "\033[1;5;32m" /* print in green */

#define BLUE "\033[1;34m"  /* print in blue */

#define YELLOW "\033[1;4:1;33m" /* print in yellow  */

#define PURPLE "\033[1;35m" /* print in purple */

#define CYAN "\033[1;3;36m" /* print in cyan */

#define RESET "\033[0m" /* reset print color  */

/**********************************Test MACROs*********************************/

#define TEST_ARE_EQUAL(name, real, expected) printf("%s: %s\n", name, real == expected\
                                                                ? GREEN"SUCCESS\n"RESET\
                                                                : RED"\aFAILURE\n"RESET)

#define TEST_ARE_NOT_EQUAL(name, real, expected) printf("%s: %s\n", name, real != expected\
                                                                ? GREEN"SUCCESS\n"RESET\
                                                                : RED"\aFAILURE\n"RESET)  

#define NUM_OF_INPUT_BITES 4

#define CREATE_TRIE trie_t *trie = TrieCreate(NUM_OF_INPUT_BITES)

#define DESTROY_TRIE TrieDestroy(trie)

/********************* comment ***************************/

void TestTrieCreate(void);
void TestTrieInsert(void);
void TestTrieCount(void);
void TestTrieIsFound(void);
void TestTrieNextAvailable(void);

/********************* comment ***************************/

int main ()
{
   /*  TestTrieCreate(); */

    /* TestTrieCount(); */

/*     TestTrieInsert();
 */
   /*  TestTrieIsFound(); */

   TestTrieNextAvailable();
    
    return (0);
}

/********************* comment ***************************/

void TestTrieCreate(void)
{
    CREATE_TRIE;

    TEST_ARE_NOT_EQUAL("TestTrieCreate", trie, NULL);

    DESTROY_TRIE;

    return ;
}

void TestTrieInsert(void)
{
    CREATE_TRIE;

    size_t data = 5;

    TrieInsert(trie, data);

    TEST_ARE_EQUAL("TestTrieInsert", TrieCount(trie), 1);

    DESTROY_TRIE;

    return ;
}

void TestTrieCount(void)
{
    CREATE_TRIE;

    size_t data = 5;

    TrieInsert(trie, data);

    TEST_ARE_EQUAL("TestTrieCount", TrieCount(trie), 1);

    DESTROY_TRIE;

    return ;
}

void TestTrieIsFound(void)
{
    CREATE_TRIE;

    size_t data = 5;

    TrieInsert(trie, data);

    TEST_ARE_EQUAL("TestTrieIsFound", TrieIsFound(trie, data), 1);

    DESTROY_TRIE;

    return ;
}


void TestTrieNextAvailable(void)
{
    CREATE_TRIE;

    size_t req_data = 5;

    size_t *req_data_ptr = &req_data;

    size_t data = 5;

    TrieInsert(trie, data);

    if (PATH_OCCUPIED == TrieInsert(trie, req_data))
    {
        TEST_ARE_EQUAL("TestTrieNextAvailable1", TrieNextAvailable(trie, req_data_ptr), SUCCESS);

        printf("\n%lu\n", req_data);
        
        TrieInsert(trie, req_data);

    }

    TEST_ARE_EQUAL("TestTrieNextAvailable2", TrieIsFound(trie, req_data), 1);

    TEST_ARE_EQUAL("TestTrieNextAvailable3", TrieCount(trie), 2);

    DESTROY_TRIE;

    return ;
}

