#include "ush.h"

void escape_chars(int i, char *str, char *parse_str, int index)
{
    switch (str[i])
    {
        case 'a':
        parse_str[index] = '\a';
            break;

        case 'b':
        parse_str[index] = '\b';
            break;

        case 't':
        parse_str[index] = '\t';
            break;

        case 'n':
        parse_str[index] = '\n';
            break;

        case 'v':
        parse_str[index] = '\v';
            break;

        case 'f':
        parse_str[index] = '\f';
            break;

        case 'r':
        parse_str[index] = '\r';
            break;

        default:
        parse_str[index] = str[i];
            break;
    }
}

int quot_error(int *flag_n, int flag_quot)
{
    if (flag_quot == -1)
    {
        *flag_n = -1;
        mx_printerr("Odd number of quotes.\n");
        return -1;
    }
    return 0;
}

char *fill_parsed_str(char *str, int *flag_n, int flag)
{
    char *parse_str = mx_strnew(1000);
    int flag_quot = 1;
    int index = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\"' || str[i] == '\'')
        {
            flag_quot *= -1;
        }
        else if (flag == 1 && str[i] == '\\' && flag_quot == -1)
        {
            escape_chars(++i, str, parse_str, index++);
        }
        else if (str[i] == '\\' && flag_quot == 1)
        {
            parse_str[index++] = str[++i];
        }
        else
        {
            parse_str[index++] = str[i];
        }
    }
    parse_str[index] = '\0';
    if (quot_error(flag_n, flag_quot) == -1)
    {
        *flag_n = -1;
    }
    return parse_str;
}

int echo_flag(char *arg, int *flag_n)
{
    int flag = 1;
    for (int i = 1; i < (int)strlen(arg); i++)
    {
        if (arg[i] == 'e' && flag != 2)
        {
            flag = 1;
        }
        else if (arg[i] == 'E' || arg[i] == 'e')
        {
            flag = 2;
        }
        else if (arg[i] == 'n')
        {
            *flag_n = 1;
        }
        else
        {
            flag = -1;
            break;
        }
    }
    return flag;
}

char *mx_parse_echo(char **args, int *flag_n)
{
    int flag = 1;
    char *str = NULL;
    for (int i = 1; i < mx_count_arr_el(args); i++)
    {
        if (args[i][0] == '-' && str == NULL && flag != -1)
        {
            flag = echo_flag(args[i], flag_n);
            if (flag >= 0)
            {
                continue;
            }
        }
        if (str == NULL && strcmp(args[i], "") != 0)
        {
            str = strdup(args[i]);
        }
        else if (strcmp(args[i], "") != 0)
        {
            str = realloc(str, strlen(str) + strlen(args[i]) + 2);
            strcat(str, " ");
            strcat(str, args[i]);
        }
    }
    if (str != NULL)
    {
        str = fill_parsed_str(str, flag_n, flag);
    }
    return str;
}

void mx_insert_chars(char **str, char sym, int index)
{
    int len = strlen(*str);
    (*str) = realloc((*str), len + 2);
    for (; index < len + 1; index++)
    {
        char tmp = (*str)[index];
        (*str)[index] = sym;
        sym = tmp;
    }
    (*str)[index] = '\0';
}

char **mx_insertin_arr(char c, char *str_input)
{
    char **arr = mx_strsplit(str_input, c);
    mx_insert_chars(&(arr[1]), c, 0);
    mx_insert_chars(&(arr[1]), c, strlen(arr[1]));
    return arr;
}

char **mx_split_echo(char *input, int check)
{
    char *str_test = mx_strtrim(input);
    free(input);
    input = strdup(str_test);
    char **arr = check == 2 ? mx_insertin_arr('\'', input) : mx_insertin_arr('\"', input);
    char **str = mx_strsplit(arr[0], ' ');
    int size = mx_count_arr_el(str);
    for (int i = 1; arr[i] != NULL; i++)
    {
        str = (char **) realloc(str, 8 * (size + 2));
        str[size++] = strdup(arr[i]);
        str[size] = NULL;
    }
    return str;
}

int mx_check_echo(char **n)
{
    int flag_one = 0;
    int flag_two = 0;
    if (strcmp(n[0], "echo") == 0 || strcmp(n[0], "/bin/echo") == 0)
    {
        for (int i = 0; i < mx_count_arr_el(n); i++)
        {
            if (n[i][0] == '-')
            {
                continue;
            }
            else if (n[i][0] == '$')
            {
                return 0;
            }
            else if (n[i][0] == '\'' || n[i][strlen(n[i]) - 1] == '\'')
            {
                flag_one++;
            }
            else if (n[i][0] == '\"' || n[i][strlen(n[i]) - 1] == '\"')
            {
                flag_two++;
            }
        }
    }
    if (flag_one == 2 && flag_two == 0)
    {
        return 2;
    }
    else if (flag_one == 0 && flag_two == 2)
    {
        return -2;
    }
    return 0;
}

void mx_echo(char **args)
{
    int flag = 0;
    char *str = mx_parse_echo(args, &flag);
    if (str != NULL)
    {
        mx_printstr(str);
    }
    if (flag == 0)
    {
        mx_printchar('\n');
    }
}

