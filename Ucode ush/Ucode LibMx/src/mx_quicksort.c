#include "libmx.h"

int mx_quicksort(char **arr, int left, int right) 
{
    int i = 0;
    int first = left;
    int last = right;
    if(arr == NULL)
    {
        return -1;
    }
    else if (left < right) 
    {
        int middle = (first + last) / 2;
        while (first <= last) 
        {
            while (mx_strlen(arr[first]) < mx_strlen(arr[middle])) 
            {
                first++;
            }
            while (mx_strlen(arr[last]) > mx_strlen(arr[middle])) 
            {
                last--;
            }
            char *tmp = arr[first];
            arr[first] = arr[last];
            arr[last] = tmp;
            first++;
            last--;
            i++;
        }
        mx_quicksort(arr, left, last);
        mx_quicksort(arr, first, right);
    }
    return i;
}

