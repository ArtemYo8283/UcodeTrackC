#include "pathfinder.h"

void weight(int *weights, char **nodes, Bridge *bridges, int count)
{
    char **visited = malloc(count * sizeof *visited);
    char *curr;
    int visits = 0;
    int min = 0;
    int weight = 0;
    for (int i = 0; i < count; i++)
    {
        
        min = 0;
        while (is_visited(visited, nodes[min], visits)) min++;
        if (visits == count) break;
        for (int j = 0; j < count; j++)
        {
            if (is_visited(visited, nodes[j], visits)) continue;
            if (weights[j] >= 0 && (weights[min] < 0 || weights[min] > weights[j]))
            {
                min = j;
            }
        }
        
        curr = nodes[min];
        for (int j = 0; j < size - 1; j++)
        {
            if (!mx_strcmp(bridges[j].I1, curr))
            {
                if (is_visited(visited, bridges[j].I2, visits)) continue;
                weight = get_weight(nodes, weights, curr);
                set_weight(&weights, nodes, bridges[j].I2, weight + bridges[j].Distance);
            }
            else if (!mx_strcmp(bridges[j].I2, curr))
            {
                if (is_visited(visited, bridges[j].I1, visits)) continue;
                weight = get_weight(nodes, weights, curr);
                set_weight(&weights, nodes, bridges[j].I1, weight + bridges[j].Distance);
            }
        }
        
        visited[visits] = curr;
        visits++;
    }
    free(visited);
}

