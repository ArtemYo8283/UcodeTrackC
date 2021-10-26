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
    
    // for(int i = 0; i < size - 1; i++)
    // {
    //     mx_printstr(stri[i][0]);
    //     mx_printchar('|');
    //     mx_printstr(stri[i][1]);
    //     mx_printchar('\n');
    // }
    // mx_printint(countIsl);
    // mx_printchar('\n');
    checkDist(stri);
    checkMaxInt(stri);
    BridgeDup(stri);

    struct Bridge *bridges = add_Bridges(stri);
    checkIsl(bridges);
    // for(int i = 0; i < size - 1; i++)
    // {
    //     mx_printstr("========================================\n");
    //     mx_printstr(bridges[i].I1);
    //     mx_printchar('-');
    //     mx_printstr(bridges[i].I2);
    //     mx_printchar('\n');
    //     mx_printint(bridges[i].Distance);
    //     mx_printchar('\n');
    //     mx_printstr("========================================\n");
    // }

    struct Path *pathes = create_routes(bridges);

    print_path(pathes);
    return 0;
}

