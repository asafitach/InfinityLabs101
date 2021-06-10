#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>
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


/******************************************************************************/
extern int ExternInt(int *x);
int Int(int *x);

static int StaticInt(int *x)
{
	int fun_var = 3;
	int fun_var_second = 6;
	const int fun_var_const = 9;
	printf(GREEN"------------------FUNC-STACK-FRAME------------------\n"WHITE);
	printf("|fun_var_const------------>\t\t\t%lu|\n", (size_t)&fun_var_const );
	printf("|fun_var_second----------->\t\t\t%lu|\n", (size_t)&fun_var_second );
	printf("|fun_var------------------>\t\t\t%lu|\n", (size_t)&fun_var );
	

	return (3);
}


int main(int argc, char *argv[], char *envp[])
{
	size_t first;
	size_t second = 2;
	const size_t const_local_first;
	const size_t const_local_second = 2;
	char *str = "hello";
	char str1[] = "hello";
	static int static_int_first;
	static int static_int_second = 2;
	const static int const_static_int_first;
	const static int const_static_int_second = 2;
	char env_var[500];
	char *alloc_first = malloc(5);
	char *alloc_second = malloc(12);
	
	void *lib = NULL;
	void *lib2 = NULL;
	strncpy(env_var, envp[1], 500);
	
	
	
/******************************************************************************/
	printf(GREEN"\n------------------COMMAND-LINE------------------\n"WHITE);
	printf("|*envp--------------------->\t\t\t%lu|\n", (size_t)envp[1] );
	printf("|*argv--------------------->\t\t\t%lu|\n\n", (size_t)argv[1] );
	printf("|envp--------------------->\t\t\t%lu|\n", (size_t)&envp[1] );
	printf("|argv--------------------->\t\t\t%lu|\n", (size_t)&argv[1] );
	
	printf(GREEN"\n\n------------------STACK------------------\n"WHITE);
	
	printf("|str1--------------------->\t\t\t%lu|\n", (size_t)str1 );
	printf("|alloc_second address----->\t\t\t%lu|\n", (size_t)&alloc_second);
	printf("|alloc_first address------>\t\t\t%lu|\n", (size_t)&alloc_first);
	printf("|const_local_second ------>\t\t\t%lu|\n", (size_t)&const_local_second );
	printf("|const_local_first-------->\t\t\t%lu|\n", (size_t)&const_local_first );
	printf("|argc--------------------->\t\t\t%lu|\n", (size_t)&argc );
	
	
	StaticInt(&static_int_first);
	
	printf(GREEN"\n\n------------------HEAP------------------\n\n"WHITE);
	printf("------------------------MMS---------------------------------------\n");

	printf("|strlen(library func)----->\t\t\t%lu|\n", (size_t)&strlen);
	printf("----------------------------------------------------------------\n\n");
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
	printf("|function (define after)-->\t\t\t\t%lu|\n", (size_t)&Int );
	printf("|main -------------------->\t\t\t\t%lu|\n", (size_t)&main );
	printf("|static function --------->\t\t\t\t%lu|\n\n", (size_t)&StaticInt );
	printf("-----------------------BOTTOM LINE------------------\n\n");

	
return 0;
}

int Int(int *x)
{
	*x = rand();
	return(4);
}
/********************************E.O.F*****************************************/
