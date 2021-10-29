#include "pathfinder.h"

bool is_blacklisted(int x, int *bl, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (bl[i] == x)
        {
            return true;
        }
    }
    return false;
}

