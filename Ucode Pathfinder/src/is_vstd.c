#include "pathfinder.h"

bool is_vstd(char **visited, char *visit, int visits)
{
    for (int i = 0; i < visits; i++)
    {
        if (!mx_strcmp(visited[i], visit)) 
        {
            return true;
        }
    }
    return false;
}

