#include <uls.h>

int mx_comparer(List *first, List *second, Flag *fl)
{
    if (fl->S == 1)
    {
        if (first->info.st_size < second->info.st_size)
        {
            return 1;
        }
        if (first->info.st_size == second->info.st_size)
        {
            return mx_strcmp(first->name, second->name);
        }
    }
    else if (fl->t == 1 && fl->c != 1 && fl->u != 1)
    {
        if (first->info.st_mtime == second->info.st_mtime)
        {
            if (first->info.st_mtimespec.tv_nsec == second->info.st_mtimespec.tv_nsec)
            {
                return mx_strcmp(first->name, second->name);
            }
            return (first->info.st_mtimespec.tv_nsec < second->info.st_mtimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_mtime < second->info.st_mtime) ? 1 : 0;
    }
    if (fl->u == 1 && fl->t == 1 && fl->S != 1)
    {
        if (first->info.st_atime == second->info.st_atime)
        {
            if (first->info.st_atimespec.tv_nsec == second->info.st_atimespec.tv_nsec)
            {
                return mx_strcmp(first->name, second->name);
            }
            return (first->info.st_atimespec.tv_nsec < second->info.st_atimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_atime < second->info.st_atime) ? 1 : 0;
    }
    else 
    {
        if (fl->c == 1 && fl->t == 1 && fl->S != 1)
        {
            if (first->info.st_ctime == second->info.st_ctime)
            {
                if (first->info.st_ctimespec.tv_nsec == second->info.st_ctimespec.tv_nsec)
                {
                    return mx_strcmp(first->name, second->name);
                }
                return (first->info.st_ctimespec.tv_nsec < second->info.st_ctimespec.tv_nsec) ? 1 : 0;
            }
            return (first->info.st_ctime < second->info.st_ctime) ? 1 : 0;
        }
        else if (fl->t != 1 && fl->S != 1)
        {
            if (mx_strcmp(first->name, second->name) > 0)
            {
                return 1;
            }
        }
        return 0;
    }
}

void mx_sort(List ***disp, Flag *fl)
{
	List **bond = *disp;
	int size = 0;
    while(bond[size])
    {
        size++;
    }
	for (int i = 0; i < size; i++) 
    {
		for (int k = i + 1; k < size; k++) 
        {
            if (bond[i]->err != NULL)
            {
                if (mx_strcmp(bond[i]->name, bond[k]->name) == 1)
                {
                    List *tmp = bond[i];
                    bond[i] = bond[k];
                    bond[k] = tmp;
                }
            }
            else if (mx_comparer(bond[i], bond[k], fl) == fl->r)
            {
                List *tmp = bond[i];
                bond[i] = bond[k];
                bond[k] = tmp;
			}
		}
	}
}

