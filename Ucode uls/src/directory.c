#include <uls.h>

void join_str(char **res, char *s2)
{
    char *newstr = mx_strnew(mx_strlen(*res) + mx_strlen(s2));
    int i = 0;
    char *s1 = *res;
    for(int j = 0; s1[j]; j++, i++)
    {
        newstr[i] = s1[j];
    }
    for(int j = 0; s2[j]; j++, i++)
    {
        newstr[i] = s2[j];
    }
    mx_strdel(&(*res));
    *res = newstr;
}

List *createNodeF(List *arg)
{
    List *node = (List *)malloc(sizeof (List));
    node->name = mx_strdup(arg->name);
    node->path = mx_strdup(arg->path);
    node->err = arg->err ? mx_strdup(arg->err) : NULL;
    lstat(node->path, &(node->info));
    node->open = arg->open != NULL ? arg->open : NULL;
    return node;
}

void CreateFDE(List ***Flags, List ***dirs, List ***errors, List ***args)
{
    int j = 0;
    int nDir = 0;
    int nErr = 0;
    for (int i = 0; (*args)[i] != NULL; i++)
    {
        ((*args)[i]->err == NULL) ? (((((*args)[i]->info.st_mode) & S_IFMT) != S_IFDIR)) ? j++ : nDir++ : nErr++;
    }
    if (j > 0)
    {
        *Flags = malloc((j + 1) * sizeof(List *));
    }
    if (nDir > 0)
    {
        *dirs = malloc((nDir + 1) * sizeof(List *));
    }
    if (nErr > 0)
    {
        *errors = malloc((nErr + 1) * sizeof(List *));
    }
}

void file_directory(List **args, Type *num, List ***Flags, List ***dirs)
{
    
    if ((((((*args)->info.st_mode)) & S_IFMT) != S_IFDIR))
    {
        (*Flags)[num->n_f++] = createNodeF((*args));
        (*Flags)[num->n_f] = NULL;
    }
    else
    {
        (*dirs)[num->n_d++] = createNodeF((*args));
        (*dirs)[num->n_d] = NULL;
    }
}

List ** list_grab_flags(List ***args, Flag *flags)
{
    List **Flags = NULL;
    List **dirs = NULL;
    List **errors = NULL;
    Type *num = malloc(sizeof(Type));
    num->n_d = 0;
    num->n_e = 0;
    num->n_f = 0;
    num->i = 0;
    CreateFDE(&Flags, &dirs, &errors, args);
    while ((*args)[num->i] != NULL)
    {
        if ((*args)[num->i]->err != NULL)
        {
            errors[num->n_e++] = createNodeF((*args)[num->i]);
            errors[num->n_e] = NULL;
        }
        else
        {
            file_directory(&(*args)[num->i], num, &Flags, &dirs);
        }
        num->i++;
    }
    if (num->n_d > 1)
    {
        flags->Flags = 1;
    }
    free(num);
    return Flags;
}

int check_a(char *name, Flag *flags)
{
    return flags->A != 1 || mx_strcmp(name, ".") == 0 || mx_strcmp(name, "..") == 0 ? 0 : 1;
}

int count_read(List **arg, Flag *flags)
{
    int c = 0;
    List *args = *arg;
    DIR *dptr;
    struct dirent *ds;
    if (((((args->info.st_mode)) & S_IFMT) == S_IFDIR) || (((args->info.st_mode) & S_IFMT) == S_IFLNK))
    {
        if ((dptr = opendir(args->path)) == NULL)
        {
            (*arg)->err = mx_strdup(strerror(errno));
            return -1;
        }
        else 
        {      
            while ((ds = readdir(dptr)) != NULL)
            {
                if (ds->d_name[0] != '.' || check_a(ds->d_name, flags) == 1)
                {
                    c++;
                }
            }
            closedir(dptr);
        }
    }
    return c;
}

List *create_he_node(char *name, char *path)
{
    List *node = (List *)malloc(sizeof(List));
    node->path = mx_strdup(path);
    node->name = mx_strdup(name);
    join_str(&node->path, "/");
    join_str(&node->path, name);
    node->err = NULL;
    if (lstat(node->path, &(node->info)) == -1)
    {
        node->err = mx_strdup(strerror(errno));
    }
    node->open = NULL;
    return node;
}

void open_dir(List ***args, Flag *flags)
{
    DIR *dptr;
    struct dirent *ds;
    int c = 0;
    for (int i = 0; (*args)[i] != NULL; i++)
    {
        c = count_read(&(*args)[i], flags);
        if (c > 0)
        {
            (*args)[i]->open = malloc((c + 1) * sizeof(List *));
            if ((dptr = opendir((*args)[i]->path)) != NULL)
            {
                for (c = 0; (ds = readdir(dptr)) != NULL;)
                {
                    if (ds->d_name[0] != '.' || check_a(ds->d_name, flags) == 1)
                    {
                        (*args)[i]->open[c++] = create_he_node(ds->d_name, (*args)[i]->path);
                    }
                }
                (*args)[i]->open[c] = NULL;
                closedir(dptr);
            }
        }
    }
    outputAll(args, flags);
}

void openDirectory(List ***args, Flag *flags)
{
    List **Flags = list_grab_flags(&(*args), flags);
	if (Flags) 
    {
		output_menu(&Flags, flags, 0);
		if (*args)
        {
			mx_printchar('\n');
        }
		flags->Flags = 1;
	}
    if (*args)
    {
        open_dir(&(*args), flags);
    }
}

char **names(int argc, char **argv, int i, int *c)
{
    int j = i;
    char **names = NULL;
    if (j != argc)
    {
        while(argv[j])
        {
            j++;
        } 
        names = malloc((j - i + 1) * sizeof(char *));
        for(j = 0; argv[i]; i++, j++)
        {
            names[j] = mx_strdup(argv[i]);
        }
        names[j] = NULL;
        *c = j + 1;
    }
    else
    {
        *c = 2;
        names = malloc(2 * sizeof(char *));
        names[0] = mx_strdup(".");
        names[1] = NULL;
    }
    return names;
}

List ** list_grab_names(int argc, char **argv, int i) 
{
    int c = 0;
    char **name = names(argc, argv, i, &c);
    List **args = malloc(c * sizeof(List *));
    for(i = 0; name[i]; i++)
    {
        List *tmp = (List *)malloc(sizeof(List));
        tmp->name = mx_strdup(name[i]);
        tmp->path = mx_strdup(name[i]);
        tmp->err = NULL;
        if (lstat(name[i], &(tmp->info)) == -1)
        {
            tmp->err = mx_strdup(strerror(errno));	
        }
        tmp->open = NULL;
        args[i] = tmp;
    }
    args[i] = NULL;
    return args;
}

