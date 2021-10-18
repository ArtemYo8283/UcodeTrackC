#include "pathfinder.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        write(2, "usage: ./pathfinder [filename]\n", 31);
        return -1;
    }

    int file = open_f(argv[1]); //Open file
    if(file == -1)
    {
        write(2, "error: file [filename] does not exist\n", 38);
        return -1;
    }
    close(file); //Close file
    
    char ***str_p_p = parse_str(argv[1]);
    str_p_p = NULL;
    // mx_printstr("==================\n");
    // for(int i = 0; i < 7; i++)
    // {
    //     mx_print_strarr(str_p_p[i], " ");
    // }
    return 0;
}

