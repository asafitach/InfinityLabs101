#ifndef __KNIGHTS_TOUR_H__
#define __KNIGHTS_TOUR_H__

#define BOARD_SIZE 64

typedef enum method
{
    BACK_TRACKING = 0,
    HEURISTIC = 1
}solution_method_t;


/*Description: 
@params: 
@return: 
@errors: 
*/
void FindKnightsPath(unsigned char arr[BOARD_SIZE], int start_index,solution_method_t method);

void PrintLut();

#endif /* __KNIGHTS_TOUR_H__ */
