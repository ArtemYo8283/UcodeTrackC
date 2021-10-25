#include "pathfinder.h"

void checkDist(char ***str_p)
{
    for(int i = 0; i < size - 1; i++)
    {
        if(mx_strlen(str_p[i][1]) == 0)
        {
            write(2, "error: line ", 12);
            write(2, mx_itoa(i+2), mx_strlen(mx_itoa(i+2)));
            write(2, " is not valid\n", 14);
            exit(-1);
        }
        for(int j = 0; j < mx_strlen(str_p[i][1]); j++)
        {
            if(!mx_isdigit(str_p[i][1][j]))
            {
                write(2, "error: line ", 12);
                write(2, mx_itoa(i+2), mx_strlen(mx_itoa(i+2)));
                write(2, " is not valid\n", 14);
                exit(-1);
            }
        }
    }
}

