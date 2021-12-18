#include "ush.h"

void mx_clear_str()
{
    write(STDOUT_FILENO, "\033[2K", 4);
    mx_printstr("\033[G");
}

void case_backspace(Input *input)
{
    if (input->coursor_position > 0)
    {
        input->coursor_position--;
        input->len--;
        mx_clear_str();
        if (input->term_width > input->len + 8)
        {
            mx_printstr("u$h> ");
        }
        mx_delete_char(input, input->coursor_position);
        if (input->term_width > input->len + 8)
        {
            mx_printstr(input->command);
            if (input->coursor_position != input->len)
            {
                mx_move_coursor(input->len - input->coursor_position, "D");
            }
        }
    }
}

void one_line_input(Input *input)
{
    if (input->coursor_position != input->len)
    {
        mx_insert_char(input, input->input_ch, input->coursor_position);
    }
    else if (input->command != NULL)
    {
        input->command = realloc(input->command, input->len + 2);
        input->command[input->len] = (char) input->input_ch;
        input->command[input->len + 1] = '\0';
    }
    else
    {
        input->command = mx_strnew(1000);
        input->command[input->len] = (char) input->input_ch;
    }
    input->len++;
    input->coursor_position++;
    if (input->coursor_position != input->len)
    {
        mx_clear_str();
        mx_printstr("u$h> ");
        mx_printstr(input->command);
        mx_move_coursor(input->len - input->coursor_position, "D");
    }
    else
    {
        mx_printchar((char) input->input_ch);
    }
}

void case_default(Input *input)
{
    if (input->len + 8 > input->term_width)
    {
        mx_printerr("\nush: input string is too long");
        input->term_width = 0;
    }
    else
    {
        one_line_input(input);
    }
}

char *mx_fill_command(Input *input)
{
    switch (input->input_ch)
    {
        case MX_BACKSPACE:
            case_backspace(input);
            break;

        case MX_ENTER:
            return mx_strtrim(input->command);
            break;

        default:
            case_default(input);
            break;
    }
    return NULL;
}

