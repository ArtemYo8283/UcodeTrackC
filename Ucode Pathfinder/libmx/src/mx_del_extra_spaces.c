#include "libmx.h"
char *mx_del_extra_spaces(const char *str) {
    char *tmp = NULL;
    if (!str) 
    {
        return NULL;
    }
    char *istr = mx_strnew(mx_strlen(str));
    for (int i = 0, j = 0; str[i]; i++)
    {
        if (!(mx_isspace(str[i])))
        {
            istr[j] = str[i];
            j++;
        }
        if (!(mx_isspace(str[i])) && mx_isspace(str[i + 1]))
        {
            istr[j] = ' ';
            j++;
        }
    }
    tmp = mx_strtrim(istr);
    mx_strdel(&istr);
    return tmp;
}

