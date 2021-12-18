#include "ush.h"

char *inside_cycle(Input *input, int *flag, Ush *ush, char *str)
{
    int i = read(0, &input->input_ch, 4);
    for (int k = 0; k < i; k++)
    {
        input->input_ch = input->input_ch_arr[k];
        if (input->input_ch <= 127 && input->input_ch != 27)
        {
            str = mx_input_ascii(input, ush);
            if (ush->exit_status != -1)
            {
                break;
            }
        }
        else
        {
            *flag = 0;
            mx_input_non_ascii(input, ush);
        }
        if (input->input_ch < 32)
        {
            break;
        }
    }
    return str;
}

char *read_str(struct termios savetty, Ush *ush)
{
    char *ret_str = NULL;
    char *tmp = NULL;
    int flag = 0;
    Input *input = iniInput();
    input->savetty = savetty;
    input->term_width = TERM_WIDTH;
    while (input->input_ch != '\r' && input->ctrl_c != 1 && input->term_width != 0)
    {
        ret_str = inside_cycle(input, &flag, ush, ret_str);
        if (ush->exit_status != -1)
        {
            break;
        }
        if (input->len > 0)
        {
            tmp = mx_add_history(input, &flag, ush);
        }
    }
    if (ush->history->next != NULL)
    {
        mx_sort_history(ush, tmp);
    }
    mx_printstr("\n");
    return ret_str;
}

char *mx_process_input(Ush *ush)
{
    char *str = NULL;
    struct termios savetty;
    size_t bufsize = 32;
    if (!isatty(0))
    {
        char *buffer = NULL;
        getline(&buffer,&bufsize,stdin);
        str = mx_strndup(buffer, mx_strlen(buffer) - 1);
        ush->exit_non_term = 1;
    }
    else
    {
        mx_printstr("u$h> ");
        mx_set_non_canonic(&savetty);
        str = read_str(savetty, ush);
        tcsetattr(0, TCSANOW, &savetty);
    }
    if (ush->history->data != NULL)
    {
        ush->history = mx_addelem(ush->history);
    }
    return str;
}

