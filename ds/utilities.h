#ifndef __UTILITIES_H__
#define __UTILITIES_H__

/********************************* test utilities ******************************/

/*********************** color macros for printf *********************************/

#define RED "\033[1;31m"  

#define GREEN "\033[1;5;32m"	

#define BLUE "\033[1;34m"  

#define YELLOW "\033[1;4:1;33m" 

#define PURPLE "\033[1;35m" 

#define CYAN "\033[1;3;36m"

#define RESET "\033[0m" 

/********************************** Test MACROs *********************************/

#define TEST_ARE_EQUAL(name, real, expected) printf("%s: %s", name, real == expected\
									? GREEN"SUCCESS\n"RESET\
									: RED"\aFAILURE\n"RESET)
									
#define TEST_ARE_NOT_EQUAL(name, real, expected) printf("%s: %s", name, real != expected\
									? GREEN"SUCCESS\n"RESET\
									: RED"\aFAILURE\n"RESET)									

/********************************* others: ******************************/


#define ARR_END 0xffffffffffffffff

#define DEC_BASE 10

#define ASCII_SIZE 256

/*typedef enum status
{
	SUCCESS = 0,
	FAIL =  1
}status_t;*/


#endif /* __UTILITIES_H__ */
