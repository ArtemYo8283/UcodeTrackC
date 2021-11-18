#include <uls.h>

void get_username(List *print, int usr)
{
    struct passwd *pw = getpwuid(print->info.st_uid);
    char *name = pw ? mx_strdup(pw->pw_name) : mx_itoa(print->info.st_uid);
    if (mx_strlen(name) == usr)
    {
       mx_printstr(name);
    }
    else if (mx_strlen(name) < usr)
    {
        mx_printstr(name);
        for (int i = mx_strlen(name); i != usr; i++)
        {
            mx_printchar(' ');
        }
    }
    mx_printstr("  ");
    free(name);
}

void get_groupname(List *print, int group)
{
    struct group *grp = getgrgid(print->info.st_gid);
    char *name = grp ? mx_strdup(grp->gr_name) : mx_itoa(print->info.st_gid);
    if (mx_strlen(name) == group)
    {
        mx_printstr(name);
    }
    else if (mx_strlen(name) < group)
    {
        mx_printstr(name);
        for (int i = mx_strlen(name); i != group; i++)
        {
            mx_printchar(' ');
        }
    }
    mx_printstr("  ");
}

void color_link(List *print, Flag *flags)
{
    if (flags->G == 1)
    {
        printstr_in_color(print);
    }
    else if ((((print->info.st_mode) & S_IFMT) == S_IFLNK))
    {
        mx_printstr(print->name);
        print_sl(print);
    }
    else
    {
        mx_printstr(print->name);
    }
}

void time_edit(List *print, char *t, Flag *flags)
{
    if (flags->T == 1)
    {
        for (int i = 4; i < t[i]; i++)
        {
           mx_printchar(t[i]); 
        }
    }
    else 
    {
        if (1565913600 >= print->info.st_mtime)
        {
            for(int i = 4; i < 10; i++)
            {
                mx_printchar(t[i]);
            }
            mx_printstr("  ");
            for (int i = 20; i < 24; i++)
            {
                mx_printchar(t[i]); 
            }
        }
        else
        {
            for(int i = 4; i < 16; i++)
            {
                mx_printchar(t[i]);
            }
        }
    }
    mx_printstr(" ");
}

void print_link(List *print, Size *size)
{
    char *res_itoa_now = mx_itoa(print->info.st_nlink);
    char *res_itoa_lnk = mx_itoa(size->lnk);
    if (mx_strlen(res_itoa_now) == mx_strlen(res_itoa_lnk))
    {
        mx_printint(print->info.st_nlink);
    }
    else if (mx_strlen(res_itoa_now) < mx_strlen(res_itoa_lnk))
    {
        for (int i = mx_strlen(res_itoa_now); i != mx_strlen(res_itoa_lnk); i++)
        {
            mx_printchar(' ');
        }
        mx_printint(print->info.st_nlink);
    }
    mx_printchar(' ');
    free(res_itoa_now);
    free(res_itoa_lnk);
}

void print_sl(List *print)
{
    ssize_t buf_size = print->info.st_size == 0 ? 100 : print->info.st_size + 1;
    char *buf = mx_strnew(buf_size);
    ssize_t nbytes = readlink(print->path, buf, buf_size);
    mx_printstr(" -> ");
    if (nbytes >= 0)
    {
        mx_printstr(buf);
    }
    mx_strdel(&buf);
}

void print_name(List *args)
{
    mx_printstr(args->name);
    mx_printstr(STANDART);
}

int print_frst(List *args)
{
    if ((((args->info.st_mode) & S_IFMT) == S_IFDIR))
    {
        mx_printstr("\033[34m");
    }
    else if ((((args->info.st_mode) & S_IFMT) == S_IFLNK))
    {
        mx_printstr("\033[35m");
    }
    else if (args->info.st_mode & S_IXOTH)
    {
        mx_printstr(RED);
    }
    else
    {
        return 0;
    }
    print_name(args); 
    return 1;
}

int print_sec(List *args)
{
    if ((((args->info.st_mode) & S_IFMT) == S_IFBLK))
    {
        mx_printstr("\033[34;46m");
    }
    else if ((((args->info.st_mode) & S_IFMT) == S_IFCHR))
    {
        mx_printstr("\033[34;43m");
    }
    else if ((((args->info.st_mode) & S_IFMT) == S_IFSOCK))
    {
        mx_printstr("\033[32m");   
    }
    else
    {
        return 0;
    }
    print_name(args); 
    return 1;
}

