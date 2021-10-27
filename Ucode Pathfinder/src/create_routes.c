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
        for(int j = i + 1; j < countIsl; j++)
        {
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
            }
            char* tmp1 = (char*)malloc(mx_strlen(Names[i]));
            char* tmp2 = (char*)malloc(mx_strlen(Names[j]));
            tmp1 = mx_strcpy(tmp1, Names[i]);
            tmp2 = mx_strcpy(tmp2, Names[j]);
            struct Bridge *tmpB = malloc((countIsl * 2 -1) * sizeof(Bridge));
            int sizetmpB = 0;
            for(int k = 0; k < size - 1; k++) // Не существующий путь А - Д
            {
                if((mx_strcmp(bridges[k].I1, tmp1) == 0 && mx_strcmp(bridges[k].I2, tmp2) != 0))
                {
                    sizetmpB++;
                    tmpB[sizetmpB - 1] = bridges[k];    
                    tmp1 = mx_strcpy(tmp1, bridges[k].I2);
                }
                else if(mx_strcmp(bridges[k].I1, tmp2) != 0 && mx_strcmp(bridges[k].I2, Names[i]) == 0)
                {
                    sizetmpB++;
                    tmpB[sizetmpB - 1] = bridges[k];    
                    tmp1 = mx_strcpy(tmp1, bridges[k].I1);
                }
                else if(
                    (mx_strcmp(bridges[k].I1, tmp1) == 0 && mx_strcmp(bridges[k].I2, tmp2) == 0) ||
                    (mx_strcmp(bridges[k].I1, tmp2) == 0 && mx_strcmp(bridges[k].I2, tmp1) == 0)
                    )
                {
                    P_size++;
                    pathes = realloc(pathes, P_size * sizeof(Path));
                    struct Path tmp = {Names[i], Names[j], tmpB, sizetmpB};
                    pathes[P_size - 1] = tmp;
                    break;
                }
            }
        }
    }
    return pathes;
}


