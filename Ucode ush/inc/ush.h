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

#define TERM_WIDTH 256
#define MX_RIGHT_ARROW 67
#define MX_LEFT_ARROW 68
#define MX_UP_ARROW 65
#define MX_DOWN_ARROW 66
#define MX_ENTER 13
#define MX_BACKSPACE 127

typedef struct Pid 
{
    int num;
    int index;
    char *str;
    struct Pid *next;
    struct Pid *prev;
} Pid;

typedef struct t_com_sub 
{
    int back_first;
    int back_first_index;
    int back_end;
    int back_end_index;
    int space;
    int space_first_index;
    int space_end_index;
    char *tmp_str;
    char *tmp_data;
    char *cout_execute;
    char *tmp_join;
    int status;
} t_com_sub;

typedef struct Queue 
{
    char *data;
    char operator;
    struct Queue *next;
} Queue;

typedef struct Input 
{
    int ctrl_c;
    unsigned char input_ch;
    char *input_ch_arr;
    int len;
    int term_width;
    int coursor_position;
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
    int return_value;
    int exit_status;
    struct Pid *pids;
    char *str_input;
    int exit_non_term;
    int curr_pid;
    char *pwd_l;
    char *pwd;
} Ush;

typedef struct Redirect 
{
    int fd_return[2];
    int fdout[2];
    int fderr[2];
    int flag;
    char *out;
    char *err;
} Redirect;

int mx_file_exist(char *path);
int mx_find_flag(char *flags, char *arg);
char *mx_coomand_in_path(char *comm, char *str_path);
int mx_check_symlink(char **arg, int flag, int link);
char *mx_getenv(char *var);

void run_commands(char *info, Ush *ush);
void run_program(char *info);

//ush
void mx_set_shl(void);
char *find_ush_path(char **commands);
Ush* mx_create_ush(char **argv);

Input *iniInput();

//cd
int mx_cd(char **args, Ush *ush);
int mx_make_path(char *path, Ush *ush, int flag);

//pwd
void mx_pwd(char **args, Ush *ush);

//which
int mx_which(char **input);

//input
char *mx_process_input(Ush *ush);

//input
char *mx_input_ascii(Input *input, Ush *ush);
void mx_input_non_ascii(Input *input, Ush *ush);
char *mx_fill_command(Input *input);
void mx_clear_str();
void mx_insert_char(Input *input, char sym, int index);
void mx_delete_char(Input *input, int index);
void mx_move_coursor(int num_of_moves, char *side);

void mx_set_non_canonic(struct termios *savetty);

//echo
void mx_echo(char **args);

//history
List *mx_addelem(List *history);
void mx_sort_history(Ush *ush, char *tmp);
char *mx_add_history(Input *input, int *flag, Ush *ush);
List* lst_create();

