#include "libmx.h"
int mx_get_substr_index(const char *str, const char *sub)
{
    int i = 0;
    int count = mx_strlen(sub);
    if (sub && str)
    {
        while (*str)
        {
            if (mx_strncmp(str, sub, count) == 0)
            {
                return i;
            }
            i++;
            str++;
        }
        return -1;
    }
    else
    {
        return -2;
    }
}

