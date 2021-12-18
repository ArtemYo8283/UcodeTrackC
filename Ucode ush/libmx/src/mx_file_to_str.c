#include "libmx.h"
int open_f(const char *a) {
    int x = open(a, 0);
    if (x < 0) {
        return -1;
    }
    return x;
}
char *mx_file_to_str(const char *file)
{
    char *dst = NULL;
    int size = 0;
    char c;
    int f = open_f(file);
    while (read(f, &c, 1))
    {
        size++;
    }
    close(f);
    f = open_f(file);
    dst = mx_strnew(size);
    for (int i = 0; read(f, &c, 1); i++)
    {
        dst[i] = c;
    }
    close(f);
    return dst;
}

