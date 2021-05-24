#include <fcntl.h> /* O_CREAT */
#include <semaphore.h> /* sem_t, sem_open, sem_wait, sem_post, sem_getvalue, sem_close, SEM_FAILED */
#include <stdio.h> /* printf */
#include <stdlib.h> /* atoi */
#include <string.h> /* strncmp */

#define INITIAL_VALUE (5)

static int CheckInput(char op, char *input, int *counter);

int main(int argc, char *argv[])
{
    sem_t *sem = NULL;
    char input[10] = {0};
    int number = 0;
    int counter = 0;

    if (argc < 2)
    {
        printf("Enter string id of the semaphor\n");
        return (-1);
    }

    sem = sem_open(argv[1], O_CREAT, 0600, INITIAL_VALUE);

    if (SEM_FAILED == sem)
    {
        printf("sem_open failed!\n");
        return (-1);
    }

    printf("Enter a command:\n");
    printf("D number- decrements the value of semaphore by number\n");
    printf("I number- increments the value of semaphore by number\n");
    printf("V - view the value of the semaphore\n");
    printf("X - exits the program\n");

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) == NULL) 
        {
            printf("fgets failed\n");
            return (-1);
        }

        switch (input[0])
        {
        case 'D':
            number = CheckInput('D', input + 2, &counter);

            while (number > 0)
            {
                sem_wait(sem);
                --number;
            }
            
            break;
        
        case 'I':
            number = CheckInput('I', input + 2, &counter);

            while (number > 0)
            {
                sem_post(sem);
                --number;
            }

            break;
        
        case 'V':

            sem_getvalue(sem, &number);
            printf("Semaphore value: %d\n", number);        

            break;
        
        case 'X':
            
            while (counter > 0)
            {
                sem_post(sem); 
                --counter;   
            }

            while (counter < 0)
            {
                sem_wait(sem); 
                ++counter;   
            }

            sem_close(sem);
            printf("Exit!\n");
            return (0);
        
        default:
            printf("Enter valid input\n");

            break;
        }

    }
    
    return (0);    
}

static int CheckInput(char op, char *input, int *counter)
{
    int number = 0;
    
    number = atoi(input);

    while ((' ' != *input) && ('\0' != *input))
    {
        ++input;
    } 

    if (0 == strncmp(input + 1, "undo", 4))
    {
        if ('D' == op)
        {
            *counter += number;
        }
        else
        {
            *counter -= number;
        }
        
    }
    
    return (number);
}