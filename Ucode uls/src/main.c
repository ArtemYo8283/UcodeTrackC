#include <uls.h>

int main(int argc, char *argv[])
{
    int count = 1;
    Flag *fl = get_flags(argv, &count);
    List **args = mx_get_names(argc, argv, count);
    if (args)
    {
        mx_opendir(&args, fl);
    }
    free(fl);
    fl = NULL;
    return 0;
}

