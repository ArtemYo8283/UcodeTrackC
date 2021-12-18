#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n)
{
	char *tmp = (char *)s;
	while (n > 0)
    {
		if (*tmp == (char)c)
        {
			return tmp;
        }
		tmp++;
		n--;
	}
	return NULL;
}

