#include <stdio.h>   /* printf fprintf fgets */
#include <semaphore.h> /* ... */
#include <fcntl.h>     /* For O_* constants */
#include <sys/stat.h>  /* For mode constants */
#include <string.h>   /* strcmp */
#include <errno.h>   /* errno */
#include <stdlib.h> /* atoi */

/***********************color macros for printf*********************************/

#define RED "\033[1;31m"  /* print in red */
#define GREEN "\033[1;32m" /* print in green */
#define BLUE "\033[1;34m"  /* print in blue */
#define YELLOW "\033[1;33m" /* print in yellow  */
#define PURPLE "\033[1;35m" /* print in purple */
#define CYAN "\033[1;3;36m" /* print in cyan */
#define RESET "\033[0m" /* reset print color  */

#define BUFF_SIZE 256

typedef enum name_status
{
    NOT_VALID = 0,
    VALID
} name_status_t;

static void PrintStartMsg();
static int IsUndoNecessary(char *input);
static void Undo(int counter, sem_t *sem);



int main(int argc, char *argv[])
{
    sem_t *sem = NULL;
    char input[BUFF_SIZE] = {0};
    unsigned int number = 0;
    unsigned int index = 0;
    int undo_flag = 0;
    int sem_val = 0;
    int errno;
    int counter = 0;

    if (argc < 2)
    {
        printf(RED"\nNot enough arguments, please try again.\n\n"RESET);

        return (1);
    }


/*     sem_unlink(argv[1]); */
    errno = 0;

    sem = sem_open(argv[1], O_CREAT, S_IRWXU, 1);
    if (sem == SEM_FAILED) 
    {
        fprintf(stderr, "sem_open() failed. errno num: %d\n", errno);
    }


    if (0 != sem_getvalue(sem, &sem_val))
    {
        printf("\nerror\n");
    }

    PrintStartMsg();

    while ('x' != *input && 'X' != *input)
    {
        if (0 == fgets(input, BUFF_SIZE, stdin))
        {
            return (-1);
        }

        number = atoi(input + 1);
        number = (number) ? number : 1;
        if (1 == IsUndoNecessary(input + 1))
        {
            undo_flag = 1;
        }

        switch (*input)
        {
        case 'D':
        case 'd':
            counter = (undo_flag) ? (counter - (int)number): counter;
            for (index = 0; index < number; ++index)
            {
                sem_wait(sem);
            }
            break;

        case 'I':
        case 'i':
            counter = (undo_flag) ? (counter + (int)number): counter;
            for (index = 0; index < number; ++index)
            {
                sem_post(sem);
            }
            break;

        case 'V':
        case 'v':
            sem_getvalue(sem, &sem_val);
            printf(GREEN"\nThe current semaphore value is: %d\n"RESET, sem_val);
            break;

        case 'X':
        case 'x':
            Undo(counter, sem);
            printf("\n\nGoodbye!\n\n");
            break;

        default:
            printf(RED"\nOnly V, I or X are allowed."RESET);
        }



    }

    sem_close(sem);

    return (0);
}

static void PrintStartMsg()
{
    printf(GREEN"\nWelcome to sem_manipulation!\n\n"RESET);
    printf("\nD and a number to decrement the semaphore. option[undo].\n");
    printf("\nI and a number to increment the semaphore. option[undo].\n");
    printf("\nV to get the semaphore value.\n");
    printf("\nX to exit the program.\n");
}

static int IsUndoNecessary(char *input)
{
    while (0 != *input && 'u' != *input)
    {
        ++input;
    }

    return ((0 == strncmp("undo", input, 4)));
}

static void Undo(int counter, sem_t *sem)
{
    while (counter > 0)
    {
        sem_wait(sem);
        --counter;
    }
    while (counter < 0)
    {
        sem_post(sem);
        ++counter;
    }
}