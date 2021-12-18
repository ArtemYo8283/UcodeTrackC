#include "ush.h"

char *find_ush_path(char **commands)
{
    char *pwd = mx_getenv("PWD");
    char *ush_path = mx_strstr(commands[0], "./") ? mx_replace_substr(commands[0], ".", pwd) : strdup(commands[0]);
    return ush_path;
}

void mx_set_shl(void)
{
    char *shlv = mx_getenv("SHLVL");
    char *shlvl = mx_itoa(mx_atoi(shlv) + 1);
    extern char **environ;
    char cwd[PATH_MAX];
    if (getenv("HOME") == NULL)
    {
        setenv("HOME", mx_getenv("HOME"), 1);
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        setenv("PWD", cwd, 1);
    }
    if (getenv("OLDPWD") == NULL)
    {
        setenv("OLDPWD", mx_getenv("PWD"), 1);
    }
    if (getenv("PATH") == NULL)
    {
        setenv("PATH", mx_getenv("PATH"), 1);
    }
    if (getenv("SHLVL") == NULL)
    {
        setenv("SHLVL", "1", 1);
    }
    else
    {
        setenv("SHLVL", shlvl, 1);
    }
    setenv("_", "/usr/bin/env", 1);
}

