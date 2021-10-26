#include "pathfinder.h"

void print_path(Path* paths)
{
    for(int i = 0; i < P_size; i++)
    {
        mx_printstr("========================================\n");
        mx_printstr("Path: "); mx_printstr(paths[i].I1); mx_printstr(" -> "); mx_printstr(paths[i].I2); mx_printchar('\n');
        if(paths[i].count == 1)
        {
            mx_printstr("Route: "); mx_printstr(paths[i].I1); mx_printstr(" -> "); mx_printstr(paths[i].I2); mx_printchar('\n');
            mx_printstr("Distance: "); mx_printint(paths[i].Bridges[0].Distance); mx_printchar('\n');
        }
        mx_printstr("========================================\n");
    }
}

