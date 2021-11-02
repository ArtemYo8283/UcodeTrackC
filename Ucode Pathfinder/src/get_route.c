#include "pathfinder.h"
bool is_bl(int x, int *bl, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (bl[i] == x)
        {
            return true;
        }
    }
    return false;
}
int get_route(int *len, int *weights, char **Names, Bridge *bridges, char *end, char **path, int *bl, int *blked, int *blAlways)
{
    int This_len = 0;
    int This_weight = -1;
    int end_weight = 0;
    int steps = 1;
    char *This_Name = end;
    path[0] = end;
    int prev_bridge_i = -1;
    int needed_bridge = -1;  
    bool flag = true;
    bool out = true;
    for (int j = 0; j < countIsl + 1 && flag == true; j++)
    {
        out = true;
        end_weight = get_weight(Names, weights, end);
        for (int i = 0; i < size - 1; i++)
        {
            if (is_bl(i, bl, (*blked)) == true)
            {
                continue;
            }

            if (!mx_strcmp(bridges[i].I2, end))
            {
                This_Name = bridges[i].I1;
                This_weight = get_weight(Names, weights, bridges[i].I1);
                This_len = bridges[i].Distance;
            }
            else if (!mx_strcmp(bridges[i].I1, end))
            {
                This_Name = bridges[i].I2;
                This_weight = get_weight(Names, weights, bridges[i].I2);
                This_len = bridges[i].Distance;
            }
            else 
            {
                continue;
            }

            if (end_weight < This_len) 
            {
                continue;
            }

            if (This_weight == 0)
            {
                bl[*blked] = i;
                (*blked)++;
                path[steps] = This_Name;
                len[steps - 1] = This_len;
                steps++;
                flag = false;
                out = false;
                needed_bridge = i;
                break;
            }

            if (end_weight - This_len == This_weight)
            {
                prev_bridge_i = i;
                len[steps - 1] = This_len;
                end = This_Name;
                path[steps] = end;
                steps++;
                out = false;
                break;
            }
        } 
        if (out == true)
        {
            if (!mx_strcmp(end, path[0]))
            {
                return -1;
            }
            j = 0;
            end = path[0];
            steps = 1;
            bl[*blked] = prev_bridge_i;
            (*blked)++;
            if (!mx_strcmp(bridges[prev_bridge_i].I1, path[0]) || !mx_strcmp(bridges[prev_bridge_i].I2, path[0]))
            {
                bl[*blAlways] = prev_bridge_i;
                (*blAlways)++;
                *blked = *blAlways;
            }
        }
        if (flag == false && (!mx_strcmp(bridges[needed_bridge].I1, path[0]) || !mx_strcmp(bridges[needed_bridge].I2, path[0])))
        {
            bl[*blAlways] = needed_bridge;
            (*blAlways)++;
            *blked = *blAlways;
        }
    }
    path[steps] = NULL;
    return steps;
}

