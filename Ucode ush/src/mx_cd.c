#include "ush.h"

void mx_setenv_ush(char *arg, Ush *ush)
{
    if (mx_strlen(arg) != 1 && arg[mx_strlen(arg) - 1] == '/')
    {
        arg[mx_strlen(arg) - 1] = '\0';
    }
    if (strcmp(arg, ush->pwd_l) != 0)
    {
        ush->pwd_l = strdup(arg);
    }
    setenv("PWD", arg, 1);
}

int handle_path(char *path, int flag, Ush *ush)
{
    char *tmp = strdup(path);
    int link = mx_check_symlink(&tmp, flag, 1);
    if (flag == 2 && link == 1)
    {
        fprintf(stderr, "cd: not a directory: %s\n", path);
        return 1;
    }
    else if (strcmp(tmp, "-") == 0)
    {
        if (mx_getenv("OLDPWD") != NULL)
        {
            mx_setenv_ush(mx_getenv("OLDPWD"), ush);
            setenv("OLDPWD", ush->pwd_l, 1);
        }
        else
        {
            fprintf(stderr, "ush: cd: OLDPWD not set\n");
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
        setenv("OLDPWD", ush->pwd_l, 1);
        mx_setenv_ush(arg, ush);
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
                if ((flag = mx_find_flag("Ps", args[i])) > 0)
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
    mx_setenv_ush(ush->pwd, ush);
    mx_file_exist(path) == 0 ? fprintf(stderr, "cd: no such file or directory: %s\n", path) : fprintf(stderr, "cd: not a directory: %s\n", path);
    return 1;
}

char *previous_dir(Ush *ush, int flag)
{
    char *prev_dir = flag != 1 ? strdup(ush->pwd_l) : mx_getenv("PWD");
    for (int i = mx_strlen(prev_dir) - 1; i >= 0; i--)
    {
        if (prev_dir[i] == '/')
        {
            prev_dir[i] = '\0';
            break;
        }
        prev_dir[i] = '\0';
    }
    if (mx_strlen(prev_dir) == 0)
    {
        prev_dir = strdup("/");
    }
    return prev_dir;
}

char *absolute_path(char *path, Ush *ush)
{
    char *tmp = mx_strjoin(ush->pwd_l, "/");
    return strcmp(ush->pwd_l, "/") != 0 ? mx_strjoin(tmp, path) : mx_strjoin("/", path); 
    
}

int create_new_path(char **tokens, char *path, Ush *ush, int flag)
{
    for (int i = 0; tokens[i] != NULL; i++)
    {
        char *value = NULL;
        if (strcmp(tokens[i], "..") == 0)
        {
            value = previous_dir(ush, flag);
        }
        else if (strcmp(tokens[i], ".") == 0)
        {
            value = flag != 1 ? strdup(ush->pwd_l) : mx_getenv("PWD");
        }
        else
        {
            value = absolute_path(tokens[i], ush);
        }
        if (chdir(value) != -1)
        {
            mx_setenv_ush(value, ush);
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
    ush->pwd = strdup(ush->pwd_l);
    if (path[0] == '/')
    {
        chdir("/");
        mx_setenv_ush("/", ush);
    }
    if (tokens != NULL)
    {
        ret = create_new_path(tokens, path, ush, flag);
    }
    setenv("OLDPWD", ush->pwd, 1);
    return ret;
}

