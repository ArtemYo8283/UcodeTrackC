#include "libmx.h"
int mx_count_substr(const char *str, const char *sub)
{
    int i = 0;
    if (sub == NULL)
    {
        return -1;
    }
    else if (str == NULL)
    {
        return -1;
    }
    else if (mx_strlen(str) > mx_strlen(sub) - 1)
    {
        while (*str) 
        {
            if (!mx_strncmp((char *)str, (char *)sub, mx_strlen(sub)))
            {
                i++;
            }
            str++;
        }
        return i;
    }
    else
    {
        return 0;
    }
}

