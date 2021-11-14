#include <uls.h>

void mx_get_user_name(t_li *print, int usr)
{
    struct passwd *pw = getpwuid(print->info.st_uid);
    int counter = 0;
    char *name = NULL;
    if (pw)
    {
        name = mx_strdup(pw->pw_name);
    }
    else
    {
        name = mx_itoa(print->info.st_uid);
    }
    if (mx_strlen(name) == usr)
    {
       mx_printstr(name);
    }
    else if (mx_strlen(name) < usr)
    {
        counter = mx_strlen(name);
        mx_printstr(name);
        while (counter != usr)
        {
            mx_printchar(' ');
            counter++;
        }
    }
    mx_printstr("  ");
    free(name);
}

void mx_get_group_name(t_li *print, int group)
{
    struct group *grp = getgrgid(print->info.st_gid);
    int counter = 0;
    char *name = NULL;
    if (grp)
    {
        name = mx_strdup(grp->gr_name);
    }
    else
    {
        name = mx_itoa(print->info.st_gid);
    }
    if (mx_strlen(name) == group)
    {
        mx_printstr(name);
    }
    else if (mx_strlen(name) < group)
    {
        counter = mx_strlen(name);
        mx_printstr(name);
        while (counter != group)
        {
            mx_printchar(' ');
            counter++;
        }
    }
    mx_printstr("  ");
    free(name);
}

void print_link_and_color(t_li *print, st_fl *fl)
{
    if (fl->G == 1)
    {
        mx_printstr_g(print);
    }
    else if (IS_LNK(print->info.st_mode))
    {
        mx_printstr(print->name);
        mx_print_symblink(print);
    }
    else
    {
        mx_printstr(print->name);
    }
}

void mx_edit_time(t_li *print, char *t, st_fl *fl)
{
    int i = 0;
    if (fl->T == 1)
    {
        for (i = 4; i < t[i]; i++)
        {
           mx_printchar(t[i]); 
        }
    }
    else 
    {
        if (1565913600 >= print->info.st_mtime)
        {
            for(i = 4; i < 10; i++)
            {
                mx_printchar(t[i]);
            }
            mx_printstr("  ");
            for (i = 20; i < 24; i++)
            {
                mx_printchar(t[i]); 
            }
        }
        else
        {
            for(i = 4; i < 16; i++)
            {
                mx_printchar(t[i]);
            }
        }
    }
    mx_printstr(" ");
}

void mx_print_lnk(t_li *print, t_sz *size)
{
    int counter = 0;
    char *res_itoa_now = mx_itoa(print->info.st_nlink);
    char *res_itoa_lnk = mx_itoa(size->lnk);
    if (mx_strlen(res_itoa_now) == mx_strlen(res_itoa_lnk))
    {
        mx_printint(print->info.st_nlink);
    }
    else if (mx_strlen(res_itoa_now) < mx_strlen(res_itoa_lnk))
    {
        counter = mx_strlen(res_itoa_now);
        while (counter != mx_strlen(res_itoa_lnk))
        {
            mx_printchar(' ');
            counter++;
        }
        mx_printint(print->info.st_nlink);
    }
    mx_printchar(' ');
    free(res_itoa_now);
    free(res_itoa_lnk);
}

void mx_print_symblink(t_li *print)
{
    char *buf = NULL;
    ssize_t nbytes = 0;
    ssize_t buf_size = 0;
    buf_size = print->info.st_size == 0 ? 100 : print->info.st_size + 1;
    buf = mx_strnew(buf_size);
    nbytes = readlink(print->path, buf, buf_size);
    mx_printstr(" -> ");
    if (nbytes >= 0)
    {
        mx_printstr(buf);
    }
    mx_strdel(&buf);
}

void mx_print_all(t_li *print, t_sz *size, st_fl *fl)
{
    time_t *chtime = &print->info.st_ctime;
    time_t *atime = &print->info.st_atime;
    time_t *t = &print->info.st_mtime;
    mx_print_per(print);
    mx_print_lnk(print, size);
    if ((fl->l == 1 && fl->g == 0) || (fl->o == 1 && fl->g == 0))
    {
        mx_get_user_name(print, size->usr);
    }
    if ((fl->l == 1 && fl->o == 0) || (fl->g == 1 && fl->o == 0))
    {
        mx_get_group_name(print, size->group);
    }
    mx_print_sz(print, size);
    if (fl->u == 1)
    {
        t = atime;
    }
    if (fl->c == 1)
    {
        t = chtime;
    }
    mx_edit_time(print, ctime(t), fl);
    print_link_and_color(print, fl);
    mx_printchar('\n');
}

