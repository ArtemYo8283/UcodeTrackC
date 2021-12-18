#include "ush.h"

const int N = 11;
void run_commands(char *info, Ush *ush)
{
    char **commands = (char **)malloc(N * 8);
    commands[0] = "export";
    commands[1] = "unset";
    commands[2] = "fg";
    commands[3] = "env";
    commands[4] = "cd";
    commands[5] = "pwd";
    commands[6] = "which";
    commands[7] = "echo";
    commands[8] = "exit";
    commands[9] = "clear";
    commands[10] = "ls";
    char **info_parsed = mx_strsplit(info, ' ');
    int id = -1;
    for(int i = 0; i < N; i++)
    {
        if(strcmp(commands[i], info_parsed[0]) == 0)
        {
            id = i;
        }
    }
    if(id == -1)    
    {
        mx_printerr("ush: command not found: ");
        mx_printerr(info_parsed[0]);
        mx_printerr("\n");
        return;
    }
    else
    {
        switch(id)
        {
            case 0:
                system(info);
                break;

            case 1:
                system(info);
                break;

            case 2:
                system(info);
                break;

            case 3:
                system(info);
                break;

            case 4:
                mx_cd(info_parsed, ush);
                break;

            case 5:
                mx_pwd(info_parsed, ush);
                break;

            case 6:

                break;

            case 7:
                mx_echo(info_parsed);
                break;

            case 8:
                exit(0);
                break;

            case 9:
                system("clear");
                break;

            case 10:
                system(info);
                break;
        }
    }
}

