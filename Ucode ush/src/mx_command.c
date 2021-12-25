#include "ush.h"

void mx_insert_char(Input *input, char sym, int i)
{
    int len = strlen(input->command);
    input->command = realloc(input->command, len + 2);
    for(; i < len + 1; i++)
    {
        char tmp = input->command[i];
        input->command[i] = sym;
        sym = tmp;
    }
    input->command[i] = '\0';
}

void mx_delete_char(Input *input, int i)
{
    int len = strlen(input->command);
    input->command = realloc(input->command, len);
    for(; i < len - 1; i++)
    {
        input->command[i] = input->command[i + 1];
    }
    input->command[i] = '\0';
}

void mx_move_coursor(int num_of_moves, char *side)
{
    char *tmp = mx_strjoin(mx_itoa(num_of_moves), side);
    char *str = mx_strjoin("\033[", tmp);
    mx_printstr(str);
}

void mx_clear_str()
{
    write(STDOUT_FILENO, "\033[2K", 4);
    mx_printstr("\033[G");
}

void mx_line_input(Input *input)
{
    if (input->position != input->length)
    {
        mx_insert_char(input, input->symbol, input->position);
    }
    else if (input->command != NULL)
    {
        input->command = realloc(input->command, input->length + 2);
        input->command[input->length] = (char)input->symbol;
        input->command[input->length + 1] = '\0';
    }
    else
    {
        input->command = mx_strnew(256);
        input->command[input->length] = (char)input->symbol;
    }
    input->length++;
    input->position++;
    if (input->position != input->length)
    {
        mx_clear_str();
        mx_printstr("u$h> ");
        mx_printstr(input->command);
        mx_move_coursor(input->length - input->position, "D");
    }
    else
    {
        mx_printchar((char) input->symbol);
    }
}

char *mx_fill_command(Input *input)
{
    switch (input->symbol)
    {
        case 127:
            if (input->position > 0)
            {
                input->position--;
                input->length--;
                mx_clear_str();
                if (256 > input->length + 8)
                {
                    mx_printstr("u$h> ");
                }
                mx_delete_char(input, input->position);
                if (256 > input->length + 8)
                {
                    mx_printstr(input->command);
                    if (input->position != input->length)
                    {
                        mx_move_coursor(input->length - input->position, "D");
                    }
                }
            }
            break;

        case 13:
            return mx_strtrim(input->command);
            break;

        default:
            if (input->length + 8 > 256)
            {
                mx_printerr("\nush: input string is too long");
            }
            else
            {
                mx_line_input(input);
            }
            break;
    }
    return NULL;
}

