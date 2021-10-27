#include "pathfinder.h"

void print_path(Path* paths)
{
    for(int i = 0; i < P_size; i++)
    {
        if(paths[i].Bridges[0].Distance == 0)
        {
            continue;
        }
        mx_printstr("========================================\n");
        mx_printstr("Path: "); mx_printstr(paths[i].I1); mx_printstr(" -> "); mx_printstr(paths[i].I2); mx_printchar('\n');
        if(paths[i].count == 1)
        {
            mx_printstr("Route: "); mx_printstr(paths[i].I1); mx_printstr(" -> "); mx_printstr(paths[i].I2); mx_printchar('\n');
            mx_printstr("Distance: "); mx_printint(paths[i].Bridges[0].Distance); mx_printchar('\n');
        }
        else
        {
            int sum = 0;
            mx_printstr("Route: ");
            if(mx_strcmp(paths[i].Bridges[0].I1, paths[i].I1) == 0)
            {
                mx_printstr(paths[i].Bridges[0].I1); 
            } 
            else
            {
                mx_printstr(paths[i].Bridges[0].I2); 
            }
            for(int j = 1; j < paths[i].count; j++)
            {
                mx_printstr(" -> ");
                if(mx_strcmp(paths[i].Bridges[j].I2 , paths[i].Bridges[j - 1].I2) == 0)
                {
                    mx_printstr(paths[i].Bridges[j].I1);
                }
                else
                {
                    mx_printstr(paths[i].Bridges[j].I2);
                }
            }
            mx_printstr(" -> ");
            mx_printstr(paths[i].I2);
            mx_printchar('\n');
            mx_printstr("Distance: ");
            mx_printint(paths[i].Bridges[0].Distance);
            sum += paths[i].Bridges[0].Distance;
            for(int j = 1; j < paths[i].count; j++)
            {
                mx_printstr(" + ");
                mx_printint(paths[i].Bridges[j].Distance);
                sum += paths[i].Bridges[j].Distance; 
            }
            mx_printstr(" = ");
            mx_printint(sum);
            mx_printchar('\n');
        }
        mx_printstr("========================================\n");
    }
}

