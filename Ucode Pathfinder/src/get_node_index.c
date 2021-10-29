#include "pathfinder.h"

int get_node_index(char **Names, char *Name)
{
    for (int i = 0; i < countIsl; i++)
    {
        if (mx_strcmp(Names[i], Name) != 0) 
        {
            return i;
        }
    }
    return -1;
}

