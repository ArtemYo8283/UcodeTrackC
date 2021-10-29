#include "pathfinder.h"

int get_path(int *len, int *weights, char **nodes, Bridge *bridges, int count, char *from, char **path, int *bl, int *blked, int *blockedAlways)
{
    int This_len = 0;
    int This_weight = -1;
    int from_weight = 0;
    int steps = 1;
    char *This_Name = from;
    int prev_bridge_i = -1;
    path[0] = from;
    int needed_bridge = -1;
    bool flag = true;
    bool out = true;
    for (int j = 0; j < count + 1 && flag == true; j++)
    {
        out = true;
        from_weight = get_weight(nodes, weights, from);
        for (int i = 0; i < size - 1; i++)
        {
            if (is_blacklisted(i, bl, *blked))
            {
                continue;
            }
            if (!mx_strcmp(bridges[i].I1, from))
            {
                This_Name = bridges[i].I2;
                This_weight = get_weight(nodes, weights, bridges[i].I2);
                This_len = bridges[i].Distance;
            }
            else if (!mx_strcmp(bridges[i].I2, from))
            {
                This_Name = bridges[i].I1;
                This_weight = get_weight(nodes, weights, bridges[i].I1);
                This_len = bridges[i].Distance;
            }
            else 
            {
                continue;
            }
            if (from_weight < This_len) 
            {
                continue;
            }
            if (This_weight == 0)
            {
                bl[*blked] = i;
                *blked += 1;
                path[steps] = This_Name;
                len[steps - 1] = This_len;
                steps++;
                flag = false;
                out = false;
                needed_bridge = i;
                break;
            }
            if (from_weight - This_len == This_weight)
            {
                prev_bridge_i = i;
                len[steps - 1] = This_len;
                from = This_Name;
                path[steps] = from;
                steps++;
                out = false;
                break;
            }
        } 
        if (out == true)
        {
            if (!mx_strcmp(from, path[0]))
            {
                return -1;
            }
            j = 0;
            from = path[0];
            steps = 1;
            bl[*blked] = prev_bridge_i;
            *blked += 1;
            if (!mx_strcmp(bridges[prev_bridge_i].I1, path[0]) || !mx_strcmp(bridges[prev_bridge_i].I2, path[0]))
            {
                bl[*blockedAlways] = prev_bridge_i;
                *blockedAlways += 1;
                *blked = *blockedAlways;
            }
        }
        if (flag == false && (!mx_strcmp(bridges[needed_bridge].I1, path[0]) || !mx_strcmp(bridges[needed_bridge].I2, path[0])))
        {
            bl[*blockedAlways] = needed_bridge;
            *blockedAlways += 1;
            *blked = *blockedAlways;
        }
    }
    path[steps] = NULL;
    return steps;
}