void print_name(t_li *args)
{
    mx_printstr(args->name);
    mx_printstr(LS_COLOR_RESET);
}

int print_frst(t_li *args)
{
    if (IS_DIR(args->info.st_mode))
    {
        mx_printstr("\033[34m");
        print_name(args);
        return 1;
    }
    else if (IS_LNK(args->info.st_mode))
    {
        mx_printstr("\033[35m");
        print_name(args);
        return 1;
    }
    else if (args->info.st_mode & S_IXOTH)
    {
        mx_printstr(LS_COLOR_RED);
        print_name(args);
        return 1;
    }
    return 0;
}

int print_sec(t_li *args)
{
    if (IS_BLK(args->info.st_mode))
    {
        mx_printstr("\033[34;46m");
        print_name(args);
        return 1;
    }
    else if (IS_CHR(args->info.st_mode))
    {
        mx_printstr("\033[34;43m");
        print_name(args);
        return 1;
    }
    else if (IS_SOCK(args->info.st_mode))
    {
        mx_printstr("\033[32m");
        print_name(args);
        return 1;
    }
    return 0;
}

void mx_printstr_g(t_li *args)
{
    if (print_frst(args) == 1)
    {
    }
    else if (print_sec(args) == 1)
    {
    }
    else if (IS_FIFO(args->info.st_mode))
    {
        mx_printstr("\033[33m");
        print_name(args);
    }
    else if (IS_WHT(args->info.st_mode))
    {
        mx_printstr("\033[36m");
        print_name(args);
    }
    else if (IS_EXEC(args->info.st_mode))
    {
        mx_printstr("\033[31m");
        print_name(args);
    }
    else
    {
        mx_printstr(args->name);
    }
}

char mx_get_file_acl(t_li *print)
{
    acl_t tmp;
    if (listxattr(print->path, NULL, 0, XATTR_NOFOLLOW) > 0)
    {
        return ('@');
    }
    if ((tmp = acl_get_file(print->path, ACL_TYPE_EXTENDED)))
    {
        acl_free(tmp);
        return ('+');
    }
    return (' ');
}

char mx_check_per(t_li *print)
{
    if (IS_DIR(print->info.st_mode))
    {
        return 'd';
    }
    if (IS_LNK(print->info.st_mode))
    {
        return 'l';
    }
    if (IS_BLK(print->info.st_mode))
    {
        return 'b';
    }
    if (IS_CHR(print->info.st_mode))
    {
        return 'c';
    }
    if (IS_FIFO(print->info.st_mode))
    {
        return 'p';
    }
    if (IS_SOCK(print->info.st_mode))
    {
        return 's';
    }
    if (IS_WHT(print->info.st_mode))
    {
        return 'w';
    }
    return '-';
}

char check_chmode1(char chmod)
{
    if (chmod == '-')
    {
        return chmod = 'S';
    }
    else
    {
        return chmod = 's';
    }
}

char check_chmode2(char *chmod)
{
    if (chmod[9] == '-')
    {
        return chmod[9] = 'T';
    }
    else
    {
        return chmod[9] = 't';
    }
}

void mx_print_per(t_li *print)
{
    char chmod[12];
    chmod[0] = mx_check_per(print);
    chmod[1] = (S_IRUSR & print->info.st_mode) ? 'r' : '-';
    chmod[2] = (S_IWUSR & print->info.st_mode) ? 'w' : '-';
    chmod[3] = (S_IXUSR & print->info.st_mode) ? 'x' : '-';
    chmod[4] = (S_IRGRP & print->info.st_mode) ? 'r' : '-';
    chmod[5] = (S_IWGRP & print->info.st_mode) ? 'w' : '-';
    chmod[6] = (S_IXGRP & print->info.st_mode) ? 'x' : '-';
    chmod[7] = (S_IROTH & print->info.st_mode) ? 'r' : '-';
    chmod[8] = (S_IWOTH & print->info.st_mode) ? 'w' : '-';
    chmod[9] = (S_IXOTH & print->info.st_mode) ? 'x' : '-';
    chmod[10] = mx_get_file_acl(print);
    chmod[11] = '\0';
    S_ISUID & print->info.st_mode ? chmod[3] = check_chmode1(chmod[3]) : 0;
    S_ISGID & print->info.st_mode ? chmod[6] = check_chmode1(chmod[6]) : 0;
    S_ISVTX & print->info.st_mode ? chmod[9] = check_chmode2(chmod) : 0;
    for (int i = 0; chmod[i]; i++)
    {
        mx_printchar(chmod[i]);
    }
    mx_printchar(' ');
}

