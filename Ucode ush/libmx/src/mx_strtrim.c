#include "libmx.h"
char *mx_strtrim(const char *str)
{
    int count = mx_strlen(str);
    while (mx_isspace(*str))
    {
        str++;
    }
    while (mx_isspace(str[count - 1]))
    {
        count--;
    }
    char *new = mx_strndup(str, count);
    return (char *)new;
}

