#pragma once
#include "libmx.h"
#define INT_MAX 2147483647
typedef struct Bridge {
    char* I1;
    char* I2;
    int Distance;
} Bridge;

typedef struct Path {
    char* I1;
    char* I2;
    Bridge* Bridges;
    int count;
} Path;

Bridge *add_Bridges(char ***str_p);
Path* create_routes(Bridge *bridges);
char ***parse_str(char *filename);

//check errors
void checkMaxInt(char ***str_p);
void BridgeDup(char ***str_p);
void checkDist(char ***str_p);
void checkIsl(Bridge *bridges);


void print_path(Path* paths); //========================================

int size;
int countIsl;
int P_size;

