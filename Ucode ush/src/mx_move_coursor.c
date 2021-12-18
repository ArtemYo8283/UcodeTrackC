#include "ush.h"

void mx_insert_char(Input *input, char sym, int index)
{
    int len = mx_strlen(input->command);
    input->command = realloc(input->command, len + 2);
    for (; index < len + 1; index++)
    {
        char tmp = input->command[index];
        input->command[index] = sym;
        sym = tmp;
    }
    input->command[index] = '\0';
}

void mx_delete_char(Input *input, int index)
{
    int len = mx_strlen(input->command);
    input->command = realloc(input->command, len);
    for (; index < len - 1; index++)
    {
        input->command[index] = input->command[index + 1];
    }
    input->command[index] = '\0';
}

void mx_move_coursor(int num_of_moves, char *side)
{
    char *str2 = "\033[";
    char *str1 = mx_itoa(num_of_moves);
    char *tmp = mx_strjoin(str1, side);
    char *str = mx_strjoin(str2, tmp);
    mx_printstr(str);
}

