#include "pathfinder.h"

int get_Name_id(char **Names, char *Name)
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

Bridge * sort_bridges(Bridge *bridges, char** Names)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size - 1; j++)
        {
            if (get_Name_id(Names, bridges[i].I1) + get_Name_id(Names, bridges[i].I2) > get_Name_id(Names, bridges[j].I1) + get_Name_id(Names, bridges[j].I2))
            {
                struct Bridge tmp = {bridges[i].I1, bridges[i].I2, bridges[i].Distance};
                bridges[i] = bridges[j];
                bridges[j] = tmp;
            }
        }
    }
    return bridges;
}