void print_spaces(int size)
{
    for(int i = 0; i <= size; i++)
    {
        mx_printchar(' ');
    }
}

char *minor_to_hex(char *minor)
{
    char *hex_minor = mx_strdup("0x00000000");
    mx_strcpy(hex_minor + (10 - mx_strlen(minor)), minor);
    return hex_minor;
}

char *mx_get_minor(t_li *print)
{
    int minor_num = (int)(print->info.st_rdev & 0xffffff);
    char *minor = NULL;
    if (minor_num > 255)
    {
        minor = minor_to_hex(mx_nbr_to_hex(minor_num));
    }
    else
    {
        minor = mx_itoa(minor_num);
    }
    return minor;
}

char *mx_get_major(t_li *print)
{
    return mx_itoa((int)(((unsigned int)print->info.st_rdev >> 24) & 0xff));
}

void print_duo_cases(t_li *print, t_sz *size)
{
    char *major = mx_get_major(print);
    char *minor = mx_get_minor(print);
    if (size->is_dev == true)
    {
        if (IS_BLK(print->info.st_mode) || IS_CHR(print->info.st_mode))
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

void mx_print_sz(t_li *print, t_sz *size)
{
    char *res_now = mx_itoa(print->info.st_size);
    char *res_sz = mx_itoa(size->sz);
    int counter = 0;
    if (mx_strlen(res_now) == mx_strlen(res_sz))
    {
        print_duo_cases(print, size);
    }
    else if (mx_strlen(res_now) < mx_strlen(res_sz))
    {
        counter = mx_strlen(res_now);
        while (counter != mx_strlen(res_sz))
        {
            mx_printchar(' ');
            counter++;
        }
        print_duo_cases(print, size);
    }
    mx_printchar(' ');
    free(res_now);
    free(res_sz);
}

char *check_grp(t_li *total) {
    struct group *grp = NULL;
    char *name = NULL;
    
    grp = getgrgid(total->info.st_gid);
    if (grp)
    {
        name = mx_strdup(grp->gr_name);
        return name;
    }
    else
    {
        name = mx_itoa(total->info.st_gid);
        return name;
    }
}

char *check_pw(t_li *total)
{
    struct passwd *pw = NULL;
    char *name = NULL;
    pw = getpwuid(total->info.st_uid);
    if (pw)
    {
        name = mx_strdup(pw->pw_name);
        return name;
    }
    else
    {
        name = mx_itoa(total->info.st_uid);
        return name;    
    }
}

void count_size(t_sz *size, t_li *total)
{
    char *name_grp = check_grp(total);
    char *name_pw = check_pw(total);
    if (size->lnk < total->info.st_nlink)
    {
        size->lnk = total->info.st_nlink;
    }
    if (size->sz < total->info.st_size)
    {
        size->sz = total->info.st_size;
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

void size_null(t_sz *size)
{
    size->lnk = 0;
    size->sz = 0;
    size->group = 0;
    size->usr = 0;
}

bool mx_check_device(t_li **names, t_sz *size)
{
    for (int i = 0; names[i]; i++)
    {
        if (IS_BLK(names[i]->info.st_mode) || IS_CHR(names[i]->info.st_mode))
        {
            return size->is_dev = true;
        }
    }
    return size->is_dev = false;
}

void mx_del_liarr(t_li ***args, t_li **dirs)
{
    t_li **del_arr = *args;
    for (int i = 0; del_arr[i]!= NULL; i++)
    {
        mx_strdel(&del_arr[i]->name);
        mx_strdel(&del_arr[i]->path);
        if (del_arr[i]->err)
        {
            mx_strdel(&del_arr[i]->err);
        }
        free(del_arr[i]);
        del_arr[i] = NULL;
    }
    free(*args);
    *args = dirs;
}

void mx_long_out(t_li **names, st_fl *fl, int flag)
{
    t_sz *size = malloc(sizeof(t_sz));
    int blk_size = 0;
    int i = 0;
    size_null(size);
    for (i = 0; names[i]; i++)
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
    mx_check_device(names, size);
    for (i = 0; names[i]; i++)
    {
        mx_print_all(names[i], size, fl);
    }
    free(size);
}



