#include "pathfinder.h"

void BridgeDup(char ***str_p)
{
    for (int i = 0; i < size - 1; i++)
    {
        char* tmp = str_p[i][0];
        mx_str_reverse(tmp);
        for(int j = 0; j < size - 1; j++)
        {
            if((mx_strcmp(str_p[i][0], str_p[j][0]) == 0 || mx_strcmp(tmp, str_p[j][0]) == 0) && i != j)
            {
                write(2, "error: duplicate bridges\n", 25);
                exit(-1);
            }
        }
    }
}

