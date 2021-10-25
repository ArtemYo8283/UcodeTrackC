#pragma once
#include "libmx.h"
#define INT_MAX 2147483647
typedef struct Path {
    char* I1;
    char* I2;
    int Distance;
} Path;

Path *add_Paths(char ***str_p);
char ***parse_str(char *filename);

//check errors
void checkMaxInt(char ***str_p);
void BridgeDup(char ***str_p);
void checkDist(char ***str_p);
void checkIsl(Path *path);


void print_path(); //========================================

int size;
int countIsl;

