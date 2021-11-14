#include <uls.h>

void mx_join(char **res, char *s2) {
    char *newstr = mx_strnew(mx_strlen(*res) + mx_strlen(s2));
    int i = 0;
    int si = -1;
    char *s1 = *res;

    while(s1[++si]) {
        newstr[i] = s1[si];
        i++;
    }
    si = -1;
    while(s2[++si]) {
        newstr[i] = s2[si];
        i++;
    }
    mx_strdel(&(*res));
    *res = newstr;
}

t_li *create_file_node(t_li *arg)
{
    t_li *node = (t_li *)malloc(1 * sizeof (t_li));

    node->name = mx_strdup(arg->name);
    node->path = mx_strdup(arg->path);
    if (arg->err)
    {
        node->err = mx_strdup(arg->err);
    }
    else 
    {
        node->err = NULL;
    }
    lstat(node->path, &(node->info));
    if (arg->open != NULL)
    {
        node->open = arg->open;
    }
    else 
    {
        node->open = NULL;
    }
    return node;
}

void create_fde(t_li ***files, t_li ***dirs, t_li ***errors, t_li ***args)
{
    int j = 0;
    int nDir = 0;
    int nErr = 0;
    for (int i = 0; (*args)[i] != NULL; i++)
    {
        if ((*args)[i]->err == NULL)
        {
            if (!IS_DIR((*args)[i]->info.st_mode))
            {
                j++;
            } 
            else
            {
                nDir++;
            }
        } 
        else
        {
            nErr++;
        }
    }
    if (j > 0)
    {
        *files = malloc((j + 1) * sizeof(t_li *));
    }
    if (nDir > 0)
    {
        *dirs = malloc((nDir + 1) * sizeof(t_li *));
    }
    if (nErr > 0)
    {
        *errors = malloc((nErr + 1) * sizeof(t_li *));
    }
}

s_type *create_num()
{
    s_type *num = malloc(sizeof (s_type));
    num->n_d = 0;
    num->n_e = 0;
    num->n_f = 0;
    num->i = 0;
    return num;
}

void fdir(t_li **args, s_type *num, t_li ***files, t_li ***dirs)
{
    if (!IS_DIR((*args)->info.st_mode))
    {
        (*files)[num->n_f++] = create_file_node((*args));
        (*files)[num->n_f] = NULL;
    }
    else
    {
        (*dirs)[num->n_d++] = create_file_node((*args));
        (*dirs)[num->n_d] = NULL;
    }
}

t_li **mx_get_files(t_li ***args, st_fl *fl)
{
    t_li **files = NULL;
    t_li **dirs = NULL;
    t_li **errors = NULL;
    s_type *num = create_num();
    create_fde(&files, &dirs, &errors, args);
    for (; (*args)[num->i] != NULL; num->i++)
    {
        if ((*args)[num->i]->err == NULL)
        {
            fdir(&(*args)[num->i], num, &files, &dirs);
        }
        else
        {
            errors[num->n_e++] = create_file_node((*args)[num->i]);
            errors[num->n_e] = NULL;
        }
    }
    if (num->n_d > 1)
    {
        fl->files = 1;
    }
    free(num);
    return files;
}

int check_a(char *name, st_fl *fl)
{
    if (fl->A != 1)
    {
        return 0;
    }
    if (mx_strcmp(name, ".") == 0)
    {
        return 0;
    }
    if (mx_strcmp(name, "..") == 0)
    {
        return 0;
    }
    return 1;
}

int count_read(t_li **arg, st_fl *fl)
{
    int count = 0;
    t_li *args = *arg;
    DIR *dptr;
    struct dirent *ds;

    if (IS_DIR(args->info.st_mode) || IS_LNK(args->info.st_mode))
    {
        if ((dptr = opendir(args->path)) != NULL)
        {
            while ((ds = readdir(dptr)) != NULL)
            {
                if (ds->d_name[0] != '.' || check_a(ds->d_name, fl) == 1)
                {
                    count++;
                }
            }
            closedir(dptr);
        }
        else 
        {
            (*arg)->err = mx_strdup(strerror(errno));
            fl->ex = 1;
            return -1;
        }
    }
    return count;
}

t_li *create_he_node(char *name, char *path)
{
    t_li *node = (t_li *)malloc(1 * sizeof(t_li));

    node->name = mx_strdup(name);
    node->path = mx_strdup(path);
    mx_join(&node->path, "/");
    mx_join(&node->path, name);
    node->err = NULL;
    if (lstat(node->path, &(node->info)) == -1)
    {
        node->err = mx_strdup(strerror(errno));
    }
    node->open = NULL;
    return node;
}

void open_dir(t_li ***args, st_fl *fl)
{
    DIR *dptr;
    struct dirent *ds;
    int count = 0;

    for (int i = 0; (*args)[i] != NULL; i++)
    {
        count = count_read(&(*args)[i], fl);
        if (count > 0)
        {
            (*args)[i]->open = malloc((count + 1) * sizeof(t_li *));
            if ((dptr = opendir((*args)[i]->path)) != NULL)
            {
                for (count = 0; (ds = readdir(dptr)) != NULL;)
                {
                    if (ds->d_name[0] != '.' || check_a(ds->d_name, fl) == 1)
                    {
                        (*args)[i]->open[count++] = create_he_node(ds->d_name, (*args)[i]->path);
                    }
                }
                (*args)[i]->open[count] = NULL;
                closedir(dptr);
            }
        }
    }
    mx_out_put_all(args, fl);
}

void mx_opendir(t_li ***args, st_fl *fl)
{
    t_li **files = mx_get_files(&(*args), fl);
	if (files) 
    {
		mx_out_put_menu(&files, fl, 0);
		if (*args)
        {
			mx_printchar('\n');
        }
		fl->files = 1;
	}
    if (*args)
    {
        open_dir(&(*args), fl);
    }
}

t_li *create_li_node(char *data)
{
    t_li *node = (t_li *)malloc(1 * sizeof(t_li));
    node->name = mx_strdup(data);
    node->path = mx_strdup(data);
    node->err = NULL;
    if (lstat(data, &(node->info)) == -1)
    {
        node->err = mx_strdup(strerror(errno));	
    }
    node->open = NULL;
    return node;
}

t_li **create_list(char **name, int count)
{
    t_li **new = malloc(count * sizeof(t_li *));
    int i = 0;
    for (i = 0; name[i]; i++)
    {
        new[i] = create_li_node(name[i]);
    }
    new[i] = NULL;
    return new;
}

char **names(int argc, char **argv, int i, int *count)
{
    int j = i;
    char **names = NULL;

    if (i == argc)
    {
        *count = 2;
        names = malloc(2 * sizeof(char *));
        names[0] = mx_strdup(".");
        names[1] = NULL;
    }
    else
    {
        for (; argv[j]; j++);
        names = malloc((j - i + 1) * sizeof(char *));
        for(j = 0; argv[i]; i++, j++)
        {
            names[j] = mx_strdup(argv[i]);
        }
        names[j] = NULL;
        *count = j + 1;
    }
    return names;
}

t_li **mx_get_names(int argc, char **argv, int i) 
{
    int count = 0;
    char **name = names(argc, argv, i, &count);
    t_li **args = create_list(name, count);
    return args;
}

