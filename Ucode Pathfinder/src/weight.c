#include "pathfinder.h"
void set_weight(int **weights, char **Names, char *str, int weight)
{
    for (int i = 0; i < countIsl; i++)
    {
        if (!mx_strcmp(Names[i], str))
        {
            if ((*weights)[i] < weight && (*weights)[i] > 0) 
            {
                return;
            }
            (*weights)[i] = weight;
            return;
        }
    }
}
void weight(int *weights, char **Names, Bridge *bridges)
{
    char **visited = malloc(countIsl * sizeof(*visited));
    char *curr;
    int visits = 0;
    int min_id = 0;
    int weight = 0;
    for (int i = 0; i < countIsl; i++)
    {
        min_id = 0;
        for (;is_vstd(visited, Names[min_id], visits); min_id++);
        if (visits == countIsl) 
        {
            break;
        }
        for (int j = 0; j < countIsl; j++)
        {
            if (is_vstd(visited, Names[j], visits))
            {
                continue;
            }
            if (weights[j] > -1 && (weights[min_id] < 0 || weights[min_id] > weights[j]))
            {
                min_id = j;
            }
        }
        curr = Names[min_id];
        for (int j = 0; j < size - 1; j++)
        {
            if (!mx_strcmp(bridges[j].I1, curr))
            {
                if (is_vstd(visited, bridges[j].I2, visits))
                {
                    continue;
                }
                weight = get_weight(Names, weights, curr);
                set_weight(&weights, Names, bridges[j].I2, weight + bridges[j].Distance);
            }
            else if (!mx_strcmp(bridges[j].I2, curr))
            {
                if (is_vstd(visited, bridges[j].I1, visits))
                {
                    continue;
                }
                weight = get_weight(Names, weights, curr);
                set_weight(&weights, Names, bridges[j].I1, weight + bridges[j].Distance);
            }
        }
        visited[visits] = curr;
        visits++;
    }
    free(visited);
}

