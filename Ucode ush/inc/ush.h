#pragma once 
#include "libmx.h"
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <termcap.h>
#include <time.h>
#include <pwd.h>

typedef struct Input 
{
    int ctrl_c;
    unsigned char symbol;
    char *symbol_arr;
    int length;
    int position;
    char *command;
    struct termios savetty;
} Input;

typedef struct List 
{
    struct List *next;
    struct List *prev;
    char *data;
} List;

typedef struct Ush 
{
    char *command;
    struct List *history;
    char *ush_path;
    char *prev_pwd;
    char *pwd;
} Ush;

typedef struct Process
{
    int pid;// конкретныйй процесс
    int Ppid; // родительский процесс
    int Pgid; //группа процессов 
    int SID; // сессия
} Process;

int mx_find_flag(char *flags, char *arg);
bool mx_check_link(char **arg, int flag, int link);
char *mx_getenv(char *var);
void run_commands(char *info, Ush *ush);
void run_program(char *info);

void mx_create_shell(void);
Ush* mx_create_ush(char **argv);
Input *mx_create_input();

int mx_cd(char **args, Ush *ush);
int mx_make_path(char *path, Ush *ush, int flag);

void mx_pwd(char **args, Ush *ush);

char *mx_input(Ush *ush);

char *mx_fill_command(Input *input);
void mx_clear_str();

void mx_echo(char **args);

List *mx_addelem(List *history);
void mx_sort_history(Ush *ush, char *tmp);
char *mx_add_history(Input *input, int *flag, Ush *ush);
List* lst_create();

