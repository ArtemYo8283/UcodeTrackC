#pragma once
#include "libmx.h"

typedef struct  Path {
    char* I1;
    char* I2;
    int Distance;
} Paths;

void add_Path(char ***str_p);
char ***parse_str(char *filename);
void print_path(); //========================================

