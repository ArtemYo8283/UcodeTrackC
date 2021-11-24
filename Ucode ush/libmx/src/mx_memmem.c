#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
	if (big_len > little_len - 1 && big_len > 0 && little_len > 0)
    {
		char *location = (char *)big;
		char *data = (char *)little;
		while (*location)
        {
			if (mx_memcmp(location, data, little_len - 1) == 0)
            {
				return location;
            }
			location++;
		}
	}
	return NULL;
}

