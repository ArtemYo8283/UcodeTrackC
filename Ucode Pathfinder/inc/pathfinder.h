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

int get_weight(char **nodes, int *weights, char *s);
void set_weight(int **weights, char **nodes, char *s, int w);

void weight(int *weights, char **nodes, Bridge *bridges, int count);
int get_node_index(char **nodes, char *node);
bool is_visited(char **visited, char *s, int visits);

void print_path(char *I1, char *I2, char** Bridges, int *Distance, int count);

int size;
int countIsl;
int P_size;

