#include <uls.h>

void out_put1(t_li **names, Flag *fl)
{
    for (int i = 0; names[i]; i++)
    {
        (fl->G != 1) ? mx_printstr(names[i]->name) :  mx_printstr_g(names[i]);
        mx_printchar('\n');
    }
}
int max_len_names(t_li **names)
{
    int max = 0;
    for (int i = 0; names[i]; i++)
    {
        int tmp = mx_strlen(names[i]->name);
        if (tmp > max)
        {
            max = tmp;
        }
    }
    max = max % 8 == 0 ? max += 8 : 8 - (max % 8) + max;
    return max;
}

void mx_print_tab(int len, int maxlen)
{
    int p = maxlen - len;
    int c = p % 8 != 0 ? (p / 8) + 1 : p / 8;
    for (int i = 0; i < c; i++)
    {
        mx_printchar('\t');
    }
}

void printcols(t_li **names, int rows, int num, int maxlen)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; i + j < num; j += rows)
        {
            mx_printstr(names[i + j]->name);
            if (names[i + j + 1] && (i + j + rows < num))
            {
                mx_print_tab(mx_strlen(names[i + j]->name), maxlen);
            }
        }
        if (i != rows - 1)
        {
            mx_printchar('\n');
        }
    }
}

void print_names(t_li **names, int maxlen, int wincol)
{
    int rows;
    int cols = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;

    while(names[num])
    { 
        num++;
    }
    if (maxlen * cols > wincol && cols != 1)
    {
        cols--;
    }
    if (num * maxlen > wincol)
    {
        rows = num / cols;
        if (rows == 0 || num % cols != 0)
        {
            rows++;
        }
        printcols(names, rows, num, maxlen);
    } 
    else
    {
        for (int i = 0; names[i]; i++) 
        {
            mx_printstr(names[i]->name);
            if (names[i + 1]) 
            {
                mx_print_tab(mx_strlen(names[i]->name), maxlen);
            }
        }
    }
    mx_printchar('\n');
}

void mx_output_c(t_li **names)
{
    struct winsize win;
    if (names)
    {
        int maxlen = max_len_names(names);
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        (isatty(1)) ? print_names(names, maxlen, win.ws_col) :  print_names(names, maxlen, 80);
    }
}

void mx_out_put_menu(t_li ***names, Flag *fl, int flag)
{
    if (**names != NULL)
    {
        mx_sort(&(*names), fl);
        (fl->l) ? mx_long_out(*names, fl, flag) : (void) 0;
        if (fl->C == 1 && !fl->G)
        {
            mx_output_c(*names);
        }
        if (fl->x == 1 && !fl->G)
        {
            mx_output_x(*names);
        }
        if (fl->m == 1)
        {
            mx_output_m(*names, fl);
        }
        if (fl->force == 1)
        {
            out_put1(*names, fl);
        }
        if (fl->G == 1 && fl->m != 1 && fl->l != 1 && fl->force != 1)
        {
            mx_output_g(*names, fl);
        }
        if (fl->l != 1 && fl->C != 1 && fl->x != 1 && fl->m != 1 && fl->force != 1 && !fl->G && !fl->g && !fl->o && isatty(1))
        {
            mx_output_c(*names);
        }
        if (!isatty(1) && fl->C != 1 && fl->x != 1 && fl->m != 1 && fl->l != 1 && fl->g != 1 && fl->o != 1 && fl->force != 1)
        {
            out_put1(*names, fl);
        }
    }
}

void outputerropen(t_li **args, Flag *fl)
{
    if ((*args)->open != NULL)
    {
        mx_out_put_menu(&(*args)->open, fl, 1);
        if (fl->R == 1)
        {
            fl->Flags = 1;
            if ((*args)->open)
            {
                mx_printchar('\n');
                mx_opendir(&(*args)->open, fl);
            }
        }
    }
    else if ((*args)->err != NULL)
    {
        write(2, "uls: ", 6);
        write(2, (*args)->path, mx_strlen((*args)->path));
        write(2, ": ", 3);
        write(2, (*args)->err, mx_strlen((*args)->err));
        write(2, "\n", 2);
    }
}

void mx_out_put_all(t_li ***args, Flag *fl) 
{
    if (*args)
    {
        for (int i = 0; (*args)[i] != NULL; i++)
        {
            if (fl->Flags == 1)
            {
                ((*args)[i]->path[0] == '/' && (*args)[i]->path[1] == '/') ?  mx_printstr(&(*args)[i]->path[1]) : mx_printstr((*args)[i]->path);
                mx_printstr(":\n");
            }
            outputerropen(&(*args)[i], fl);
            if (fl->Flags == 1 && (*args)[i+1])
            {
                mx_printchar('\n');
            }
        }
    }
}

