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
    int Flags;
    int G;
    int T;
    int g;
    int o;
    int ex;
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

Flag *get_flags(char *argv[], int *i);

void mx_join(char **res, char *s2);
void mx_printstr_g(List *args);
int max_len_names(List **names);
void mx_print_tab(int len, int maxlen);
void mx_del_arr_arr(List ***args);

List **mx_get_names(int argc, char **argv, int i);
List **mx_get_Flags(List ***args, Flag *fl);
void mx_opendir(List ***names, Flag *fl);
void mx_out_put_all(List ***args, Flag *fl);
void mx_sort(List ***disp, Flag *fl);
// Output
void mx_out_put_menu(List ***names, Flag *fl, int flag);
void mx_out_err(List ***error, Flag *fl);
void mx_output_x(List **names);
void mx_output_c(List **names);
void mx_output_m(List **names, Flag *fl);
void mx_output_g(List **names, Flag *fl);
void mx_long_out(List **names, Flag *fl, int flag);

void mx_print_per(List *print);
void mx_print_size(List *print, Size *size);
void mx_print_symblink(List *print);


