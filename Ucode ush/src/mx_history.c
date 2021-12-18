#include "ush.h"

char *mx_add_history(Input *input, int *flag, Ush *ush)
{
    char *tmp = NULL;
    if (ush->history->data != NULL)
    {
        if (ush->history->next != NULL && *flag == 0)
        {
            *flag = 1;
            tmp = strdup(ush->history->data);
        }
    }
    ush->history->data = strdup(input->command);
    return tmp;
}

void mx_sort_history(Ush *ush, char *tmp)
{
    char *p = strdup(ush->history->data);
    ush->history->data = strdup(tmp);
    while (ush->history->next != NULL)
    {
        ush->history = ush->history->next;
    }
    ush->history->data = p;
}

List *mx_addelem(List *history)
{
    List *tmp = malloc(sizeof(List));
    List *p = history->next;
    history->next = tmp;
    tmp->next = p;
    tmp->prev = history;
    tmp->data = NULL;
    if (p != NULL)
    {
        p->prev = tmp;
    }
    return tmp;
}

