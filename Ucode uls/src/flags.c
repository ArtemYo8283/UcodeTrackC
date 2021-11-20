#include <uls.h>

void add_flags(Flag **flags, char flag)
{
    if (flag == 'T')
    {
        (*flags)->T = 1;
    }
    else if (flag == 'G' && isatty(1))
    {
        (*flags)->G = 1;
    }
    else if (flag == 'c')
    {
        (*flags)->u = 0;
        (*flags)->c = 1;
    }
    else if (flag == 't')
    {
        (*flags)->t = 1;
    }
    else if (flag == 'u')
    {
        (*flags)->u = 1;
        (*flags)->c = 0;
    }
    else
    {
        if (flag == 'S')
        {
            (*flags)->S = 1;
        }
        else if (flag == 'r' && (*flags)->r != -1)
        {
            (*flags)->r = 0;
        }
        else if (flag == 'G' && !isatty(1))
        {
            (*flags)->G = 0;
        }
        else if (flag == 'R')
        {
            (*flags)->R = 1;
        }
        else if (flag == 'A')
        {
            (*flags)->A = 1;
        }
        else if (flag == 'g')
        {
            (*flags)->g = 1;
            (*flags)->l = 1;
        }
        else if (flag == 'o')
        {
            (*flags)->o = 1;
            (*flags)->l = 1;
        }
        else 
        {
            (*flags)->x = 0;
            (*flags)->l = 0;
            (*flags)->C = 0;
            (*flags)->m = 0;
            (*flags)->force = 0;
            switch(flag)
            {
                case 'l':
                    (*flags)->l = 1;
                break;
                
                case 'C':
                    (*flags)->C = 1;
                break;

                case '1':
                    (*flags)->force = 1;
                break;

                case 'x':
                    (*flags)->x = 1;
                break;

                case 'm':
                    (*flags)->m = 1;
                break;

                default:
                    write(2, "uls: illegal option -- ", 24);
                    write(2, &flag, 1);
                    write(2, "\nusage: uls [-ACGRST@acefhlmprtu1] [file ...]\n", 45);
                    free(*flags);
                    flags = NULL;
                    exit(1);
                break;
            }
        }
    }
} 

Flag * Flag_grab_flags(char *argv[], int *i)
{
    Flag *flags = malloc(sizeof(Flag));
    flags->r = 1;
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
                add_flags(&flags, argv[(*i)][j]);
            }
        }
        else
        {
            break;
        }
        (*i)++;
    }
    return flags;
}

