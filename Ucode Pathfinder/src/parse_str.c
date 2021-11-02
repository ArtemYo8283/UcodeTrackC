#include "pathfinder.h"

char*** parse_str(char *filename)
{
    char *str = mx_file_to_str(filename); //Convert file to str
    if(mx_strlen(str) == 0)
    {
        write(2, "error: file ", 12);
        write(2, filename, mx_strlen(filename));
        write(2, " is empty\n", 10);
        exit(-1);
    }

    size = mx_count_words(str, '\n');
    char** str_p1 = mx_strsplit(str, '\n');

    for(int i = 0; i < mx_strlen(str_p1[0]); i++) //Check valid of first line
    {
        if(!mx_isdigit(str_p1[0][i]))
        {
            write(2, "error: line 1 is not valid\n", 27);
            exit(-1);
        }
    }
    countIsl = mx_atoi(str_p1[0]);
    if(countIsl < 1)
    {
        write(2, "error: line 1 is not valid\n", 27);
        exit(-1);
    }

    for(int i = 1; i < size; i++) //Check
    { 
        if(str_p1[i][mx_strlen(str_p1[i])-1] == ',' || str_p1[i][0] == ',')
        {
            write(2, "error: line ", 12);
            write(2, mx_itoa(i+1), mx_strlen(mx_itoa(i+1)));
            write(2, " is not valid\n", 14);
            exit(-1);
        }
    } 
    for(int i = 1; i < size; i++) //Check
    { 
        int c1 = 0;
        int c2 = 0;
        for(int j = 0; j < mx_strlen(str_p1[i]); j++)
        {
            if(str_p1[i][j] == ',')
            {
                c1++;
            }
            if(str_p1[i][j] == '-')
            {
                c2++;
            }
        }
        if(c1 != 1 || c2 != 1)
        {
            write(2, "error: line ", 12);
            write(2, mx_itoa(i+1), mx_strlen(mx_itoa(i+1)));
            write(2, " is not valid\n", 14);
            exit(-1);
        }
    }
    
    char*** stri = (char***)malloc(size);   //Set memmory for 3D array
    for (int i = 0; i < size; i++)
    {
        stri[i] = (char**) malloc(size);
        for(int j = 0; j < size; j++)
        {
            stri[i][j] = (char*) malloc(size);
        }
    }
    int id = -1;
    for(int i = 1; i < size; i++)
    {
        id = -1;
        for(int j = 0; j < mx_strlen(str_p1[i]); j++)
        {
            if(str_p1[i][j] == ',')
            {
                id = j;
            }
        }
        if(id == -1)
        {
            write(2, "error: line ", 12);
            write(2, mx_itoa(i+1), mx_strlen(mx_itoa(i+1)));
            write(2, " is not valid\n", 14);
            exit(-1);
        }
    }
    for(int i = 1, j = 0; i < size; i++, j++) //Parse str
    {
        stri[j] = mx_strsplit(str_p1[i], ',');
    }
    mx_del_strarr(&str_p1);
    return stri;
}

