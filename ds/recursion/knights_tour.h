#ifndef __KNIGHTS_TOUR_H__
#define __KNIGHTS_TOUR_H__

#define SIZE 8


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

#define BOARD_SIZE (ROWS * COL)


/********************************************************************/


/*Description: 
@params: 
@return: 
@errors: 
*/ 
/* void FindKnightsPath(unsigned char arr[SIZE][SIZE]);
 */knight_tour_status_t FindKnightTour(char knight_tour[BOARD_SIZE], int start_position, algorithm_t algorithm);


#endif /* __KNIGHTS_TOUR_H__ */

