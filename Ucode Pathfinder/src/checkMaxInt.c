#include "pathfinder.h"

void checkMaxInt(char ***str_p)
{
    long long sum = 0;
    for (int i = 0; i < size - 1; i++)
    {
        if(sum + mx_atoi(str_p[i][1]) > INT_MAX)
        {
            write(2, "error: sum of bridges lengths is too big\n", 41);
            exit(-1);
        }
        if(mx_atoi(str_p[i][1]) < 1)
        {
            write(2, "error: line ", 12);
            write(2, mx_itoa(i+2), mx_strlen(mx_itoa(i+2)));
            write(2, " is not valid\n", 14);
            exit(-1);
        }
        sum += mx_atoi(str_p[i][1]);
    }
}

