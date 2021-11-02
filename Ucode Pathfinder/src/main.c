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
    
    char*** stri = parse_str(argv[1]);
    checkDist(stri);
    checkMaxInt(stri);
    BridgeDup(stri);
    struct Bridge *bridges = add_Bridges(stri);
    checkIsl(bridges);
    create_routes(bridges);
    free(bridges);
    mx_del_strarr(stri);
    return 0;
}

