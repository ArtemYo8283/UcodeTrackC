#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len)
{
    if (len == 0) 
    {
        return (dst);
    }
    const char *str = src;
    char *str1 = dst;
    do {
        if ((*str1++ = *str++) == 0) 
        {
            while (len != 0)
            {
                *str1++ = 0;
                len--;
            }
            break;
        }
        len--;
    } while (len != 0);
	return (dst);
}

