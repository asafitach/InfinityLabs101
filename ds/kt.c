#include <stdio.h>   /* printf */
#include <assert.h>   /* assert */
#include <stdlib.h>   /* size_t rund qsort */
#include <time.h>   /* time */

/********************* Typedefs and macros ***************************/

typedef enum knight_tour_status
{
    SUCCESS = 0,
    FAILURE
} knight_tour_status_t;

typedef enum algorithm
{
    BACKTRACK = 0,
    HEURISTIC
} algorithm_t;

typedef struct adjacent
{
    int index;
    int degree;
} adjacent_t;

#define ROWS 8

#define COL 8

#define NEXT_MOVE 8

#define BOARD_SIZE (ROWS * COL)

#define NOT_ZERO (~(size_t)(0))

typedef size_t bitarray_t;

/********************* Function signitures ***************************/

knight_tour_status_t FindKnightTour(char knight_tour[BOARD_SIZE], int start_position, algorithm_t algorithm);
static knight_tour_status_t RecursFindKnightTour(char knight_tour[BOARD_SIZE], int current_position, int knight_possible_moves[BOARD_SIZE][NEXT_MOVE], bitarray_t bit_board, int counter, algorithm_t algorithm);

static void InitKnightPossibleMovesLut(int knight_possible_moves[BOARD_SIZE][NEXT_MOVE]);
static void InitSquarePosiibleMoves(int knight_possible_moves[BOARD_SIZE][NEXT_MOVE], int i);
static int PossibleMove(int tmp_col, int tmp_row);

static void PrintLut(int lut[BOARD_SIZE][NEXT_MOVE]);
static void PrintKnightMoves(char knight_tour[BOARD_SIZE]);

static int BitArrIsBitOn(bitarray_t bitarray, int bit_index);
static bitarray_t BitArrSetBitOn(bitarray_t bitarray, int bit_index);

static int GetAdjacentDegree(int knight_possible_moves[BOARD_SIZE][NEXT_MOVE], bitarray_t bitarray, int index);
static int CompareAdjacents(const void *ptr1, const void *ptr2);
static void InitAdjacentArray(adjacent_t arr[NEXT_MOVE], int knight_possible_moves[BOARD_SIZE][NEXT_MOVE], bitarray_t bitarray, int index);

/********************* Main ***************************/

int main()
{
    char knight_tour[BOARD_SIZE] = {0};

    int start_position = 0;

    knight_tour_status_t status = SUCCESS;

    algorithm_t algorithm = HEURISTIC;

    status = FindKnightTour(knight_tour, start_position, algorithm);

    printf("\n%d\n", status);

    PrintKnightMoves(knight_tour);

    /* PrintLut(knight_possible_moves); */

    return (0);
}
/********************* FindKnightTour ***************************/

knight_tour_status_t FindKnightTour(char knight_tour[BOARD_SIZE], int start_position, algorithm_t algorithm)
{
    int knight_possible_moves[BOARD_SIZE][NEXT_MOVE] = {{0},{0}};

    bitarray_t bit_board = 0;

    int counter = 0;

    InitKnightPossibleMovesLut(knight_possible_moves);

    PrintLut(knight_possible_moves);

    assert(NULL != knight_tour);
    
    return (RecursFindKnightTour(knight_tour, start_position, knight_possible_moves, bit_board, counter, algorithm));
}

/********************* RecursFindKnightTour ***************************/

static knight_tour_status_t RecursFindKnightTour(char knight_tour[BOARD_SIZE], int current_position, int knight_possible_moves[BOARD_SIZE][NEXT_MOVE], bitarray_t bit_board, int counter, algorithm_t algorithm)
{
    int next_move = 0;

    int next_position = 0; 

    knight_tour_status_t status = FAILURE;

    adjacent_t adj_arr[NEXT_MOVE] = {{-1, 0}};

    assert(NULL != knight_tour);
    assert(NULL != knight_possible_moves);
    
    if (NOT_ZERO == bit_board)  /* if we cover all the bit board */
    {
        return (SUCCESS);
    }

    if (1 == BitArrIsBitOn(bit_board, current_position))   /* if we already been on that square */
    {
      return (FAILURE);
    }

    bit_board = BitArrSetBitOn(bit_board, current_position);

    knight_tour[counter] = *(char *)&current_position;

    counter++;

    if (BACKTRACK == algorithm)
    {
        for (next_move = 0; (next_move < NEXT_MOVE) && (FAILURE == status); next_move++)
        {
            next_position = knight_possible_moves[current_position][next_move];

            if (-1 != next_position)
            {
                status = RecursFindKnightTour(knight_tour, next_position, knight_possible_moves, bit_board, counter, algorithm);
            }
        }
    }
    else
    {
        InitAdjacentArray(adj_arr, knight_possible_moves, bit_board, current_position);

        for (next_move = 0; next_move < NEXT_MOVE && FAILURE == status; next_move++)
        {
            next_position = adj_arr[next_move].index;

            if (-1 != next_position)
            {
                status = RecursFindKnightTour(knight_tour, next_position, knight_possible_moves, bit_board, counter, algorithm);
            }
        }   
    }

    return (status);
}

