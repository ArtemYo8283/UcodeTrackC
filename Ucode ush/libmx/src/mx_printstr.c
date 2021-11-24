#include "libmx.h"

void mx_printstr(char *s)
{
    write(1, s, mx_strlen(s));
}

