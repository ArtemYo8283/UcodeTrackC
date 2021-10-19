#include "pathfinder.h"

void parse_str(char *filename)
{
    char *str = mx_file_to_str(filename); //Convert file to str
    if(mx_strlen(str) == 0)
    {
        write(2, "error: file ", 12);
        write(2, filename, mx_strlen(filename));
        write(2, " is empty\n", 10);
        exit(-1);
    }
    int size = mx_count_words(str, '\n'); //7
    char** str_p = mx_strsplit(str, '\n');
    char** str_p1 = mx_strsplit(str, '\n');

    char** dist = (char**)malloc(size - 1);
    char** isl = (char**)malloc(size - 1);

    for(int i = 0, j = 1; i < size -1; i++, j++) //array dist
    {
        dist[i] = strstr(str_p[j], ",")+1; 
        mx_printstr(dist[i]);
        mx_printchar('\n');
    }
    mx_printstr("=========\n");
    for(int i = 0; i < size -1; i++) //array dist
    {
        mx_printstr(str_p[i]);
        mx_printchar('\n');
    }
    mx_printstr("=========\n");
    for(int i = 0, j = 1; i < size - 1; i++, j++) //array dist
    {
        int id = -1;
        for(int k = 0; k < mx_strlen(str_p1[j]); k++)
        {
            if(str_p1[j][k] == ',')
            {
                id = k;
            }
        }
        if(id == -1)
        {
            write(2, "error: line ", 12);
            write(2, mx_itoa(j+1), mx_strlen(mx_itoa(j+1)));
            write(2, " is not valid\n", 15);
            exit(-1);
        }
        strncpy(isl[i], str_p1[j], id); 
        mx_printstr(isl[i]);
        mx_printchar('\n');
    }
}

