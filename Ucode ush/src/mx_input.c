#include "ush.h"

void events(Input *input, int *exit_status)
{
    if (input->input_ch == 4)
    {
        tcsetattr(0, TCSANOW, &input->savetty);
        *exit_status = 1;
    }
    else if (input->input_ch == 3)
    {
        input->ctrl_c = 1;
    }
}

char *mx_input_ascii(Input *input, Ush *ush)
{
    if (input->input_ch != '\r'  && input->input_ch != '\t' && input->input_ch < 32)
    {
        events(input, &ush->exit_status);
        return NULL;
    }
    else
    {
        return mx_fill_command(input);
    }
}

void right_arrow(Input *input)
{
    if (input->coursor_position < input->len)
    {
        mx_printstr("\033[C");
        input->coursor_position++;
    }
}

void left_arrow(Input *input)
{
    if (input->coursor_position > 0)
    {
        mx_printstr("\033[D");
        input->coursor_position--;
    }
}

void up_arrow(Input *input, Ush *ush)
{
    if (ush->history->prev != NULL && strlen(ush->history->prev->data) > 0)
    {
        ush->history = ush->history->prev;
        mx_clear_str();
        mx_printstr("u$h> ");
        if (ush->history->data != NULL)
        {
            input->command = strdup(ush->history->data);
            mx_printstr(input->command);
        }
        input->coursor_position = mx_strlen(input->command);
        input->len = mx_strlen(input->command);
    }
}

void down_arrow(Input *input, Ush *ush)
{
    if (ush->history->next != NULL)
    {
        ush->history = ush->history->next;
        mx_clear_str();
        mx_printstr("u$h> ");
        if (ush->history->data != NULL)
        {
            input->command = strdup(ush->history->data);
            mx_printstr(input->command);
        }
        if (ush->history->data == NULL)
        {
            input->command = malloc(256);
        }
        input->coursor_position = mx_strlen(input->command);
        input->len = mx_strlen(input->command);
    }
}

void mx_input_non_ascii(Input *input, Ush *ush)
{
    if (input->input_ch == 27)
    {
        if (input->input_ch_arr[2] == MX_RIGHT_ARROW)
        {
            right_arrow(input);
        }
        else if (input->input_ch_arr[2] == MX_LEFT_ARROW)
        {
            left_arrow(input);
        }
        else if (input->input_ch_arr[2] == MX_UP_ARROW )
        {
            up_arrow(input, ush);
        }
        else if (input->input_ch_arr[2] == MX_DOWN_ARROW)
        {
            down_arrow(input, ush);
        }
    }
}

