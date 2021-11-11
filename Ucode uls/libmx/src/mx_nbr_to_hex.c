#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long tmp = nbr;
    int count = 0;
    while (tmp)
    {
        tmp /= 16;
        count++;
    }
    int buff;
    char *str = malloc(count);

    if (nbr == 0)
    {
        return mx_strcpy(str, "0");
    }
    while (nbr)
    {
        buff = nbr % 16;
        if (buff < 10)
        {
            count--;
            str[count] = 48 + buff;
        }
        if (buff > 9)
        {
            count--;
            str[count] = 87 + buff;
        }
        nbr /= 16;
    }
    return str;
}

