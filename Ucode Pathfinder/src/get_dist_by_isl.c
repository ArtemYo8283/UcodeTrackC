#include "pathfinder.h"

int get_dist_by_isl(Bridge* bridges, char* A, char* B)
{
    for(int i = 0; i < size - 1; i++)
    {
        if( (mx_strcmp(bridges[i].I1, A) == 0 &&  mx_strcmp(bridges[i].I2, B) == 0)
            ||
            (mx_strcmp(bridges[i].I1, B) == 0 &&  mx_strcmp(bridges[i].I2, A) == 0))
        {
            return bridges[i].Distance;
        }
    }
    return 0;
}

