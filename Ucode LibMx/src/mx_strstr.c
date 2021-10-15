#include "libmx.h"
char *mx_strstr(const char *haystack, const char *needle)
{
    char *h = (char *)haystack;
    char *n = (char *)needle;
    if (!h)
    {
        return NULL;
    }
    else if (!n)
    {
        return NULL;
    }
    else if (!mx_strlen(n))
    {
        return h;
    }
    while (*h) 
    {
        if (!mx_strncmp(h, n, mx_strlen(n)))
        {
            return h;
        }
        h++;
    }
    return NULL;
}

