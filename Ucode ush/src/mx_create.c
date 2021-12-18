#include "ush.h"

// t_com_sub* mx_create_com_sub()
// {
//     t_com_sub *com_sub = malloc(sizeof(t_com_sub));
//     com_sub->back_first = 0;
//     com_sub->back_first_index = 0;
//     com_sub->back_end = 0;
//     com_sub->back_end_index = 0;
//     com_sub->space = 0;
//     com_sub->space_first_index = 0;
//     com_sub->space_end_index = 0;
//     com_sub->tmp_str = NULL;
//     com_sub->tmp_data = NULL;
//     com_sub->cout_execute = NULL;
//     com_sub->tmp_join = NULL;
//     com_sub->status = 0;
//     return com_sub;
// }
List* lst_create()
{
    List *lst = malloc(sizeof(List));
    lst->data = NULL;
    lst->next = NULL;
    lst->prev = NULL;
    return lst;
}

Ush* mx_create_ush(char **argv)
{
    Ush *ush = malloc(sizeof(Ush));
    ush->command = NULL;
    ush->history = NULL;
    ush->exit_status = -1;
    ush->return_value = 0;
    ush->exit_non_term = 0;
    ush->pids = NULL;
    ush->str_input = NULL;
    ush->ush_path = find_ush_path(argv);
    ush->history = lst_create();
    ush->pwd_l = mx_getenv("PWD");
    return ush;
}

// Redirect *mx_create_redirect(int flag_redir)
// {
//     Redirect *redirect = malloc(sizeof(Redirect));
//     redirect->err = mx_strnew(1000);
//     redirect->out = mx_strnew(1000);
//     redirect->flag = flag_redir;
//     pipe(redirect->fd_return);
//     pipe(redirect->fdout);
//     pipe(redirect->fderr);
//     return redirect;
// }



Input *iniInput()
{
    Input *input = malloc(sizeof(Input));
    input->len = 0;
    input->command = mx_strnew(1);
    input->ctrl_c = 0;
    input->coursor_position = 0;
    input->input_ch = '\0';
    input->input_ch_arr = (char *)&input->input_ch;
    return input;
}

// void mx_parenRedirect(Redirect *redirect, int *return_)
// {
//     if (redirect->flag == 1)
//     {
//         mx_read_from_pipe(redirect->out, 1000, redirect->fdout);
//     }
//     mx_read_from_pipe(redirect->err, 1000, redirect->fderr);
//     if (mx_strlen(redirect->err) != 0)
//     {
//         *return_ = 1;
//         mx_printstr(redirect->err);
//     }
// }

// void mx_child_redirect(Redirect *redirect)
// {
//     signal(SIGTSTP, SIG_DFL);
//     if (redirect->flag == 1)
//     {
//         if (dup2(redirect->fdout[1], 1) == -1)
//         {
//             perror("dup2");
//         }
//         close(redirect->fdout[0]);
//     }
//     if (dup2(redirect->fderr[1], 2) == -1)
//     {
//         perror("dup2");
//     }
//     close(redirect->fderr[1]);
// }

