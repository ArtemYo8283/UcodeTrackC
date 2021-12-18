#include "ush.h"

int mx_find_flag(char *flags, char *arg)
{
    int flag = 0;
    for (int i = 0; i < (int)strlen(flags); i++)
    {
        for (int j = 1; j < (int)strlen(arg); j++)
        {
            if (arg[j] == flags[i])
            {
                if (i + 1 > flag)
                {
                    flag = i + 1;
                }
                break;
            }
        }
    }
    return flag;
}

