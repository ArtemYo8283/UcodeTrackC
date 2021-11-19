#include <uls.h>

void output_names(List **names, Flag *flags)
{
    for (int i = 0; names[i]; i++)
    {
        (flags->G != 1) ? mx_printstr(names[i]->name) :  printstr_in_color(names[i]);
        mx_printchar('\n');
    }
}
int Names_lenght_max(List **names)
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

void print_tab(int len, int maxlen)
{
    int p = maxlen - len;
    int c = p % 8 != 0 ? (p / 8) + 1 : p / 8;
    for (int i = 0; i < c; i++)
    {
        mx_printchar('\t');
    }
}

void print_color(List **names, int row, int num, int maxlen)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; i + j < num; j += row)
        {
            mx_printstr(names[i + j]->name);
            if (names[i + j + 1] && (i + j + row < num))
            {
                print_tab(mx_strlen(names[i + j]->name), maxlen);
            }
        }
        if (i != row - 1)
        {
            mx_printchar('\n');
        }
    }
}

void print_names(List **names, int maxlen, int wincol)
{
    int row;
    int col = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;
    while(names[num])
    { 
        num++;
    }
    if (maxlen * col > wincol && col != 1)
    {
        col--;
    }
    if (num * maxlen > wincol)
    {
        row = num / col;
        if (row == 0 || num % col != 0)
        {
            row++;
        }
        print_color(names, row, num, maxlen);
    } 
    else
    {
        for (int i = 0; names[i]; i++) 
        {
            mx_printstr(names[i]->name);
            if (names[i + 1]) 
            {
                print_tab(mx_strlen(names[i]->name), maxlen);
            }
        }
    }
    mx_printchar('\n');
}

void flag_c_output(List **names)
{
    struct winsize win;
    if (names)
    {
        int maxlen = Names_lenght_max(names);
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        (isatty(1)) ? print_names(names, maxlen, win.ws_col) :  print_names(names, maxlen, 80);
    }
}

void outputerropen(List **args, Flag *flags)
{
    if ((*args)->open != NULL)
    {
        output_menu(&(*args)->open, flags, 1);
        if (flags->R == 1)
        {
            flags->Flags = 1;
            if ((*args)->open)
            {
                mx_printchar('\n');
                openDirectory(&(*args)->open, flags);
            }
        }
    }
    else if ((*args)->err != NULL)
    {
        int slashes_pos = 0;
        char *c = (*args)->path;
        for(int i = 0; i < mx_strlen(c); i++)
        {
            if(c[i] == '/')
            {
                slashes_pos = i;
            }
        }
        slashes_pos++;
        if(mx_strcmp((*args)->err, "No such file or directory") == 0)
        {
            write(2, "uls: ", 6);
            write(2, (*args)->path, mx_strlen((*args)->path));
            write(2, ": ", 3);
            write(2, (*args)->err, mx_strlen((*args)->err));
            write(2, "\n", 2);
        }
        else
        {
            write(2, "uls: ", 6);
            for(int i = slashes_pos; c[i] != '\0'; i++)
            {
                write(2, &c[i], 1);
            }
            write(2, ": ", 3);
            write(2, (*args)->err, mx_strlen((*args)->err));
            write(2, "\n", 2);
        }
    }
}

void outputAll(List ***args, Flag *flags) 
{
    if (*args)
    {
        for (int i = 0; (*args)[i] != NULL; i++)
        {
            outputerropen(&(*args)[i], flags);
        }
    }
}

void print_spaces_flag_g(int len, int maxlen)
{
    for (int i = 0; i < maxlen - len; i++)
    {
        mx_printchar(' ');
    }
}

