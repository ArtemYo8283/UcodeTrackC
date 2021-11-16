#include <uls.h>

void add_flags(Flag **fl, char flag)
{
    if (flag == 'T')
    {
        (*fl)->T = 1;
    }
    else if (flag == 'G' && isatty(1))
    {
        (*fl)->G = 1;
    }
    else if (flag == 'c')
    {
        (*fl)->u = 0;
        (*fl)->c = 1;
    }
    else if (flag == 't')
    {
        (*fl)->t = 1;
    }
    else if (flag == 'u')
    {
        (*fl)->u = 1;
        (*fl)->c = 0;
    }
    else
    {
        if (flag == 'S')
        {
            (*fl)->S = 1;
        }
        else if (flag == 'r' && (*fl)->r != -1)
        {
            (*fl)->r = 0;
        }
        else if (flag == 'G' && !isatty(1))
        {
            (*fl)->G = 0;
        }
        else if (flag == 'R')
        {
            (*fl)->R = 1;
        }
        else if (flag == 'A')
        {
            (*fl)->A = 1;
        }
        else if (flag == 'g')
        {
            (*fl)->g = 1;
            (*fl)->l = 1;
        }
        else if (flag == 'o')
        {
            (*fl)->o = 1;
            (*fl)->l = 1;
        }
        else 
        {
            (*fl)->x = 0;
            (*fl)->l = 0;
            (*fl)->C = 0;
            (*fl)->m = 0;
            (*fl)->force = 0;
            switch(flag)
            {
                case 'l':
                    (*fl)->l = 1;
                break;
                
                case 'C':
                    (*fl)->C = 1;
                break;

                case '1':
                    (*fl)->force = 1;
                break;

                case 'x':
                    (*fl)->x = 1;
                break;

                case 'm':
                    (*fl)->m = 1;
                break;

                default:
                    write(2, "uls: illegal option -- ", 24);
                    write(2, &flag, 1);
                    write(2, "\nusage: uls [-ACGRSTcfglmortux1] [file ...]\n", 45);
                    free(*fl);
                    fl = NULL;
                    exit(1);
                break;
            }
        }
    }
} 

Flag *get_flags(char *argv[], int *i)
{
    Flag *fl = malloc(sizeof(Flag));
    fl->r = 1;
    while(argv[(*i)])
    {
        if (argv[(*i)][0] == '-')
        {
            if (argv[(*i)][1] == '-') 
            {
                (*i)++;
                break;
            }
            else if (argv[(*i)][1] == '\0')
            {
                break;
            }
            for (int j = 1; argv[(*i)][j]; j++)
            {
                add_flags(&fl, argv[(*i)][j]);
            }
        }
        else
        {
            break;
        }
        (*i)++;
    }
    return fl;
}

