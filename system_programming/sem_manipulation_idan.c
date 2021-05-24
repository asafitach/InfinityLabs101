#include <stdio.h>   /* printf */
#include <semaphore.h>  /* open getvalue wait post close unlink */
#include <fcntl.h>     /* For O_* constants */
#include <sys/stat.h>  /* For mode constants */
#include <string.h>   /* strncmp */
#include <assert.h>   /* comment */
#include <errno.h>   /* errno */
#include <stdlib.h>  /* atoi abs */
#include <ctype.h>  /* toapper */

/***********************color macros for printf*********************************/

#define RED "\033[1;31m"  /* print in red */

#define GREEN "\033[1;32m" /* print in green */

#define BLUE "\033[1;34m"  /* print in blue */

#define YELLOW "\033[1;33m" /* print in yellow  */

#define PURPLE "\033[1;35m" /* print in purple */

#define CYAN "\033[1;3;36m" /* print in cyan */

#define RESET "\033[0m" /* reset print color  */

#define BUFFER_SIZE 256

/********************* name_status_t ***************************/

typedef enum name_status
{
    NOT_VALID = 0,
    VALID
} name_status_t;

/********************* service function signitures ***************************/

static void PrintWelcomeMessage(void);
static void Operation(sem_t *sem, char *input, int number,int *undo_counter, int *undo_flag);
static name_status_t IsNameValid(char *name);
static int ProcessInput(char *input, int *undo_flag);
static void Undo(sem_t *sem, int undo_counter);

/********************* Main ***************************/

int main(int argc, char *argv[])
{
    sem_t *sem = NULL;

    int number = 0;

    int undo_falg = 0;

    int undo_counter = 0;

    char input[BUFFER_SIZE] = {0};

    int errno;

    if (argc < 2)
    {
        printf(RED"\nNot enough arguments, please try again.\n\n"RESET);

        return (1);
    }
/* 
    if (NOT_VALID == IsNameValid(argv[1]))
    {
        return (1);
    }
 */
    errno = 0;

    if ((sem = sem_open(argv[1], O_CREAT, S_IRWXU, 1)) == SEM_FAILED) 
    {
        fprintf(stderr, RED"sem_open() failed.  errno: %d\n"RESET, errno);
    }

    PrintWelcomeMessage();

    while ('X' != toupper(*input))
    {
        fgets(input, BUFFER_SIZE, stdin);

        number = ProcessInput(input, &undo_falg);
        
        Operation(sem, input, number, &undo_counter, &undo_falg);
    }

    Undo(sem, undo_counter);

    sem_close(sem);

    return (0);
}

static void PrintWelcomeMessage(void)
{
    printf(GREEN"\nWelcome to sem_manipulation!\n\n"RESET);
    printf("\nplease insert the following inputs:\n\n");
    printf("\nD and then a positive integer number to decrement the semaphore by number.\n");
    printf("\nI and then a positive integer number to increment the semaphore by number.\n");
    printf("\nV to print the current semaphore value.\n");
    printf("\nX to exit the program.\n\n");

    return ;
}

/********************* Operation ***************************/

static void Operation(sem_t *sem, char *input, int number,int *undo_counter, int *undo_flag)
{
    int sval = 0;

    int i = 0;

    assert(NULL != sem);
    assert(NULL != input);
    assert(NULL != undo_counter);
    assert(NULL != undo_flag);
    
    switch (toupper(*input))
    {
        case 'D':

            for (i = 0; i < number; i++)
            {
                sem_wait(sem);

                *undo_counter += *undo_flag;
            } 

            break;

        case 'I':

            for (i = 0; i < number; i++)
            {
                sem_post(sem);

                *undo_counter -= *undo_flag;
            }

            break;

        case 'V':

            if (0 != sem_getvalue(sem, &sval))
            {
                printf("\nsem_getvalue error\n");
            }

            printf(GREEN"\nThe current semaphore value is: %d\n"RESET, sval);

            break;

        case 'X':

            printf("\n\nGoodbye!\n\n");

            break;

        default:

            printf(RED"\nOnly V, I or X are allowed.\n"RESET);

            break;
    }

    return ;
}

/********************* Undo ***************************/

static void Undo(sem_t *sem, int undo_counter)
{
    int is_positive = undo_counter > 0 ? 1 : 0;

    undo_counter = abs(undo_counter);

    assert(NULL != sem);
    
    while (undo_counter > 0)
    {
        (1 == is_positive) ? sem_post(sem) : sem_wait(sem);

        undo_counter--;
    }

    return ;
}

/********************* IsNameValid ***************************/

static name_status_t IsNameValid(char *name)
{
    assert(NULL != name);

    if ('/' != name[0])
    {
        printf(RED"\nThe name of the semaphore is not valid.\n"RESET);
        printf("\nplease insert a name that start with '/'.\n");
        printf("\nfor more info, please read posix semaphores manual.\n\n");

        return (NOT_VALID);
    }

    return (VALID);
}

/********************* ProcessInput ***************************/

static int ProcessInput(char *input, int *undo_flag)
{
    int number = 0;

    assert(NULL != input);
    assert(NULL != undo_flag);
    
    input += 2;

    number = atoi(input);

    if (number < 0)
    {
        printf(RED"\nYou cannot insert a negative number.\n\n"RESET);
        printf("\nthe program will use its absolute value insted.\n\n");

        number = abs(number);
    }

    while (' ' != *input && '\0' != *input)
    {
        input++;
    } 

    if (0 == strncmp(input + 1, "undo", 4))
    {
        *undo_flag = 1;
    }

    return(number != 0 ? number : 1);
}

/********************* End ***************************/
