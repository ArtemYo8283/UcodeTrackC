#include "pathfinder.h"

Path *add_Paths(char ***str_p)
{
    struct Path *paths = malloc((size - 1) * sizeof(Path));

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
        struct Path tmp = {aboba[1], aboba[0], mx_atoi(str_p[i][1])};
        paths[i] = tmp;
    }
    return paths;
}

