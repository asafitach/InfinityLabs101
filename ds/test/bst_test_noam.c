#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include <string.h>

#include "utility.h"

#include "bst.h"

#define SIZE 20

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"RESET : RED"Fail"RESET)
#define NOT_TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual != expected ? GREEN"Pass"RESET : RED"Fail"RESET)
    					/* Function Declaration */

int CmpInt(const void *data1, const void *data2, const void *param);
int CmpStr(const void *data1, const void *data2, const void *param);
static void TestI();
static void TestII();
static void TestForEach();
int SumInts(void *data, void *sum);

/*****************************************************************************/


int main()
{
    TestI();
    TestII();
    TestForEach();
    return 0; 
}

int CmpInt(const void *data1, const void *data2, const void *param)
{
	param = param;
	return (*(int *)&data2 - *(int *)&data1);
}

int CmpStr(const void *data1, const void *data2, const void *param)
{
	param = param;
	return (strcmp((char *)data2, (char *)data1));
}

int SumInts(void *data, void *sum)
{
    int *curr_sum = (int*)sum;
    *curr_sum += *(int*)data;
    
    return 0;
}

static void TestI()
{
    bst_iter_t root = NULL;
    bst_iter_t find_data = NULL;
    bst_iter_t end = NULL;
    bst_iter_t begin = NULL;
    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int five = 5;
    int six = 6;
    int seven = 7;
    int nine = 9;
    int ten = 10;
    size_t index =0;
    int *data = NULL;

    bst_t *tree = BstCreate(&CmpInt, (void *)6);
    printf(CYAN"\n\tTest I\n\n"RESET); 
    
    NOT_TEST("BstCreate", tree, NULL);
    TEST("IsEmpty", BstIsEmpty(tree), 1);
    TEST("Size (0)", BstSize(tree), 0);
    
    TEST("BstEnd == BstBegin", BstEnd(tree), BstBegin(tree));

    root = BstInsert(tree, &six);    
    BstInsert(tree, &one);
    BstInsert(tree, &two);
    BstInsert(tree, &three);
    BstInsert(tree, &five);
    BstInsert(tree, &nine);
    BstInsert(tree, &seven);
    BstInsert(tree, &four);
    
    printf("BstInsert: 6, 1, 2, 3, 5, 9, 7, 4\n");
    /*Print2DInt(root, 0);*/
    begin = BstBegin(tree);
        for (index = 1; index < 9; ++index)
    {
        data = (int *)BstGetData(begin);
        printf(" %d ", *data);
        begin = BstNext(begin);
    }
    TEST("Size (8)", BstSize(tree), 8);
    
    

    find_data = BstFind(tree, &seven);
    NOT_TEST("BstFind (7)", find_data, NULL);
    find_data = BstFind(tree, &ten);
    TEST("BstFind (10)", find_data, NULL);

    TEST("IsEmpty", BstIsEmpty(tree), 0);
    begin = BstBegin(tree);
    TEST("BstBegin -> GetData (1)", *(int *)BstGetData(begin), (int)1);
    
    end = BstEnd(tree);
    end = BstPrev(end);
    end = BstPrev(end);
    end = BstPrev(end);
    BstRemove(end);
    printf("BstRemove of 6\n");
    Print2DInt(root, 0);

    BstDestroy(tree);
    printf(CYAN"\n\tEnd Test I\n\n"RESET); 
}


static void TestII()
{
    bst_iter_t root = NULL;
    bst_iter_t find_data = NULL;
    bst_iter_t begin = NULL;
    char *str1 = "Noam";
    char *str2 = "Eden";
    char *str3 = "Naor";
    char *str4 = "Carmel";
    char *str5 = "Moshe";
    char *str6 = "Liran";
    char *str7 = "Saggi";

    bst_t *tree = BstCreate(&CmpStr, (void *)6);
    printf(CYAN"\n\tTest II\n\n"RESET); 
    
    NOT_TEST("BstCreate", tree, NULL);
    TEST("Size (0)", BstSize(tree), 0);
    TEST("IsEmpty", BstIsEmpty(tree), 1);

    root = BstInsert(tree, str2);
    BstInsert(tree, str1);
    BstInsert(tree, str3);
    BstInsert(tree, str4);
    BstInsert(tree, str5);
    BstInsert(tree, str6);
    BstInsert(tree, str7);

    printf("BstInsert: Eden, Noam, Naor, Carmel, Moshe, Liran, Saggi\n");
   /* Print2DStr(root, 0);
    printf("\n");
    */
    TEST("Size (7)", BstSize(tree), 7);
    TEST("IsEmpty", BstIsEmpty(tree), 0);
    
    begin = BstBegin(tree);
    begin = BstNext(begin);
    TEST("IsEqual", begin, root);
    
    begin = BstNext(begin);
    begin = BstNext(begin);
    begin = BstNext(begin);
    begin = BstNext(begin);

    BstRemove(begin);
    printf("BstRemove 'Noam'\n");
    Print2DStr(root, 0);
    printf("\n");

    find_data = BstFind(tree, "Liran");
    NOT_TEST("BstFind ('Liran')", find_data, NULL);
    find_data = BstFind(tree, "liran");
    TEST("BstFind ('liran')", find_data, NULL);

    BstDestroy(tree);
    printf(CYAN"\n\tEnd Test II\n\n"RESET); 
}

static void TestForEach()
{
    bst_iter_t root = NULL;
    int status = 0;
    int param = 0;

    int one = 11;
    int two = 22;
    int three = 33;
    int four = 44;
    int five = 55;
    int six = 66;
    int seven = 77;
    int nine = 99;
    int ten = 100;

    bst_t *tree = BstCreate(&CmpInt, (void *)6);
    printf(CYAN"\n\tTest ForEach\n\n"RESET); 

    root = BstInsert(tree, &six);    
    BstInsert(tree, &one);
    BstInsert(tree, &two);
    BstInsert(tree, &three);
    BstInsert(tree, &five);
    BstInsert(tree, &nine);
    BstInsert(tree, &ten);
    BstInsert(tree, &seven);
    BstInsert(tree, &four);
    
    printf("BstInsert: 66, 11, 22, 33, 55, 99, 100, 77, 44\n");
    Print2DInt(root, 0);
    printf("\n");

    status = BstForeach(BstBegin(tree), BstEnd(tree) , &SumInts, &param);
    TEST("Status returned from FromEach", status, 0);
    TEST("TotalSum calculated with ForEach", param, 507);

    BstDestroy(tree);
    printf(CYAN"\n\tEnd Test I\n\n"RESET); 
}

