#include "ush.h"

void events(Input *input)
{
    if (input->symbol == 4)
    {
        tcsetattr(0, TCSANOW, &input->savetty);
        mx_printstr("\n");
        exit(0);
    }
    else if (input->symbol == 3)
    {
        input->ctrl_c = 1;
    }
}

char *mx_input_ascii(Input *input)
{
    if (input->symbol != '\r'  && input->symbol != '\t' && input->symbol < 32)
    {
        events(input);
        return NULL;
    }
    else
    {
        return mx_fill_command(input);
    }
}

void mx_input_non_ascii(Input *input, Ush *ush)
{
    if (input->symbol == 27)
    {
        if (input->symbol_arr[2] == 67)
        {
            if (input->position < input->length)
            {
                mx_printstr("\033[C");
                input->position++;
            }
        }
        else if (input->symbol_arr[2] == 68)
        {
            if (input->position > 0)
            {
                mx_printstr("\033[D");
                input->position--;
            }
        }
        else if (input->symbol_arr[2] == 65)
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
                input->position = strlen(input->command);
                input->length = strlen(input->command);
            }
        }
        else if (input->symbol_arr[2] == 66)
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
                input->position = strlen(input->command);
                input->length = strlen(input->command);
            }
        }
    }
}

char *mx_cycle(Input *input, int *flag, Ush *ush, char *str)
{
    int i = read(0, &input->symbol, 4);
    if(i == EOF)
    {
        exit(0);
    }
    for (int j = 0; j < i; j++)
    {
        input->symbol = input->symbol_arr[j];
        if (input->symbol <= 127 && input->symbol != 27)
        {
            str = mx_input_ascii(input);
        }
        else
        {
            *flag = 0;
            mx_input_non_ascii(input, ush);
        }
        if (input->symbol < 32)
        {
            break;
        }
    }
    return str;
}

char *mx_input(Ush *ush)
{
    char *str = NULL;
    struct termios savetty;
    if (!isatty(0))
    {
        size_t size = 32;
        char *buffer = NULL;
        getline(&buffer, &size, stdin);
        str = mx_strndup(buffer, strlen(buffer) - 1);
    }
    else
    {
        mx_printstr("u$h> ");
        struct termios term;
        tcgetattr(0, &term);
        savetty = term;
        term.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
        term.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
        term.c_cflag &= ~(CSIZE | PARENB);
        term.c_cflag |= CS8;
        term.c_iflag &= IGNCR;
        term.c_cc[VMIN] = 1;
        term.c_cc[VERASE] = 127;
        tcsetattr(0, TCSAFLUSH, &term);
        char *tmp = NULL;
        int flag = 0;
        Input *input = mx_create_input();
        input->savetty = savetty;
        while (input->symbol != '\r' && input->ctrl_c != 1)
        {
            str = mx_cycle(input, &flag, ush, str);
            if (input->length > 0)
            {
                tmp = mx_add_history(input, &flag, ush);
            }
        }
        if (ush->history->next != NULL)
        {
            mx_sort_history(ush, tmp);
        }
        mx_printstr("\n");
        tcsetattr(0, TCSANOW, &savetty);
    }
    if (ush->history->data != NULL)
    {
        ush->history = mx_addelem(ush->history);
    }
    return str;
}

