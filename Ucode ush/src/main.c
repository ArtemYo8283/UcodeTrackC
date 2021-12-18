#include "ush.h"

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
    mx_set_shl();
    while (true)
    { 
        ush->command = mx_process_input(ush);
        if (ush->command != NULL && strlen(ush->command) > 0)
        {
            if(ush->command[0] == '.' && ush->command[1] == '/')
            {
                run_program(ush->command);
            }
            else
            {
                run_commands(ush->command, ush);
            }
        }
    }
    return 0;
}



