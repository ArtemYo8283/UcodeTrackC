#pragma once
#include "libmx.h"
#define INT_MAX 2147483647
typedef struct Bridge {
    char* I1;
    char* I2;
    int Distance;
} Bridge;

Bridge *add_Bridges(char ***str_p);
void create_routes(Bridge *bridges);
char ***parse_str(char *filename);
//check errors
void checkMaxInt(char ***str_p);
void BridgeDup(char ***str_p);
void checkDist(char ***str_p);
void checkIsl(Bridge *bridges);
int get_weight(char **Names, int *weights, char *Name);
void weight(int *weights, char **Names, Bridge *bridges);
bool is_vstd(char **visited, char *visit, int visits);
void print_path(char *I1, char *I2, char** Bridges, int *Distance, int count);
int get_route(int *len, int *weights, char **Names, Bridge *bridges, char *end, char **path, int *bl, int *blked, int *blAlways);
Bridge * sort_bridges(Bridge *bridges, char** Names);
int get_dist_by_isl(Bridge* bridges, char* A, char* B);
int size;
int countIsl;
int P_size;

