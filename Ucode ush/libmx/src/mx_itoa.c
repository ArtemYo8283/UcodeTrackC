#include "libmx.h"

char *mx_itoa(int number) {
    int tmp = number;
    int count = 0;
    while (tmp)
    {
        tmp /= 10;
        count++;
    }
	char *str = mx_strnew(count);

	if (number == 0)
    {
		return mx_strcpy(str, "0");
    }
	else if (number == -2147483648)
    {
		return mx_strcpy(str, "-2147483648");
    }
    else if (number < 0)
    {
		str[count] = '-';
		number = -number;
	}
	for (int i = 0; i < count; i++)
    {
		str[i] = (number % 10) + '0';
		number /= 10;
	}
	mx_str_reverse(str);
	return str;
}

