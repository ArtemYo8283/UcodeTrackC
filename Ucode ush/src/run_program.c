#include "ush.h"
pid_t pid;
int pid_counter = 1;
char *stopped_program;//problem v etom
void ctrlZ()
{
    kill(pid, SIGTSTP);
    mx_printstr("\n");
    mx_printstr("[");
    mx_printint(pid_counter);
    mx_printstr("]+  Stopped");
    mx_printstr("                 ");
    mx_printstr(stopped_program);
    mx_printstr("\n");
} 

void run_program(char *info)
{
    char **info_parsed = mx_strsplit(info, ' ');
    int size = mx_count_words(info, ' ');
    char **args = mx_strsplit(info, ' ');
    for(int i = 1; i < size; i++)
    {
        for(int j = 0; j < (int)strlen(info_parsed[i]); j++)
        {
            args[i][j] = info_parsed[i][j];
        }   
    }
    pid = fork();
    stopped_program = malloc(sizeof(info));
    stopped_program = info;
    if(signal(SIGTSTP, ctrlZ))
    {
        pid_counter++;
    }
    if(pid == 0)
    {       
        setpgid(pid, 0);
        execvp(info_parsed[0], args);
        exit(0);
    }
    else                                                                                                                                                      
    {    
        int status = 0;
        waitpid(pid, &status, WUNTRACED);
        kill(pid, SIGKILL);
    }
}

