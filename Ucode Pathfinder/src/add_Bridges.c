#include "pathfinder.h"

Bridge *add_Bridges(char ***str_p)
{
    struct Bridge *bridge = malloc((size - 1) * sizeof(Bridge));

    for(int i = 0; i < size - 1; i++)
    {
        if(str_p[i][0][0] == '-' || str_p[i][0][mx_strlen(str_p[i][0])-1] == '-')
        {
            write(2, "error: line ", 12);
            write(2, mx_itoa(i+2), mx_strlen(mx_itoa(i+2)));
            write(2, " is not valid\n", 14);
            exit(-1);
        }
        char **aboba = mx_strsplit(str_p[i][0], '-');
        mx_str_reverse(aboba[0]);
        mx_str_reverse(aboba[1]);
        struct Bridge tmp = {aboba[1], aboba[0], mx_atoi(str_p[i][1])};
        bridge[i] = tmp;
    }
    return bridge;
}

