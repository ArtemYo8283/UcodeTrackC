#include "pathfinder.h"

bool is_visited(char **visited, char *visit, int visits)
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

