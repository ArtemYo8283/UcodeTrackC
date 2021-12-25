#include "ush.h"

void mx_pwd_err(char c, int *flag)
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

void mx_parse_pwd(char **args, int *flag)
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
            for (int j = 1; j < (int)strlen(args[i]); j++)
            {
                if (args[i][j] != 'L' && args[i][j] != 'P')
                {
                    mx_pwd_err(args[i][j], flag);
                    break;
                }
            }
            if (*flag == 3)
            {
                break;
            }
            *flag = mx_find_flag("LP", args[i]);
            if(*flag > 0)
            {
                continue;
            }
        }
        else
        {
            mx_pwd_err('\0', flag);
        }
    }
}

char* path_link(char *arg)
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

bool mx_check_link(char **arg, int flag, int link)
{
    struct stat *st = malloc(sizeof(struct stat));
    bool is_link = false;
    lstat(*arg, st);
    if ((st->st_mode & S_IFMT) == S_IFLNK)
    {
        is_link = true;
        if (flag == link)
        {
            (*arg) = path_link(*arg);
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
    int flag = 0;
    bool is_link = false;
    char *position = NULL;
    mx_parse_pwd(args, &flag);
    if (flag != 2)
    {
        position = strdup(ush->prev_pwd);
    }
    else
    {
        position = mx_getenv("PWD");
        is_link = mx_check_link(&position, flag, 2);
    }
    if (flag != 3)
    {
        mx_printstr(position);
        mx_printchar('\n');
    }
}

