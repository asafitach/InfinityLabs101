#include <stdio.h>   /* printf */
#include <stdlib.h>
#include "knights_tour.h"


/********************* Function signitures ***************************/

knight_tour_status_t FindKnightTour(char knight_tour[BOARD_SIZE], int start_position, algorithm_t algorithm);

static void PrintKnightMoves(char knight_tour[BOARD_SIZE]);

/********************* Main ***************************/

int main()
{
    char knight_tour[BOARD_SIZE] = {0};
    knight_tour_status_t status = SUCCESS;

    status = FindKnightTour(knight_tour, (rand() % BOARD_SIZE) / 2 + 15, HEURISTIC);

    printf("\nHEURISTIC %d\n", status);

    PrintKnightMoves(knight_tour);

    status = FindKnightTour(knight_tour, 0, BACKTRACK);

    printf("\nBACKTRACK %d\n", status);

    PrintKnightMoves(knight_tour);

    return (0);
}

/********************* PrintKnightMoves ***************************/

static void PrintKnightMoves(char knight_tour[BOARD_SIZE])
{
    int i = 0;

    printf("\n\n");

    for (i = 0; i < BOARD_SIZE; i++)
    {
        printf("%d\t", (int)knight_tour[i]);
        if (0 == ((i + 1) % 8))
        {
            printf("\n\n\n");
        }
    }

    printf("\n\n");
}
