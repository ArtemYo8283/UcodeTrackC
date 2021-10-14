#include "libmx.h"

char *mx_strdup(const char *s1)
{
    int size = mx_strlen(s1);
    char *str = mx_strnew(size);
    mx_strcpy(str, s1);
    return str;
}

