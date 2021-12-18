#include "pathfinder.h"
int get_Namea(char **Names, char *Name)
{
    for (int i = 0; i < countIsl; i++)
    {
        if (!mx_strcmp(Names[i], Name)) 
        {
            return i;
        }
    }
    return -1;
}

void create_routes(Bridge *bridges)
{
    char **Names = (char**)malloc(countIsl);
    int h = 0;
    for(int i = 0; i < countIsl; i++)
    {
        Names[i] = (char*)malloc(256); 
    }
    for(int i = 0; i < size - 1; i++)
    {
        int flag1 = 0;
        int flag2 = 0;
        for (int j = 0; j < h; j++)
        {
            if(mx_strcmp(Names[j], bridges[i].I1) == 0)
            {
                flag1 = 1;
            }
            if(mx_strcmp(Names[j], bridges[i].I2) == 0)
            {
                flag2 = 1;
            }
        }
        if(flag1 == 1 && flag2 == 1)
        {
            continue;
        }
        if(flag1 == 0 && flag2 == 1)
        {
            h++;
            Names[h - 1] = bridges[i].I1;
        }   
        if(flag1 == 1 && flag2 == 0)
        {
            h++;
            Names[h - 1] = bridges[i].I2;
        } 
        if(flag1 == 0 && flag2 == 0)
        {
            h++;
            Names[h - 1] = bridges[i].I1;
            h++;
            Names[h - 1] = bridges[i].I2;
        } 
    }
    bridges = sort_bridges(bridges, Names);
    int **matrix = malloc(countIsl * sizeof(int*));
    for (int i = 0; i < countIsl; i++)
    {
        matrix[i] = malloc(countIsl * sizeof(int));
        for (int j = 0; j < countIsl; j++)
        {
            matrix[i][i] = 0;
        }
    }
    for(int i = 0; i < countIsl; i++)
    {
        matrix[i][i] = -1;
    }

    for (int i = 0; i < countIsl - 1; i++)
    {
        int tmp;
        for (int j = i + 1; j < countIsl; j++)
        { 
            tmp = get_dist_by_isl(bridges, Names[i], Names[j]);
            matrix[i][j] = tmp;
            matrix[j][i] = tmp;
        }
    }
    int *weights = malloc((countIsl + 1) * sizeof(int));
    for (int i = 0; i < countIsl - 1; i++)
    {
        for (int j = i + 1; j < countIsl; j++)
        {
            for (int h = 0; h < countIsl; h++) 
            {
                weights[h] = -1;
            }
            for (int h = 0; h < countIsl; h++)
            {
                if (!mx_strcmp(Names[h], Names[j]))
                {
                    weights[h] = 0;
                    break;
                }
            }
            weight(weights, Names, bridges);
            int *len = (int *)malloc(countIsl);
            int *bl = (int *)malloc(size - 1);
            char **path = malloc((countIsl + 1) * sizeof(*path));
            int blAlways = 0;
            int count_i = 0;
            int blocked = 0;
            for (;;)
            {
                count_i = get_route(len, weights, Names, bridges, Names[i], path, bl, &blocked, &blAlways);
                if (count_i == -1) 
                {
                    break;
                }  
                else
                {
                    print_path(path[0], path[count_i - 1], path, len, count_i);
                }
            }
        }
    }
}

