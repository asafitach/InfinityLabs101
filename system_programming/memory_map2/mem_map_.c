#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include <unistd.h>
#include "string.h"
#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>


#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"


int global_int_first;
const int global_int_second;
extern double global_double_first;
double global_double_second = 2;
static const int global_int_const = 0;

struct stack
{
	size_t top;
	size_t capacity;
	void **array;
};
typedef struct stack stack_t;
typedef struct node node_t;
	

struct node
{
	void *data;
	node_t *next;
	node_t *prev;

};

struct dlist
{
	node_t head;
	node_t tail; 
};

typedef struct dlist dlist_t;

/******************************************************************************/
extern int ExternInt(int *x);
int Int(int *x);

static int StaticInt(int *x)
{
	int fun_var = 3;
	int fun_var_second = *x;
	const int fun_var_const = 9;
	
	printf(GREEN"------------------FUNC-STACK-FRAME------------------\n"WHITE);
	printf("|fun_var_const------------>\t\t\t%lu|\n", (size_t)&fun_var_const );
	printf("|fun_var_second----------->\t\t\t%lu|\n", (size_t)&fun_var_second );
	printf("|fun_var------------------>\t\t\t%lu|\n", (size_t)&fun_var );
	

	return (3);
}


static void *TreadTest(void *x)
{
	int fun_var = 3;
	int fun_var_second = 6;
	const int fun_var_const = 9;
	pthread_key_t key = 0;


	pthread_key_create(&key, NULL);
	pthread_setspecific(key, &fun_var);
	printf(GREEN"------------------FUNC-thread------------------\n"WHITE);
	printf("|fun_var_const------------>\t\t\t%lu|\n", (size_t)&fun_var_const );
	printf("|fun_var_second----------->\t\t\t%lu|\n", (size_t)&fun_var_second );
	printf("|fun_var------------------>\t\t\t%lu|\n", (size_t)&fun_var );
	printf("TLS global---------------->\t\t\t%lu|\n", (size_t)&key);

	
	x = (void *)((size_t)x + 1);
	return (x);
}