void printstr_in_color(List *args)
{
    if (print_frst(args) == 1 || print_sec(args) == 1)
    {
        return;
    }
    else if ((((args->info.st_mode) & S_IFMT) == S_IFIFO))
    {
        mx_printstr("\033[33m");
        print_name(args);
    }
    else if ((((args->info.st_mode)& S_IFMT) == S_IFWHT))
    {
        mx_printstr("\033[36m");
        print_name(args);
    }
    else if (((args->info.st_mode) & S_IXUSR))
    {
        mx_printstr("\033[31m");
        print_name(args);
    }
    else
    {
        mx_printstr(args->name);
    }
}

char get_Flag_acl(List *print)
{
    acl_t tmp = acl_get_file(print->path, ACL_TYPE_EXTENDED);
    if (tmp)
    {
        acl_free(tmp);
        return '+';
    }
    if (listxattr(print->path, NULL, 0, XATTR_NOFOLLOW) > 0)
    {
        return '@';
    }
    return ' ';
}

char check_per(List *print)
{
    if ((((print->info.st_mode) & S_IFMT) == S_IFDIR))
    {
        return 'd';
    }
    else if ((((print->info.st_mode) & S_IFMT) == S_IFLNK))
    {
        return 'l';
    }
    else if ((((print->info.st_mode) & S_IFMT) == S_IFBLK))
    {
        return 'b';
    }
    else if ((((print->info.st_mode) & S_IFMT) == S_IFCHR))
    {
        return 'c';
    }
    else if ((((print->info.st_mode) & S_IFMT) == S_IFIFO))
    {
        return 'p';
    }
    else if ((((print->info.st_mode) & S_IFMT) == S_IFSOCK))
    {
        return 's';
    }
    else if ((((print->info.st_mode) & S_IFMT) == S_IFWHT))
    {
        return 'w';
    }
    return '-';
}

char check_chmode_S(char chmod)
{
    return chmod == '-' ? 'S' : 's';
}

char check_chmode_T(char *chmod)
{
    return chmod[9] == '-' ? 'T' : 't';
}

void print_chmod(List *print)
{
    char chmod[12];
    chmod[0] = check_per(print);
    chmod[1] = (S_IRUSR & print->info.st_mode) ? 'r' : '-';
    chmod[2] = (S_IWUSR & print->info.st_mode) ? 'w' : '-';
    chmod[3] = (S_IXUSR & print->info.st_mode) ? 'x' : '-';
    chmod[4] = (S_IRGRP & print->info.st_mode) ? 'r' : '-';
    chmod[5] = (S_IWGRP & print->info.st_mode) ? 'w' : '-';
    chmod[6] = (S_IXGRP & print->info.st_mode) ? 'x' : '-';
    chmod[7] = (S_IROTH & print->info.st_mode) ? 'r' : '-';
    chmod[8] = (S_IWOTH & print->info.st_mode) ? 'w' : '-';
    chmod[9] = (S_IXOTH & print->info.st_mode) ? 'x' : '-';
    chmod[10] = get_Flag_acl(print);
    chmod[11] = '\0';
    S_ISUID & print->info.st_mode ? chmod[3] = check_chmode_S(chmod[3]) : 0;
    S_ISGID & print->info.st_mode ? chmod[6] = check_chmode_S(chmod[6]) : 0;
    S_ISVTX & print->info.st_mode ? chmod[9] = check_chmode_T(chmod) : 0;
    for (int i = 0; chmod[i]; i++)
    {
        mx_printchar(chmod[i]);
    }
    mx_printchar(' ');
}

void print_spaces(int size)
{
    while(size-- >= 0)
    {
        mx_printchar(' ');
    }
}

char *get_minor(List *print)
{
    int minor_num = (int)(print->info.st_rdev & 0xffffff);
    if (minor_num > 255) 
    { 
        char *hex_minor = mx_strdup("0x00000000");
        mx_strcpy(hex_minor + (10 - mx_strlen(mx_nbr_to_hex(minor_num))), mx_nbr_to_hex(minor_num));
        return hex_minor;
    }
    else
    { 
        return mx_itoa(minor_num);
    }
}

