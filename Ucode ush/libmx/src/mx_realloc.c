#include "libmx.h"

void *mx_realloc(void *ptr, size_t size)
{
    size_t count = malloc_size(ptr);
    void *tmp = NULL;

    if (size < 1 && ptr)
    {
        free(ptr);
        return NULL;
    }
    else if (!ptr && size)
    {
        return malloc(size);
    }
    if (count > size)
    {
        tmp = (void *)malloc(count);
        size = count;
    }
    else
    {
        tmp = (void *)malloc(size);
    }
    if (!tmp)
    {
        return NULL;
    }
    tmp = mx_memmove(tmp, ptr, size);
    free(ptr);
    return tmp;
}

