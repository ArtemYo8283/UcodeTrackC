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
        write(2, "error: file ", 12);
        write(2, argv[1], mx_strlen(argv[1]));
        write(2, " does not exist\n", 16);
        return -1;
    }
    close(file); //Close file
    
    parse_str(argv[1]);
    
    // mx_printstr("==================\n");
    // for(int i = 0; i < 7; i++)
    // {
    //     mx_print_strarr(str_p_p[i], " ");
    // }
    return 0;
}

