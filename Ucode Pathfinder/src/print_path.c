#include "pathfinder.h"

void print_path(char *I1, char *I2, char** Bridges, int *Distance, int count)
{
        mx_printstr("========================================\n");
        mx_printstr("Path: "); mx_printstr(I1); mx_printstr(" -> "); mx_printstr(I2); mx_printchar('\n');
        if(count == 2)
        {
            mx_printstr("Route: ");
            mx_printstr(I1);
            mx_printstr(" -> ");
            mx_printstr(I2);
            mx_printchar('\n');
            mx_printstr("Distance: "); 
            mx_printint(Distance[0]); 
            mx_printchar('\n');
        }
        else
        {
            int sum = 0;
            mx_printstr("Route: ");
            mx_print_strarr(Bridges, " -> ");
            mx_printstr("Distance: ");
            mx_printint(Distance[0]);
            sum += Distance[0];
            for(int i = 1; i < count - 1; i++)
            {
                mx_printstr(" + ");
                mx_printint(Distance[i]);
                sum += Distance[i]; 
            }
            mx_printstr(" = ");
            mx_printint(sum);
            mx_printchar('\n');
        }
        mx_printstr("========================================\n");
}

