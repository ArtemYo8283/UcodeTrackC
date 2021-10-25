#include "pathfinder.h"

void checkIsl(Path *path)
{
    for(int i = 0; i < size - 1; i++) //alphabet check
    {
        for(int j = 0; j < mx_strlen(path[i].I1); j++)
        {
            if(!mx_isalpha(path[i].I1[j]))
            {
                write(2, "error: line ", 12);
                write(2, mx_itoa(i+2), mx_strlen(mx_itoa(i+2)));
                write(2, " is not valid\n", 14);
                exit(-1);
            }
        }
        for(int j = 0; j < mx_strlen(path[i].I2); j++)
        {
            if(!mx_isalpha(path[i].I1[j]))
            {
                write(2, "error: line ", 12);
                write(2, mx_itoa(i+2), mx_strlen(mx_itoa(i+2)));
                write(2, " is not valid\n", 14);
                exit(-1);
            }
        }
        if(strcmp(path[i].I1, path[i].I2) == 0)
        {
            write(2, "error: line ", 12);
            write(2, mx_itoa(i+2), mx_strlen(mx_itoa(i+2)));
            write(2, " is not valid\n", 14);
            exit(-1);
        }
    }
    //Count check
    char **tmp = (char**)malloc(size-1);
    for(int i = 0; i < size - 1; i++)
    {
        tmp[i] = (char*)malloc(256); 
    }
    int s = 0;
    for(int i = 0; i < size - 1; i++)
    {
        int flag = 0;
        for (int j = i - 1; j > -1; j--)
        {
            if(mx_strcmp(path[i].I1, path[j].I1) == 0 || mx_strcmp(path[i].I1, path[j].I2) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            s++;
        }   
    }
    for(int i = 0; i < size - 1; i++)
    {
        int flag = 0;
        for (int j = i - 1; j > -1; j--)
        {
            if(mx_strcmp(path[i].I2, path[j].I2) == 0 || mx_strcmp(path[i].I2, path[j].I1) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            s++;
        }   
    }
    if(s != countIsl)
    {
        write(2, "error: invalid number of islands\n", 33);
        exit(-1);
    }
}

