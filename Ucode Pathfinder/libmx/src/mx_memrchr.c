#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n)
{
	char *tmp = (char *)s + mx_strlen(s);
	while (n)
    {
		n--;
		if (*tmp == (char)c)
        {
			return tmp;
        }
		tmp--;
	}
	return NULL;
}