void mx_print_spaces_g(int len, int maxlen)
{
    for (int i = 0; i < maxlen - len; i++)
    {
        mx_printchar(' ');
    }
}

void print_nameG(t_li **names, int maxlen, int wincol, Flag *fl)
{
    int cols = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;
    while(names[num])
    { 
        num++;
    }
    if (maxlen * cols > wincol && cols != 1)
    {
        cols--;
    }
    if (num * maxlen > wincol)
    {
        int rows = num / cols;
        if (rows == 0 || num % cols != 0)
        {
            rows++;
        }
        if (fl->x == 0)
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; i + j < num; j += rows)
                {
                    mx_printstr_g(names[i + j]);
                    if (names[i + j + 1] && (i + j + rows < num))
                    {
                        mx_print_spaces_g(mx_strlen(names[i + j]->name), maxlen);
                    }
                }
                if (i + 1 != rows)
                {
                    mx_printchar('\n');
                }
            }
        }
        else
        {
            int tmpcols = cols;
            for (int i = 0; i < rows; i++, cols += tmpcols)
            {
                for (int j = 0; names[j] && j < cols; j++)
                {
                    mx_printstr_g(names[j]);
                    if (names[j + 1] && (j != cols - 1))
                    {
                        mx_print_spaces_g(mx_strlen(names[j]->name), maxlen);
                    }
                }
                if (i + 1 != rows)
                {
                    mx_printchar('\n');
                }
            }
        }
    } 
    else
    {
        for (int i = 0; names[i]; i++)
        {
            mx_printstr_g(names[i]);
            if (names[i + 1])
            {
                mx_print_spaces_g(mx_strlen(names[i]->name), maxlen);
            }
        }
    }
    mx_printchar('\n');
}

void mx_output_g(t_li **names, Flag *fl)
{
    struct winsize win;
    if (names)
    {
        int max = 0;
        for (int i = 0; names[i]; i++)
        {
            int tmp = mx_strlen(names[i]->name);
            if (tmp > max)
            {
                max = tmp;
            }
        }
        max++;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        print_nameG(names, max, win.ws_col, fl);
    }
}

void print_nameN(t_li **names, int wincol, Flag *fl)
{
    int len = 0;
    for (int i = 0; names[i]; i++)
    {
        if (fl->G == 1)
        {
            mx_printstr_g(names[i]);
        }
        else if (fl->G != 1)
        {
            mx_printstr(names[i]->name);
        }
        len += mx_strlen(names[i]->name) + 2;
        if (names[i + 1])
        {
            mx_printstr(", ");
            int nextlen = names[i + 2] ? 3 : 1;
            if (len + nextlen + mx_strlen(names[i + 1]->name) > wincol)
            {
                len = 0;
                mx_printchar('\n');
            }
        }
    }
    mx_printchar('\n');
}

void mx_output_m(t_li **names, Flag *fl)
{
    struct winsize win;
    if (names)
    {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        (isatty(1)) ? print_nameN(names, win.ws_col, fl) : print_nameN(names, 80, fl);
    }  
}

void printcols_xM(t_li **names, int rows, int cols, int maxlen)
{
    int tmpcols = cols;
    for (int i = 0; i < rows; i++, cols += tmpcols)
    {
        for (int j = 0; names[j] && j < cols; j++)
        {
            mx_printstr(names[j]->name);
            if (names[j + 1] && (j != cols - 1))
            {
                mx_print_tab(mx_strlen(names[j]->name), maxlen);
            }
        }
        if (i + 1 != rows)
        {
            mx_printchar('\n');
        }
    }
}

void print_namesX(t_li **names, int maxlen, int wincol)
{
    int cols = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;
    while(names[num])  
    {
        num++;
    }
    if (maxlen * cols > wincol && cols != 1)
    {
        cols--;
    }
    if (num * maxlen > wincol)
    {
        int rows = num / cols;
        if (rows == 0 || num % cols != 0)
        {
            rows++;
        }
        printcols_xM(names, rows, cols, maxlen);
    } 
    else
    {
        for (int i = 0; names[i]; i++) 
        {
            mx_printstr(names[i]->name);
            if (names[i + 1])
            {
                mx_print_tab(mx_strlen(names[i]->name), maxlen);
            }
        }
    }
    mx_printchar('\n');
}

void mx_output_x(t_li **names) 
{
    struct winsize win;
    if (names)
    {
        int maxlen = max_len_names(names);
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        (isatty(1)) ? print_namesX(names, maxlen, win.ws_col) : print_namesX(names, maxlen, 80);
    }
}

