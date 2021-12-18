#include "ush.h"

bool is_comm_rw(char *str) 
{
    char reserved_words[][5] = {"!", "{", "}", "time"};
    for (int i = 0; i < 4; i++) 
    {
        if (strcmp(str, reserved_words[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

// void check_builtin(char *input, int *ret_flag, int flag) 
// {
//     char *tmp = mx_coomand_in_path(input, mx_getenv("PATH"));
//     if (mx_is_builtin(tmp) != 0) 
//     {
//         printf("%s: shell built-in command\n", input);
//         if (flag == 2 && strcmp(tmp, input) != 0)
//         {
//           printf("%s\n", tmp);  
//         }
//     }
//     else if (strcmp(tmp, input) != 0) 
//     {
//         printf("%s\n", tmp);
//     }
//     else
//     {
//         *ret_flag = 1;
//     }
// }

void check_command(char *input, int *ret_flag, int flag) 
{
    if (is_comm_rw(input) == true)
    {
        printf("%s: shell reserved word\n", input);
    }
    else if (mx_get_char_index(input, '/') != -1) 
    {
        char **path = mx_strsplit(mx_getenv("PATH"), ':');
        for (int i = 0; i < mx_count_arr_el(path); i++) 
        {
            if (mx_get_substr_index(input, path[i]) != -1 && mx_file_exist(input)) 
            {
                if (flag != 1)
                {
                    printf("%s\n", input);
                }
                *ret_flag = 0;
                break;
            }
            *ret_flag = 1;
        }
    }
    // else
    // {
    //     check_builtin(input, ret_flag, flag);
    // }
}

int check_flag_which(char *input, int *flag) 
{
    for (int i = 1; i < mx_strlen(input); i++) 
    {
        if (input[i] == 's' && *flag != 2)
        {
            *flag = 1;
        }
        else if (input[i] == 'a')
        {
            *flag = 2;
        }
        else
        {
            mx_printerr("which: illegal option -- ");
            mx_print_char_err(input[i]);
            mx_printerr("\nusage: which [-as] program ...\n");
            //fprintf(stderr, "which: illegal option -- %c\nusage: which [-as] program ...\n", input[i]);
            return 1;
        }
    }
    return 0;
}

int mx_which(char **input)
{
    int flag = 0;
    int ret_flag = 0;
    if (mx_count_arr_el(input) == 1)
    {
        mx_printerr("usage: which [-as] program ...\n");
        //fprintf(stderr, "usage: which [-as] program ...\n");
        return 1;
    }
    for (int i = 1; i < mx_count_arr_el(input); i++)
    {
        if (strcmp(input[i], "--") == 0)
        {
            flag = 3;
        }
        else if (input[i][0] == '-' && flag < 3)
        {
            if ((ret_flag = check_flag_which(input[i], &flag)) == 0)
            {
                continue;
            }
        }
        check_command(input[i], &ret_flag, flag);
    }
    return ret_flag;
}

