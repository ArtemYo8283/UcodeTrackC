#pragma once
#include "libmx.h"
#include <errno.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <time.h>

#define LS_COLOR_RED        "\x1b[31m"
#define LS_COLOR_RESET      "\x1b[0m"

typedef struct Flag
{
    int l;
    int C;
    int x;
    int R;
    int r;
    int t;
    int u;
    int c;
    int S;
    int a;
    int A;
    int force;
    int m;
    int G;
    int T;
    int g;
    int o;
    int Flags;
}   Flag;

typedef struct Size
{
    int lnk;
    int size;
    int group;
    int usr;
    bool is_dev;
}   Size;

typedef struct List
{
    char *name;
    char *path;
    char *err;
    struct stat info;
    struct List **open;
}   List;

typedef struct Type
{
    int n_f;
    int n_d;
    int n_e;
    int i;
}   Type;
Flag * Flag_grab_flags(char *argv[], int *i);
void join_str(char **res, char *s2);
void printstr_in_color(List *args);
int Names_lenght_max(List **names);
void print_tab(int len, int maxlen);
List ** list_grab_names(int argc, char **argv, int i);
List ** list_grab_flags(List ***args, Flag *flags);
void openDirectory(List ***names, Flag *flags);
void outputAll(List ***args, Flag *flags);
void sorting(List ***disp, Flag *flags);
void print_chmod(List *print);
void print_size(List *print, Size *size);
void print_sl(List *print);
void output_menu(List ***names, Flag *flags, int flag);
void flag_c_output(List **names);
void flag_g_output(List **names, Flag *flags);
void long_output(List **names, Flag *flags, int flag);




