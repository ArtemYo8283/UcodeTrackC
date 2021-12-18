#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2)
{
    int size = mx_strlen(s1) + mx_strlen(s2);
    int i = mx_strlen(s1);
    for (int j = 0; i < size; i++, j++)
    {
        s1[i] = s2[j];
    }
    s1[i++] = '\0';
    return s1;
}

