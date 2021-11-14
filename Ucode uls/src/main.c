#include <uls.h>

int main(int argc, char *argv[])
{
    int count = 1;
    st_fl *fl = get_flags(argv, &count);
    t_li **args = mx_get_names(argc, argv, count);
    int ex = 0;

    if (args)
    {
        mx_opendir(&args, fl);
    }
    if (fl->ex == 1)
    {
        ex = 1;
    }
    free(fl);
    fl = NULL;
    exit(ex);
}

