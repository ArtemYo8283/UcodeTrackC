#include "pathfinder.h"

void set_weight(int **weights, char **nodes, char *s, int waight)
{
    for (int i = 0; i < countIsl; i++)
    {
        if (!mx_strcmp(nodes[i], s))
        {
            if ((*weights)[i] < waight && (*weights)[i] > 0) 
            {
                return;
            }
            (*weights)[i] = waight;
            return;
        }
    }
}

