#include <uls.h>

void out_put1(t_li **names, st_fl *fl)
{
    for (int i = 0; names[i]; i++)
    {
        if (fl->G != 1)
        {
            mx_printstr(names[i]->name);
        }
        else
        {
            mx_printstr_g(names[i]);
        }
        mx_printchar('\n');
    }
}
int max_len_names(t_li **names)
{
    int max = 0;
    int temp = 0;
    for (int i = 0; names[i]; i++)
    {
        temp = mx_strlen(names[i]->name);
        if (temp > max)
        {
            max = temp;
        }
    }
    if (max % 8 == 0)
    {
        max += 8;
    }
    else
    {
        max = 8 - (max % 8) + max;
    }
    return max;
}

void mx_print_tab(int len, int maxlen)
{
    int count = 0;
    int p;
    p = maxlen - len;
    if (p % 8 != 0)
    {
        count = (p / 8) + 1;
    }
    else
    {
        count = p / 8;
    }
    for (int i = 0; i < count; i++)
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

    for(;names[num]; num++);
    if (maxlen * cols > wincol && cols != 1)
    {
        cols--;
    }
    if (num * maxlen > wincol)
    {
        rows = num / cols;
        if (rows == 0 || num % cols != 0)
        {
            rows += 1;
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
    int maxlen;
    struct winsize win;

    if (!names)
        return;
    maxlen = max_len_names(names);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (isatty(1))
    {
        print_names(names, maxlen, win.ws_col);
    }
    else
    {
        print_names(names, maxlen, 80);
    }
}

void mx_out_put_menu(t_li ***names, st_fl *fl, int flag)
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

void outputerropen(t_li **args, st_fl *fl)
{
    if ((*args)->open != NULL)
    {
        mx_out_put_menu(&(*args)->open, fl, 1);
        if (fl->R == 1)
        {
            fl->files = 1;
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

void mx_out_put_all(t_li ***args, st_fl *fl) 
{
    if (*args)
    {
        for (int i = 0; (*args)[i] != NULL; i++)
        {
            if (fl->files == 1)
            {
                if ((*args)[i]->path[0] == '/' && (*args)[i]->path[1] == '/')
                {
                    mx_printstr(&(*args)[i]->path[1]);
                }
                else
                {
                    mx_printstr((*args)[i]->path);
                }
                mx_printstr(":\n");
            }
            outputerropen(&(*args)[i], fl);
            if (fl->files == 1 && (*args)[i+1])
            {
                mx_printchar('\n');
            }
        }
    }
}

void mx_out_err(t_li ***error, st_fl *fl)
{
    if (error && *error && **error)
    {
        mx_sort(error, fl);
        fl->files = 1;
        fl->ex = 1;
        for (int i = 0; (*error)[i]; i++)
        {
            write(2, "uls: ", 6);
            write(2, (*error)[i]->name, mx_strlen((*error)[i]->name));
            write(2, ": ", 3);
            write(2, (*error)[i]->err, mx_strlen((*error)[i]->err));
            write(2, "\n", 2);
            free((*error)[i]);
            (*error)[i] = NULL;
        }
        free(*error);
        *error = NULL;
    }
}

void mx_print_spaces_g(int len, int maxlen)
{
    int count = 0;
    count = maxlen - len;
    for (int i = 0; i < count; i++)
    {
        mx_printchar(' ');
    }
}

void printcols_c(t_li **names, int rows, int num, int maxlen) {
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
        if (i != rows - 1)
        {
            mx_printchar('\n');
        }
    }
}

int mx_max_len_n_g(t_li **names)
{
    int max = 0;
    int temp = 0;
    for (int i = 0; names[i]; i++)
    {
        temp = mx_strlen(names[i]->name);
        if (temp > max)
        {
            max = temp;
        }
    }
    max++;
    return max;
}

void printcols_x(t_li **names, int rows, int cols, int maxlen)
{
    int j = 0;
    int tempcols = cols;
    for (int i = 0; i < rows; i++, cols += tempcols)
    {
        for (; names[j] && j < cols; j++)
        {
            mx_printstr_g(names[j]);
            if (names[j + 1] && (j != cols - 1))
            {
                mx_print_spaces_g(mx_strlen(names[j]->name), maxlen);
            }
        }
        if (i != rows - 1)
        {
            mx_printchar('\n');
        }
    }
}

void printrow_g(t_li **names, int maxlen)
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

void print_nameG(t_li **names, int maxlen, int wincol, st_fl *fl)
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
            rows += 1;
        }
        if (fl->x == 0)
        {
            printcols_c(names, rows, num, maxlen);
        }
        else
        {
            printcols_x(names, rows, cols, maxlen);
        }
    } 
    else
    {
        printrow_g(names, maxlen);
    }
    mx_printchar('\n');
}

void mx_output_g(t_li **names, st_fl *fl)
{
    int maxlen;
    struct winsize win;
    if (!names)
    {
        return;
    }
    maxlen = mx_max_len_n_g(names);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    print_nameG(names, maxlen, win.ws_col, fl);
}

void printn(int *len)
{
    (*len) = 0;
    mx_printchar('\n');
}

void print_nameN(t_li **names, int wincol, st_fl *fl)
{
    int len = 0, nextlen = 0;

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
            if (names[i + 2])
            {
                nextlen = 3;
            }
            else
            {
                nextlen = 1;
            }
            if (len + nextlen + mx_strlen(names[i + 1]->name) > wincol)
            {
                printn(&len);
            }
        }
    }
    mx_printchar('\n');
}

void mx_output_m(t_li **names, st_fl *fl)
{
    struct winsize win;

    if (!names)
    {
        return;
    }
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (isatty(1))
    {
        print_nameN(names, win.ws_col, fl);
    }
    else
    {
        print_nameN(names, 80, fl);
    }
}


void printcols_xM(t_li **names, int rows, int cols, int maxlen)
{
    int j = 0;
    int tempcols = cols;
    for (int i = 0; i < rows; i++, cols += tempcols)
    {
        for (; names[j] && j < cols; j++)
        {
            mx_printstr(names[j]->name);
            if (names[j + 1] && (j != cols - 1))
            {
                mx_print_tab(mx_strlen(names[j]->name), maxlen);
            }
        }
        if (i != rows - 1)
        {
            mx_printchar('\n');
        }
    }
}

void print_namesX(t_li **names, int maxlen, int wincol)
{
    int rows;
    int cols = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;

    for(;names[num]; num++);
    if (maxlen * cols > wincol && cols != 1)
    {
        cols--;
    }
    if (num * maxlen > wincol)
    {
        rows = num / cols;
        if (rows == 0 || num % cols != 0)
        {
            rows += 1;
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
    int maxlen;
    struct winsize win;

    if (!names)
    {
        return;
    }
    maxlen = max_len_names(names);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (isatty(1))
    {
        print_namesX(names, maxlen, win.ws_col);
    }
    else
    {
        print_namesX(names, maxlen, 80);
    }
}

