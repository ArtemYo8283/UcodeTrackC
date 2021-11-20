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
// int main()
// {
//     struct stat info;
//     lstat("../../file/file1.txt", &info);
//     if(((((info.st_mode) & S_IFMT) != S_IFDIR)))
//     {
//         mx_printstr("is dir");
//     }
// }

