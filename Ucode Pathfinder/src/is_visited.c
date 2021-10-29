#include "pathfinder.h"

bool is_visited(char **visited, char *s, int visits)
{
    for (int i = 0; i < visits; i++)
    {
        if (!mx_strcmp(visited[i], s)) 
        {
            return true;
        }
    }
    return false;
}

