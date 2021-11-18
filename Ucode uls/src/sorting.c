#include <uls.h>

int mx_comparer(List *first, List *second, Flag *flags)
{
    if (flags->S == 1)
    {
        if (first->info.st_size < second->info.st_size)
        {
            return 1;
        }
        else if (first->info.st_size == second->info.st_size)
        {
            return mx_strcmp(first->name, second->name);
        }
    }
    else if (flags->t == 1 && flags->c != 1 && flags->u != 1)
    {
        return (first->info.st_mtime == second->info.st_mtime) ? (first->info.st_mtimespec.tv_nsec == second->info.st_mtimespec.tv_nsec) ? mx_strcmp(first->name, second->name) : (first->info.st_mtimespec.tv_nsec < second->info.st_mtimespec.tv_nsec) ? 1 : 0 : (first->info.st_mtime < second->info.st_mtime) ? 1 : 0;
    }
    if (flags->u == 1 && flags->t == 1 && flags->S != 1)
    {
        return (first->info.st_atime == second->info.st_atime) ? (first->info.st_atimespec.tv_nsec == second->info.st_atimespec.tv_nsec) ? mx_strcmp(first->name, second->name) : (first->info.st_atimespec.tv_nsec < second->info.st_atimespec.tv_nsec) ? 1 : 0 : (first->info.st_atime < second->info.st_atime) ? 1 : 0;
    }
    else 
    {
        if (flags->c == 1 && flags->t == 1 && flags->S != 1)
        {
            return (first->info.st_ctime == second->info.st_ctime) ? (first->info.st_ctimespec.tv_nsec == second->info.st_ctimespec.tv_nsec) ? mx_strcmp(first->name, second->name) : (first->info.st_ctimespec.tv_nsec < second->info.st_ctimespec.tv_nsec) ? 1 : 0 : (first->info.st_ctime < second->info.st_ctime) ? 1 : 0;
        }
        else if (flags->t != 1 && flags->S != 1)
        {
            if (mx_strcmp(first->name, second->name) > 0)
            {
                return 1;
            }
        }
        return 0;
    }
}

void sorting(List ***disp, Flag *flags)
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
            else if (mx_comparer(bond[i], bond[k], flags) == flags->r)
            {
                List *tmp = bond[i];
                bond[i] = bond[k];
                bond[k] = tmp;
			}
		}
	}
}

