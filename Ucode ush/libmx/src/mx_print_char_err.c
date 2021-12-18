#include "libmx.h"

void mx_print_char_err(char c)
{
    write(2, &c, 1);
}