int main(int argc, char *argv[], char *envp[])
{
	pthread_t threads[2];
	size_t first;
	size_t second = 2;
	const size_t const_local_first;
	const size_t const_local_second = 2;
	char *str = "hello";
	char str1[] = "hello";
	static int static_int_first;
	static int static_int_second = 2;
	static const int const_static_int_first;
	static const int const_static_int_second = 2;
	stack_t *(*stackcreate)(size_t) = NULL;
	char env_var[500];
	char *alloc_first = malloc(5);
	char *alloc_second = malloc(12);
	pthread_key_t key = 0;
	dlist_t *(*fprint)(void) = NULL;

	
	/*int(*printf)(char *, ...) = NULL;
*/	void *lib = NULL;
	void *lib2 = NULL;
	system("clear");
	
	pthread_key_create(&key, NULL);
	pthread_setspecific(key, &const_static_int_second);
	pthread_create(&threads[1], NULL, TreadTest, NULL);
	pthread_create(&threads[1], NULL, TreadTest, NULL);
	sleep(2);

	lib = dlopen("/home/asafitach/asaf-itach/ds/lib/libdllist.so", RTLD_LAZY);

	
	*(void**)(&fprint) = dlsym(lib, "DlistCreate");
/*	first = atoi(argv[1]);*/
/*	first += rand();*/
	fprint();	
	lib2 = dlopen("./libstack.so", RTLD_LAZY);
	*(void **)(&stackcreate) = dlsym(lib2, "StackCreate");
	stackcreate((size_t)2);
	
/******************************************************************************/
	printf(GREEN"\n------------------COMMAND-LINE------------------\n"WHITE);
	printf("|*envp--------------------->\t\t\t%lu|\n", (size_t)envp[1] );
	printf("|*argv--------------------->\t\t\t%lu|\n\n", (size_t)argv[1] );
	printf("|envp--------------------->\t\t\t%lu|\n", (size_t)&envp[1] );
	printf("|argv--------------------->\t\t\t%lu|\n", (size_t)&argv[1] );
	
	printf(GREEN"\n\n------------------STACK------------------\n"WHITE);
	
	printf("|str1--------------------->\t\t\t%lu|\n", (size_t)str1 );
	printf("|const_local_second ------>\t\t\t%lu|\n", (size_t)&const_local_second );
	printf("|const_local_first-------->\t\t\t%lu|\n", (size_t)&const_local_first );
	printf("|argc--------------------->\t\t\t%lu|\n", (size_t)&argc );
	printf("|&dlistcreate------------->\t\t\t%lu|\n", (size_t)&fprint);
	printf("|&stackcreate------------->\t\t\t%lu|\n", (size_t)&stackcreate);
	
	
	StaticInt(&static_int_first);
	
	printf(GREEN"\n\n------------------HEAP------------------\n\n"WHITE);
	printf("------------------------MMS---------------------------------------\n");
	printf("----------------------------------------------------------------\n");
	printf("|dlistcreate-------------->\t\t\t%lu|\n", (size_t)fprint);
	printf("|stackcreate-------------->\t\t\t%lu|\n", (size_t)stackcreate);
	printf("\n\n--------------------IMPLICIT LIB--------------------------------\n");
	printf("----------------------------------------------------------------\n");
	printf("|d list lib--------------->\t\t\t%lu|\n", (size_t)lib);
	printf("TLS global---------------->\t\t\t%lu|\n", (size_t)&key);
	printf("TLS local----------------->\t\t\t%lu|\n", (size_t)lib);

/* 	MemoryMap(8);
 *//* 	printf("|memory map--------------->\t\t\t%lu|\n", (size_t)MemoryMap);
 */	printf("|strlen(library func)----->\t\t\t%lu|\n", (size_t)&printf);
	printf("----------------------------------------------------------------\n\n");
	printf("|stack lib---------------->\t\t\t\t%lu|\n", (size_t)lib2);
	printf("|alloc_second------------->\t\t\t\t%lu|\n", (size_t)alloc_second);
	printf("|alloc_first-------------->\t\t\t\t%lu|\n", (size_t)alloc_first);
	
	printf(GREEN"\n\n------------------BSS------------------\n"WHITE);
	printf("|global_const = 0 -------->\t\t\t\t%lu|\n", (size_t)& global_int_second);
	printf("|global_int_first--------->\t\t\t\t%lu|\n", (size_t)& global_int_first);
	printf("|global_double_first------>\t\t\t\t%lu|\n", (size_t)& global_double_first);
	printf("|static_int_first--------->\t\t\t\t%lu|\n", (size_t)& static_int_first);
	printf("|global_int_const--------->\t\t\t\t%lu|\n\n", (size_t)&global_int_const );

	printf(GREEN"|------------------DATA------------------\n"WHITE);
	printf("|static_int_second-------->\t\t\t\t%lu|\n", (size_t)& static_int_second);
	printf("|global_double_second----->\t\t\t\t%lu|\n", (size_t)& global_double_second);
	
	printf(GREEN"------------------DATA - READ ONLY------------------\n"WHITE);
	printf("|const_static_int_second-->\t\t\t\t%lu|\n", (size_t)&const_static_int_second );
	printf("|const_static_int_first--->\t\t\t\t%lu|\n", (size_t)&const_static_int_first );
	printf("|string literal----------->\t\t\t\t%lu|\n\n", (size_t)str );

	printf(GREEN"\n------------------TEXT------------------\n"WHITE);
	printf("|extern function --------->\t\t\t\t%lu|\n", (size_t)&ExternInt);
	printf("|static lib func---------->\t\t\t\t%lu|\n", (size_t)&StrLen );
	printf("|function (define after)-->\t\t\t\t%lu|\n", (size_t)&Int );
	printf("|main -------------------->\t\t\t\t%lu|\n", (size_t)&main );
	printf("|static function --------->\t\t\t\t%lu|\n\n", (size_t)&StaticInt );
	printf("-----------------------BOTTOM LINE------------------\n\n");
	
	dlclose(lib);
	dlclose(lib2);
	
return 0;
}

int Int(int *x)
{
	*x = rand();
	return(4);
}
/********************************E.O.F*****************************************/
