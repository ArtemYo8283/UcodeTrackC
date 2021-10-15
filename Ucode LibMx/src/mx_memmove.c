#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *buf = malloc(len);
	buf = mx_memcpy(buf, src, len);
	dst = mx_memcpy(dst, buf, len);
	free(buf);
	return dst;
}

