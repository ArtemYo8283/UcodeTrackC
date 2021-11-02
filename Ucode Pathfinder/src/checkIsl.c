#include "pathfinder.h"

void checkIsl(Bridge *bridge)
{
    for(int i = 0; i < size - 1; i++) //alphabet check
    {
        for(int j = 0; j < mx_strlen(bridge[i].I1); j++)
        {
            if(!mx_isalpha(bridge[i].I1[j]))
            {
                write(2, "error: line ", 12);
                write(2, mx_itoa(i+2), mx_strlen(mx_itoa(i+2)));
                write(2, " is not valid\n", 14);
                exit(-1);
            }
        }
        for(int j = 0; j < mx_strlen(bridge[i].I2); j++)
        {
            if(!mx_isalpha(bridge[i].I2[j]))
            {
                write(2, "error: line ", 12);
                write(2, mx_itoa(i+2), mx_strlen(mx_itoa(i+2)));
                write(2, " is not valid\n", 14);
                exit(-1);
            }
        }
        if(mx_strcmp(bridge[i].I1, bridge[i].I2) == 0)
        {
            write(2, "error: line ", 12);
            write(2, mx_itoa(i+2), mx_strlen(mx_itoa(i+2)));
            write(2, " is not valid\n", 14);
            exit(-1);
        }
    }
    //Count check
    int s = 0;
    for(int i = 0; i < size - 1; i++)
    {
        int flag = 0;
        for (int j = i - 1; j > -1; j--)
        {
            if(mx_strcmp(bridge[i].I1, bridge[j].I1) == 0 || mx_strcmp(bridge[i].I1, bridge[j].I2) == 0)
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
            if(mx_strcmp(bridge[i].I2, bridge[j].I2) == 0 || mx_strcmp(bridge[i].I2, bridge[j].I1) == 0)
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

