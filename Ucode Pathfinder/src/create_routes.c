#include "pathfinder.h"
bool is_blacklisted(int c, int *blacklist, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (blacklist[i] == c)
        {
            return true;
        }
    }
    return false;
}

int get_path(int *len, int *weights, char **nodes, Bridge *bridges, int count, char *from, char **path, int *blacklist, int *blked, int *permblkd)
{
    int cur_len = 0;
    int cur_weight = -1;
    int from_weight = 0;
    int steps = 1;
    char *cur_node = from;
    int prev_bridge_i = -1;
    path[0] = from;
    int needed_bridge = -1;
    bool break_flag = true;
    bool fell = true;
    for (int j = 0; j < count + 1 && break_flag; j++)
    {
        fell = true;
        from_weight = get_weight(nodes, weights, from);
        for (int i = 0; i < size - 1; i++)
        {
            if (is_blacklisted(i, blacklist, *blked)) continue;
            if (!mx_strcmp(bridges[i].I1, from))
            {
                cur_node = bridges[i].I2;
                cur_weight = get_weight(nodes, weights, bridges[i].I2);
                cur_len = bridges[i].Distance;
            }
            else if (!mx_strcmp(bridges[i].I2, from))
            {
                cur_node = bridges[i].I1;
                cur_weight = get_weight(nodes, weights, bridges[i].I1);
                cur_len = bridges[i].Distance;
            }
            else continue;
            if (from_weight < cur_len) continue;
            if (cur_weight == 0)
            {
                blacklist[*blked] = i;
                *blked += 1;
                path[steps] = cur_node;
                len[steps - 1] = cur_len;
                steps++;
                break_flag = false;
                fell = false;
                needed_bridge = i;
                break;
            }
            if (from_weight - cur_len == cur_weight)
            {
                prev_bridge_i = i;
                len[steps - 1] = cur_len;
                from = cur_node;
                path[steps] = from;
                steps++;
                fell = false;
                break;
            }
        } 
        if (fell)
        {
            if (!mx_strcmp(from, path[0]))
            {
                return -1;
            }
            j = 0;
            from = path[0];
            steps = 1;
            blacklist[*blked] = prev_bridge_i;
            *blked += 1;
            if (!mx_strcmp(bridges[prev_bridge_i].I1, path[0])
                || !mx_strcmp(bridges[prev_bridge_i].I2, path[0]))
            {
                blacklist[*permblkd] = prev_bridge_i;
                *permblkd += 1;
                *blked = *permblkd;
            }
        }
        if (!break_flag && (!mx_strcmp(bridges[needed_bridge].I1, path[0])
            || !mx_strcmp(bridges[needed_bridge].I2, path[0])))
        {
            blacklist[*permblkd] = needed_bridge;
            *permblkd += 1;
            *blked = *permblkd;
        }
    }
    path[steps] = NULL;
    return steps;
}

void tmp(int *weights, char **Names, Bridge *bridges, int count, char *from, int bridge_count)
{
    int *len = malloc(count * sizeof *len);
    char **path = malloc((count + 1) * sizeof *path);
    path[count] = NULL;
    int *blacklist = malloc(bridge_count * sizeof *blacklist);
    int perm_blocked = 0;
    int steps = 0;
    int blocked = 0;
    while (true)
    {
        steps = get_path(len, weights, Names, bridges, count, from, path, blacklist, &blocked, &perm_blocked);
        if (steps == -1) 
        {
            break;
        }   
        print_path(path[0], path[steps - 1], path, len, steps);
    }
}
void create_routes(Bridge *bridges)
{
    char **Names = (char**)malloc(countIsl);
    int h = 0;
    for(int i = 0; i < countIsl; i++)
    {
        Names[i] = (char*)malloc(256); 
    }
    Names[0] = bridges[0].I1;
    for(int i = 1; i < size - 1; i++)
    {
        int flag = 0;
        for (int j = i - 1; j > -1; j--)
        {
            if(mx_strcmp(bridges[i].I1, bridges[j].I1) == 0 || mx_strcmp(bridges[i].I1, bridges[j].I2) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            h++;
            Names[h] = bridges[i].I1;
        }   
    }
    for(int i = 0; i < size - 1; i++)
    {
        int flag = 0;
        for (int j = i - 1; j > -1; j--)
        {
            if(mx_strcmp(bridges[i].I2, bridges[j].I2) == 0 || mx_strcmp(bridges[i].I2, bridges[j].I1) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            h++;
            Names[h] = bridges[i].I2;
        }   
    }
    int *weights = malloc((countIsl + 1) * sizeof(int));
    for (int i = 0; i < countIsl - 1; i++)
    {
        for (int j = i + 1; j < countIsl; j++)
        {
            for (int z = 0; z < countIsl; z++) 
            {
                weights[z] = -1;
            }
            set_weight(&weights, Names, Names[j], 0);
            weight(weights, Names, bridges, countIsl);
            tmp(weights, Names, bridges, countIsl, Names[i], (size - 1));

        }
    }
}