char *get_major(List *print)
{
    return mx_itoa((int)(((unsigned int)print->info.st_rdev >> 24) & 0xff));
}

void print_duo_cases(List *print, Size *size)
{
    char *major = get_major(print);
    char *minor = get_minor(print);
    if (size->is_dev == true)
    {
        if ((((((print->info.st_mode) & S_IFMT) == S_IFBLK) || ((print->info.st_mode) & S_IFMT) == S_IFCHR)))
        {
            print_spaces(2 - mx_strlen(major));
            mx_printstr(major);
            mx_printstr(", ");
            print_spaces(2 - mx_strlen(minor));
            mx_printstr(minor); 
        }
        else
        {
            mx_printstr("       ");
            mx_printint(print->info.st_size);
        }
    }
    else
    {
       mx_printint(print->info.st_size);
    } 
    free(major);
    free(minor);
}

void print_size(List *print, Size *size)
{
    char *res_now = mx_itoa(print->info.st_size);
    char *res_size = mx_itoa(size->size);
    if (mx_strlen(res_now) == mx_strlen(res_size))
    {
        print_duo_cases(print, size);
    }
    else if (mx_strlen(res_now) < mx_strlen(res_size))
    {
        for (int c = mx_strlen(res_now); c != mx_strlen(res_size); c++)
        {
            mx_printchar(' ');
        }
        print_duo_cases(print, size);
    }
    mx_printchar(' ');
    free(res_now);
    free(res_size);
}

char *check_group(List *total)
{
    struct group *grp = getgrgid(total->info.st_gid);
    return grp ? mx_strdup(grp->gr_name) : mx_itoa(total->info.st_gid);
}

char *check_pw(List *total)
{
    struct passwd *pw = getpwuid(total->info.st_uid);
    return pw ? mx_strdup(pw->pw_name) : mx_itoa(total->info.st_uid);
}

void count_size(Size *size, List *total)
{
    char *name_grp = check_group(total);
    char *name_pw = check_pw(total);
    if (size->lnk < total->info.st_nlink)
    {
        size->lnk = total->info.st_nlink;
    }
    if (size->size < total->info.st_size)
    {
        size->size = total->info.st_size;
    }
    if (size->group < mx_strlen(name_grp))
    {
        size->group = mx_strlen(name_grp);
    }
    if (size->usr < mx_strlen(name_pw))
    {
        size->usr = mx_strlen(name_pw);
    }
    free(name_grp);
    free(name_pw);
}

void long_output(List **names, Flag *flags, int flag)
{
    Size *size = malloc(sizeof(Size));
    int blk_size = 0;
    size->lnk = 0;
    size->size = 0;
    size->group = 0;
    size->usr = 0;
    for (int i = 0; names[i]; i++)
    {
        blk_size += names[i]->info.st_blocks;
        count_size(size, names[i]);
    }
    if (flag == 1)
    {
        mx_printstr("total ");
        mx_printint(blk_size);
        mx_printchar('\n');
    }
    for (int i = 0; names[i]; i++)
    {
        size->is_dev = false;
        if (((((names[i]->info.st_mode) & S_IFMT) == S_IFBLK) || ((names[i]->info.st_mode) & S_IFMT) == S_IFCHR))
        {
            size->is_dev = true;
            break;
        }         
    }
    for (int i = 0; names[i]; i++)
    {
        time_t *chtime = &names[i]->info.st_ctime, *atime = &names[i]->info.st_atime, *time = &names[i]->info.st_mtime;
        print_chmod(names[i]);
        print_link(names[i], size);
        if ((flags->l == 1 && flags->g == 0) || (flags->o == 1 && flags->g == 0))
        {
            get_username(names[i], size->usr);
        }
        if ((flags->l == 1 && flags->o == 0) || (flags->g == 1 && flags->o == 0))
        {
            get_groupname(names[i], size->group);
        }
        print_size(names[i], size);
        if (flags->u == 1)
        {
            time = atime;
        }
        if (flags->c == 1)
        {
            time = chtime;
        }
        time_edit(names[i], ctime(time), flags);
        color_link(names[i], flags);
        mx_printchar('\n');
    }
    free(size);
}



