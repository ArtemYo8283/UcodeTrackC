#include "pathfinder.h"

char ***parse_str(char *filename)
{
    char *str = mx_file_to_str(filename); //Convert file to str
    if(mx_strlen(str) == 0)
    {
        write(2, "error: file [filename] is empty\n", 32);
        exit(-1);
    }

    char** str_p = mx_strsplit(str, '\n');
    char ***str_p_p = (char***)malloc((mx_count_words(str, '\n'))-1);
    for(int i = 0, j = 1; i < mx_count_words(str, '\n') - 1; i++, j++)
    {
        str_p_p[i] = mx_strsplit(str_p[j], ',');
        mx_print_strarr(str_p_p[i], " ");
    }
    mx_printstr("==================\n");
    for(int i = 0; i < mx_count_words(str, '\n') - 1; i++)
    {
        mx_print_strarr(str_p_p[i], " ");
    }
    return str_p_p;
}

