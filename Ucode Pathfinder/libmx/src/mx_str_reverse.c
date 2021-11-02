#include "libmx.h"

void mx_str_reverse(char *s)
{
    int size = mx_strlen(s);
    for(int i = 0, j = size - 1; i < size/2; i++, j--)
    {
        mx_swap_char(&s[i], &s[j]);
    }
}

