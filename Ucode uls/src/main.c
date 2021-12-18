#include <uls.h>

int main(int argc, char *argv[])
{
    int count = 1;
    Flag *flags = Flag_grab_flags(argv, &count);
    List **args = list_grab_names(argc, argv, count);
    if (args)
    {
        openDirectory(&args, flags);
    }
    free(flags);
    flags = NULL;
    return 0;
}