void print_name_flag_G(List **names, int maxlen, int wincol, Flag *flags)
{
    int col = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;
    while(names[num])
    { 
        num++;
    }
    if (maxlen * col > wincol && col != 1)
    {
        col--;
    }
    if (num * maxlen > wincol)
    {
        int row = num / col;
        if (row == 0 || num % col != 0)
        {
            row++;
        }
        if (flags->x == 0)
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; i + j < num; j += row)
                {
                    printstr_in_color(names[i + j]);
                    if (names[i + j + 1] && (i + j + row < num))
                    {
                        print_spaces_flag_g(mx_strlen(names[i + j]->name), maxlen);
                    }
                }
                if (i + 1 != row)
                {
                    mx_printchar('\n');
                }
            }
        }
        else
        {
            int tmpcol = col;
            for (int i = 0; i < row; i++, col += tmpcol)
            {
                for (int j = 0; names[j] && j < col; j++)
                {
                    printstr_in_color(names[j]);
                    if (names[j + 1] && (j != col - 1))
                    {
                        print_spaces_flag_g(mx_strlen(names[j]->name), maxlen);
                    }
                }
                if (i + 1 != row)
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
            printstr_in_color(names[i]);
            if (names[i + 1])
            {
                print_spaces_flag_g(mx_strlen(names[i]->name), maxlen);
            }
        }
    }
    mx_printchar('\n');
}

void flag_g_output(List **names, Flag *flags)
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
        print_name_flag_G(names, max, win.ws_col, flags);
    }
}

void print_name_flag_N(List **names, int wincol, Flag *flags)
{
    int len = 0;
    for (int i = 0; names[i]; i++)
    {
        if (flags->G == 1)
        {
            printstr_in_color(names[i]);
        }
        else if (flags->G != 1)
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

void print_name_flag_xm(List **names, int row, int col, int maxlen)
{
    int tmpcol = col;
    for (int i = 0; i < row; i++, col += tmpcol)
    {
        for (int j = 0; names[j] && j < col; j++)
        {
            mx_printstr(names[j]->name);
            if (names[j + 1] && (j != col - 1))
            {
                print_tab(mx_strlen(names[j]->name), maxlen);
            }
        }
        if (i + 1 != row)
        {
            mx_printchar('\n');
        }
    }
}

void print_name_flag_X(List **names, int maxlen, int wincol)
{
    int col = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;
    while(names[num])  
    {
        num++;
    }
    if (maxlen * col > wincol && col != 1)
    {
        col--;
    }
    if (num * maxlen > wincol)
    {
        int row = num / col;
        if (row == 0 || num % col != 0)
        {
            row++;
        }
        print_name_flag_xm(names, row, col, maxlen);
    } 
    else
    {
        for (int i = 0; names[i]; i++) 
        {
            mx_printstr(names[i]->name);
            if (names[i + 1])
            {
                print_tab(mx_strlen(names[i]->name), maxlen);
            }
        }
    }
    mx_printchar('\n');
}

void output_menu(List ***names, Flag *flags, int flag)
{
    if (**names != NULL)
    {
        sorting(&(*names), flags);
        (flags->l) ? long_output(*names, flags, flag) : (void) 0;
        if (flags->C == 1 && !flags->G)
        {
            flag_c_output(*names);
        }
        if (flags->x == 1 && !flags->G)
        {
            struct winsize win;
            if (*names)
            {
                int maxlen = Names_lenght_max(*names);
                ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
                (isatty(1)) ? print_name_flag_X(*names, maxlen, win.ws_col) : print_name_flag_X(*names, maxlen, 80);
            }
        }
        if (flags->m == 1)
        {
            struct winsize win;
            if (*names)
            {
                ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
                (isatty(1)) ? print_name_flag_N(*names, win.ws_col, flags) : print_name_flag_N(*names, 80, flags);
            }  
        }
        if (flags->force == 1)
        {
            output_names(*names, flags);
        }
        if (flags->G == 1 && flags->m != 1 && flags->l != 1 && flags->force != 1)
        {
            flag_g_output(*names, flags);
        }
        if (flags->l != 1 && flags->C != 1 && flags->x != 1 && flags->m != 1 && flags->force != 1 && !flags->G && !flags->g && !flags->o && isatty(1))
        {
            flag_c_output(*names);
        }
        if (!isatty(1) && flags->C != 1 && flags->x != 1 && flags->m != 1 && flags->l != 1 && flags->g != 1 && flags->o != 1 && flags->force != 1)
        {
            output_names(*names, flags);
        }
    }
}
