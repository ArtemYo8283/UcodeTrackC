#include "ush.h"

void pwd_err(char c, int *flag)
{
    if (c != '\0')
    {
        mx_printerr("ush: pwd: ");
        mx_print_char_err(c);
        mx_printerr(": invalid option\npwd: usage: pwd [-LP]\n");
    }
    else
    {
        mx_printerr("pwd: too many arguments\n");
    }
    *flag = 3;
}

void parse_pwd(char **args, int *flag)
{
    int len = mx_count_arr_el(args);
    for (int i = 1, stop = 0; i < len; i++)
    {
        if (strcmp(args[i], "--") == 0)
        {
            stop = 3;
        }
        if (stop == 0 && args[i][0] == '-')
        {
            for (int y =1; y < mx_strlen(args[i]); y++)
            {
                if (args[i][y] != 'L' && args[i][y] != 'P')
                {
                    pwd_err(args[i][y], flag);
                    break;
                }
            }
            if (*flag == 3)
            {
                break;
            }
            if((*flag = mx_find_flag("LP", args[i])) > 0)
            {
                continue;
            }
        }
        else
        {
            pwd_err('\0', flag);
        }
    }
}

char* path_symlink(char *arg)
{
    char buf[1024];
    ssize_t len = readlink(arg, buf, 1024);
    if (len == -1)
    {
        perror("readlink");
    }
    buf[len] = '\0';
    return buf[0] != '.' ? mx_strjoin("/", buf) : strdup(buf);
}

int mx_check_symlink(char **arg, int flag, int link)
{
    struct stat *st = malloc(sizeof(struct stat));
    int is_link = 0;
    lstat(*arg, st);
    if ((st->st_mode & S_IFMT) == S_IFLNK)
    {
        is_link = 1;
        if (flag == link)
        {
            (*arg) = path_symlink(*arg);
        }
    }
    if (st != NULL)
    {
        free(st);
        st = NULL;
    }
    return is_link;
}

void mx_pwd(char **args, Ush *ush)
{
    int flag = 0, is_link = 0;
    char *position = NULL;
    parse_pwd(args, &flag);
    if (flag != 2)
    {
        position = strdup(ush->pwd_l);
    }
    else
    {
        position = mx_getenv("PWD");
        is_link = mx_check_symlink(&position, flag, 2);
    }
    if (flag != 3)
    {
        mx_printstr(position);
        mx_printchar('\n');
    }
    else
    {
        mx_strdel(&position);
    }
    mx_strdel(&position);
}

