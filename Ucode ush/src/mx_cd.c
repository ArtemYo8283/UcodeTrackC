#include "ush.h"

int mx_find_flag(char *flags, char *str)
{
    int flag = 0;
    for (int i = 0; i < (int)strlen(flags); i++)
    {
        for (int j = 1; j < (int)strlen(str); j++)
        {
            if (str[j] == flags[i])
            {
                if (i + 1 > flag)
                {
                    flag = i + 1;
                }
                break;
            }
        }
    }
    return flag;
}

void mx_setenv(char *str, Ush *ush)
{
    if (strlen(str) != 1 && str[strlen(str) - 1] == '/')
    {
        str[strlen(str) - 1] = '\0';
    }
    if (strcmp(str, ush->prev_pwd) != 0)
    {
        ush->prev_pwd = strdup(str);
    }
    setenv("PWD", str, 1);
}

int handle_path(char *path, int flag, Ush *ush)
{
    char *tmp = strdup(path);
    int link = mx_check_link(&tmp, flag, 1);
    if (flag == 2 && link == 1)
    {
        mx_printerr("cd: not a directory: ");
        mx_printerr(path);
        mx_printerr("\n");
        return 1;
    }
    else if (strcmp(tmp, "-") == 0)
    {
        if (mx_getenv("OLDPWD") != NULL)
        {
            mx_setenv(mx_getenv("OLDPWD"), ush);
            setenv("OLDPWD", ush->prev_pwd, 1);
        }
        else
        {
            mx_printerr("ush: cd: OLDPWD not set\n");
            return 1;
        }
    }
    else
    {
        return mx_make_path(tmp, ush, flag);
    }
    return 0;
}

int mx_cd(char **args, Ush *ush)
{
    int stop = 0;
    int flag = 0;
    int len = mx_count_arr_el(args);
    if (len == 1 || (strcmp(args[1], "--") == 0 && len == 2))
    {
        char *arg = mx_getenv("HOME");
        setenv("OLDPWD", ush->prev_pwd, 1);
        mx_setenv(arg, ush);
    }
    else
    {
        for (int i = 1; i < len; i++)
        {
            if (strcmp(args[i], "--") == 0)
            {
                stop = 3;
                continue;
            }
            if (stop == 0 && args[i][0] == '-')
            {
                flag = mx_find_flag("Ps", args[i]);
                if (flag > 0)
                {
                    continue;
                }
            }
            return handle_path(args[i], flag, ush);
        }
    }
    return 0;
}

int cd_print_error(char *path, Ush *ush)
{
    mx_setenv(ush->pwd, ush);
    if(mx_file_exist(path) == 0) 
    { 
        mx_printerr("cd: no such file or directory: ");
        mx_printerr(path);
        mx_printerr("\n");
    }
    else 
    {
        mx_printerr("cd: not a directory: ");
        mx_printerr(path);
        mx_printerr("\n");
    }
    return 1;
}

char *previous_dir(Ush *ush, int flag)
{
    char *dir = flag != 1 ? strdup(ush->prev_pwd) : mx_getenv("PWD");
    for (int i = strlen(dir) - 1; i >= 0; i--)
    {
        if (dir[i] == '/')
        {
            dir[i] = '\0';
            break;
        }
        dir[i] = '\0';
    }
    if (strlen(dir) == 0)
    {
        dir = strdup("/");
    }
    return dir;
}

int create_new_path(char **tokens, char *path, Ush *ush, int flag)
{
    for (int i = 0; tokens[i] != NULL; i++)
    {
        char *value = NULL;
        if(strcmp(tokens[i], "~") == 0)
        {
            value = mx_strjoin(value, "/Users/"); 
            value = mx_strjoin(value, getlogin()); 
        }
        else if (strcmp(tokens[i], "..") == 0)
        {
            value = previous_dir(ush, flag);
        }
        else if (strcmp(tokens[i], ".") == 0)
        {
            value = flag != 1 ? strdup(ush->prev_pwd) : mx_getenv("PWD");
        }
        else
        {
            value = strcmp(ush->prev_pwd, "/") != 0 ? mx_strjoin(mx_strjoin(ush->prev_pwd, "/"), tokens[i]) : mx_strjoin("/", tokens[i]); 
        }
        if (chdir(value) != -1)
        {
            mx_setenv(value, ush);
        }
        else
        {
            return cd_print_error(path, ush);
        }
    }
    return 0;
}

int mx_make_path(char *path, Ush *ush, int flag)
{
    char **tokens = mx_strsplit(path, '/');
    int ret = 0;
    ush->pwd = strdup(ush->prev_pwd);
    if (path[0] == '/')
    {
        chdir("/");
        mx_setenv("/", ush);
    }
    if (tokens != NULL)
    {
        ret = create_new_path(tokens, path, ush, flag);
    }
    setenv("OLDPWD", ush->pwd, 1);
    return ret;
}

