#include "pathfinder.h"

int get_weight(char **Names, int *weights, char *Name)
{
    for (int i = 0; i < countIsl; i++)
    {
        if (!mx_strcmp(Names[i], Name)) 
        {
            return weights[i];
        }
    }
    return 0;
}

