#include "pathfinder.h"

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
    int *weights = malloc((countIsl + 1) * sizeof(int));
    for (int i = 0; i < countIsl - 1; i++)
    {
        for (int j = i + 1; j < countIsl; j++)
        {
            for (int z = 0; z < countIsl; z++) 
            {
                weights[z] = -1;
            }
            set_weight(&weights, Names, Names[j], 0);
            weight(weights, Names, bridges, countIsl);
            int *len = (int *)malloc(countIsl);
            char **path = malloc((countIsl + 1) * sizeof(*path));
            path[countIsl] = NULL;
            int *bl = (int *)malloc(size - 1);
            int blockedAlways = 0;
            int steps = 0;
            int blocked = 0;
            while (true)
            {
                steps = get_path(len, weights, Names, bridges, countIsl, Names[i], path, bl, &blocked, &blockedAlways);
                if (steps == -1) 
                {
                    break;
                }   
                print_path(path[0], path[steps - 1], path, len, steps);
            }
            free(len);
            free(path);
            free(bl);
        }
    }
}

