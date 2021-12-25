#include "ush.h"

void newl()
{
    mx_printstr("\n");
}

int main (int argc, char **argv)
{
    if (argc > 1)
    {
        mx_printerr("ush: can't open input file: ");
        mx_printerr(argv[1]);
        mx_printerr("\n");
        exit(-1);
    }
    Ush *ush = mx_create_ush(argv);
    mx_create_shell();
    while (true)
    {
        signal(SIGINT, newl);
        ush->command = mx_input(ush);
        if (ush->command != NULL && strlen(ush->command) > 0)
        {
            if(strlen(ush->command) == 1 && ush->command[0] == ';')
            {
                mx_printerr("ush: syntax error near unexpected token `;'\n");
                continue;
            }
            int count = 0;
            for(int i = 0; ush->command[i]; i++)
            {
                if(ush->command[i] == ';')
                {
                    count++;
                }
            }
            if(count > 0)
            {
                char **split = mx_strsplit(ush->command, ';');
                for(int i = 0; i <= count; i++)
                {
                    if((split[i][0] == '.' && split[i][1] == '/') || (split[i][0] == '.' && split[i][1] == '.' && split[i][2] == '/'))
                    {
                        run_program(split[i]);
                    }
                    else
                    {
                        run_commands(split[i], ush);
                    }
                }
            }
            else
            {     
                if((ush->command[0] == '.' && ush->command[1] == '/') || (ush->command[0] == '.' && ush->command[1] == '.' && ush->command[2] == '/'))
                {         
                    run_program(ush->command);
                }
                else
                {
                    run_commands(ush->command, ush);
                }
            }
        }
        free(ush->command);
    }
    return 0;
}

