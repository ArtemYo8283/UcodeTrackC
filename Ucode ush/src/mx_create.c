#include "ush.h"

char *ush_path(char **commands)
{
    char *pwd = mx_getenv("PWD");
    char *ush_path = mx_strstr(commands[0], "./") ? mx_replace_substr(commands[0], ".", pwd) : strdup(commands[0]);
    return ush_path;
}

void mx_create_shell()
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

List* list_create()
{
    List *list = malloc(sizeof(List));
    list->data = NULL;
    list->next = NULL;
    list->prev = NULL;
    return list;
}

Ush* mx_create_ush(char **argv)
{
    Ush *ush = malloc(sizeof(Ush));
    ush->command = NULL;
    ush->history = NULL;
    ush->ush_path = ush_path(argv);
    ush->history =  list_create();
    ush->prev_pwd = mx_getenv("PWD");
    return ush;
}

Input *mx_create_input()
{
    Input *input = malloc(sizeof(Input));
    input->length = 0;
    input->command = mx_strnew(1);
    input->ctrl_c = 0;
    input->position = 0;
    input->symbol = '\0';
    input->symbol_arr = (char *)&input->symbol;
    return input;
}