static void InitAdjacentArray(adjacent_t arr[NEXT_MOVE], int knight_possible_moves[BOARD_SIZE][NEXT_MOVE], bitarray_t bitarray, int current_position)
{
    int next_position = 0;
    int next_move = 0;

    for (next_move = 0; next_move < NEXT_MOVE; next_move++)
    {
        next_position = knight_possible_moves[current_position][next_move];
        arr[next_move].index = next_position;
        arr[next_move].degree = GetAdjacentDegree(knight_possible_moves, bitarray, next_position);
    }
    
    qsort(arr, NEXT_MOVE, sizeof(adjacent_t), CompareAdjacents);
}

/********************************************************************/

static int CompareAdjacents(const void *ptr1, const void *ptr2)
{
    adjacent_t *adjacent1 = (adjacent_t *)ptr1;
    adjacent_t *adjacent2 = (adjacent_t *)ptr2;

    return (adjacent1->degree - adjacent2->degree);
}

/********************************************************************/

static int GetAdjacentDegree(int knight_possible_moves[BOARD_SIZE][NEXT_MOVE], bitarray_t bitarray, int current_position)
{
    int next_position = 0;
    int next_move = 0;
    unsigned char degree = 0;

    for (next_move = 0; next_move < NEXT_MOVE; next_move++)
    {
        next_position = knight_possible_moves[current_position][next_move];
        if (-1 != next_position && 0 == BitArrIsBitOn(bitarray, next_position))
        {
            degree++;
        }
    }
    return (degree);
}

/********************* InitKnightPossibleMovesLut ***************************/

static void InitKnightPossibleMovesLut(int knight_possible_moves[BOARD_SIZE][NEXT_MOVE])
{
    int i = 0;

    assert(NULL != knight_possible_moves);
    
    for (i = 0; i < BOARD_SIZE; i++)
    {
        InitSquarePosiibleMoves(knight_possible_moves, i);
    }

    return ;
}

/********************* InitSquarePosiibleMoves ***************************/

static void InitSquarePosiibleMoves(int knight_possible_moves[BOARD_SIZE][NEXT_MOVE], int i)
{
    int row = i / ROWS;

    int col = i % 8;

    int tmp_row = 0;

    int tmp_col = 0;

    int j = 0;

    int x_move[COL] = {2, 1, -1, -2, -2, -1, 1, 2 };

    int y_move[ROWS] = {1, 2, 2, 1, -1, -2, -2, -1};

    assert(NULL != knight_possible_moves);

    for (j = 0; j < NEXT_MOVE; j++)
    {
        tmp_col = col + x_move[j];

        tmp_row = row + y_move[j];

        knight_possible_moves[i][j] = PossibleMove(tmp_col, tmp_row);
    }

    return ;
}

/********************* PossibleMove ***************************/

static int PossibleMove(int tmp_col, int tmp_row)  /* return a valid square to move to, else -1 */
{
    if ((tmp_col < 0) || (tmp_col > COL - 1) || (tmp_row < 0) || (tmp_row > ROWS - 1))
    {
        return (-1);
    }

    return (tmp_row * ROWS + tmp_col);
}

/********************* PrintLut ***************************/

static void PrintLut(int lut[BOARD_SIZE][NEXT_MOVE])
{
    int i = 0;
    int j = 0;

    assert(NULL != lut);
    
    for(i = 0; i < BOARD_SIZE; i++)
    {
        for(j = 0; j < NEXT_MOVE; j++)
        {
            printf("  %d  ", lut[i][j]);
        }
        printf("\n\n");
    }
}

/********************* BitArrSetBit ***************************/

static void PrintKnightMoves(char knight_tour[BOARD_SIZE])
{
    int i = 0;

    printf("\n\n");

    for (i = 0; i < BOARD_SIZE; i++)
    {
        printf("%d  ", (int)knight_tour[i]);
    }

    printf("\n\n");
}

/********************* BitArrSetBitOn ***************************/

static bitarray_t BitArrSetBitOn(bitarray_t bitarray, int bit_index)
{
    bitarray_t mask = 1;
    
    assert(bit_index < BOARD_SIZE);
    
    mask <<= bit_index;

    bitarray |= mask;
    
    return(bitarray);
}

/********************* BitArrIsBitOn ***************************/

static int BitArrIsBitOn(bitarray_t bitarray, int bit_index)
{
    int is_on = 0;

    bitarray >>= bit_index;

    is_on |= bitarray & 1;
    
    return(is_on);
}

/* time_t start_time = time(NULL);
time_t end_time = 300;

while ((time(NULL) - start_time) < end_time)
{

} */


