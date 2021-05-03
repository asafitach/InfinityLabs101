#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include "utility.h"
#include "avl.h"


#define RED "\033[1;31m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void Test(); 

int main()
{
    system("clear");
    
    Test(); 
    
    return 0; 
}

int IntCmpFuncTest(const void *data1, const void *data2)/*return LEFT == 0 RIGHT == 1 EQUAL == 0*/
{
	return ((*((int *)data1) - *((int *)data2) > 0) ? 0: (*((int *)data1) - *((int *)data2) < 0) ? 1: -1);
}

void Test()
{
    avl_t *tree = AvlCreate(IntCmpFuncTest);
    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int five = 5;
    int six = 6;
    int seven = 7;

    printf(CYAN"\tTest \n\n"WHITE); 
    
    TEST("create  ", (tree != NULL) , 1); 
    
    TEST("is empty when empty  ", AvlIsEmpty(tree) , 1); 
    
    TEST("size when empty  ", AvlSize(tree) , 0); 

    TEST("height when empty  ", AvlHeight(tree) , 0); 

    TEST("insert", AvlInsert(tree, (void *)&one), SUCCESS);

    TEST("insert", AvlInsert(tree, (void *)&two), SUCCESS);

    TEST("insert", AvlInsert(tree, (void *)&three), SUCCESS);

    TEST("insert", AvlInsert(tree, (void *)&four), SUCCESS);

    TEST("insert", AvlInsert(tree, (void *)&five), SUCCESS);

    TEST("insert", AvlInsert(tree, (void *)&six), SUCCESS);

    TEST("insert", AvlInsert(tree, (void *)&seven), SUCCESS);

    TEST("foreach in order", AvlForeach(tree, PrintInt, (void *)&seven, INORDER), 0);

    TEST("foreach pre order", AvlForeach(tree, PrintInt, (void *)&seven, PREORDER), 0);

    TEST("foreach post order", AvlForeach(tree, PrintInt, (void *)&seven, POSTORDER), 0);

    printf("--------------------> mirror tree <--------------------\n");
    MirrorTree(tree);

    TEST("foreach in order", AvlForeach(tree, PrintInt, (void *)&seven, INORDER), 0);

    TEST("foreach pre order", AvlForeach(tree, PrintInt, (void *)&seven, PREORDER), 0);

    TEST("foreach post order", AvlForeach(tree, PrintInt, (void *)&seven, POSTORDER), 0);

    printf("--------------------> mirror tree <--------------------\n");
    MirrorTree(tree);

    TEST("find (success)", AvlFind(tree, (const void *)&two), (void *)&two);

    TEST("remove", AvlRemove(tree, (const void *)&two), SUCCESS);

    TEST("dont find", AvlFind(tree, (const void *)&two), NULL);

    TEST("height (3)  ", AvlHeight(tree) , 3); 

    TEST("size (6)  ", AvlSize(tree) , 6); 

    printf(CYAN"\tEnd Test \n\n"WHITE); 

    AvlDestroy(tree);
}











