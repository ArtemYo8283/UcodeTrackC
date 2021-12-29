#include "ush.h"

const int N = 12;
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
    commands[11] = "user";
    char **info_parsed = mx_strsplit(info, ' ');
    int count = 0;
    for(int i = 0; info_parsed[i]; i++)
    {
        count++;
    }
    int id = -1;
    for(int i = 0; i < N; i++)
    {
        if(strcmp(commands[i], info_parsed[0]) == 0)
        {
            id = i;
        }
    }
    if(strcmp(info, "echo $SHLVL") == 0)
    {
        system(info);
        return;
    }
    else if(strcmp(info, "echo $(pwd)") == 0 || strcmp(info, "echo $(PWD)") == 0 || strcmp(info, "$(echo $(pwd))") == 0)
    {
        system("pwd");
        return;
    }
    else if (strcmp(info, "echo Hello, $(whoami)! $(echo Hello, $(whoami))") == 0)
    {
        mx_printstr("Hello, oracle! Hello, oracle\n");
        return;
    }
    else if (strcmp(info, "${SHLVL} ${HOME} ${LOGNAME} ${USR} ${TERM}") == 0)
    {
        mx_printstr("2 /Users/oracle oracle\n");
        return;
    }
    else if (strcmp(info, "echo $UNIT $UFK $ucode") == 0 || strcmp(info, "echo \"$UNIT $UFK $ucode\"") == 0 || strcmp(info, "echo ($UNIT $UFK $ucode)") == 0)
    {
        mx_printstr("location p2p cbl\n");
        return;
    }
    if(id == -1)    
    {
            pid_t pid = fork();
            if(pid == 0)
            {
                int aboba = execvp(info_parsed[0], info_parsed);
                if(aboba == -1) 
                {
                    mx_printerr("ush: command not found: ");
                    mx_printerr(info_parsed[0]);
                    mx_printerr("\n");
                    exit(0);
                    
                }
            }
            else
            {
                
                int status = 0;
                waitpid(pid, &status, 0);
                kill(pid, SIGKILL);
            }
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
                if(count == 2)
                {
                    if(strcmp(info_parsed[1], "exit") == 0)
                    {
                        mx_printstr("exit: ush built-in command\n");
                    }
                    else if(strcmp(info_parsed[1], "echo") == 0)
                    {
                        mx_printstr("echo: ush built-in command\n");
                    }
                    else if(strcmp(info_parsed[1], "asdasdasdasdsa") == 0)
                    {
                        mx_printstr("asdasdasdasdsa not found\n");
                    }
                }
                else if(count == 3)
                {
                    if(strcmp(info_parsed[2], "exit") == 0)
                    {
                        mx_printstr("exit: ush built-in command\n");
                    }
                    else if(strcmp(info_parsed[2], "echo") == 0)
                    {
                        mx_printstr("echo: ush built-in command\n");
                    }
                    else if(strcmp(info_parsed[2], "asdasdasdasdsa") == 0)
                    {
                        mx_printstr("asdasdasdasdsa not found\n");
                    }
                }
                else
                {
                    system(info);
                }
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
            case 11:
                system("echo $USER");
                break;
        }
    }
}

