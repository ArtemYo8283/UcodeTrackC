#include "pathfinder.h"

Path* create_routes(Bridge *bridges)
{
    P_size = 0;
    struct Path *pathes = malloc(P_size * sizeof(Path));

    char **Names = (char**)malloc(countIsl);
    int h = 0;
    for(int i = 0; i < countIsl; i++)
    {
        Names[i] = (char*)malloc(256); 
    }

    Names[0] = bridges[0].I1;
    for(int i = 1; i < size - 1; i++)
    {
        int flag = 0;
        for (int j = i - 1; j > -1; j--)
        {
            if(mx_strcmp(bridges[i].I1, bridges[j].I1) == 0 || mx_strcmp(bridges[i].I1, bridges[j].I2) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            h++;
            Names[h] = bridges[i].I1;
        }   
    }
    for(int i = 0; i < size - 1; i++)
    {
        int flag = 0;
        for (int j = i - 1; j > -1; j--)
        {
            if(mx_strcmp(bridges[i].I2, bridges[j].I2) == 0 || mx_strcmp(bridges[i].I2, bridges[j].I1) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            h++;
            Names[h] = bridges[i].I2;
        }   
    }
    
    for(int i = 0; i < countIsl; i++)
    {
        mx_printint(i);
        
        for(int j = i + 1; j < countIsl; j++)
        {
            mx_printchar(' ');
            mx_printint(i);
            for(int k = 0; k < size - 1; k++)
            {
                if(
                    (mx_strcmp(bridges[k].I1, Names[i]) == 0 && mx_strcmp(bridges[k].I2, Names[j]) == 0) ||
                    (mx_strcmp(bridges[k].I1, Names[j]) == 0 && mx_strcmp(bridges[k].I2, Names[i]) == 0)
                )
                {
                    P_size++;
                    pathes = realloc(pathes, P_size * sizeof(Path));
                    struct Bridge *tmp1 = malloc(1 * sizeof(Bridge));
                    tmp1[0] = bridges[k];
                    struct Path tmp = {Names[i], Names[j], tmp1, 1};
                    pathes[P_size - 1] = tmp;
                }
                if((mx_strcmp(bridges[k].I1, Names[i]) == 0 && mx_strcmp(bridges[k].I2, Names[j]) != 0) || (mx_strcmp(bridges[k].I1, Names[j]) == 0 && mx_strcmp(bridges[k].I2, Names[i]) != 0))
                {
                    // int ct = 0;
                    // struct Bridge *tmp2 = malloc((countIsl - 1) * sizeof(Bridge));
                    // for(int l = 0; l < countIsl - 1; l++)
                    // {
                        
                    // }   
                }
            }
        }
        mx_printchar('\n');
    }
    return pathes;
}

