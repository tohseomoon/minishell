#include "../minishell.h"
#include <stdio.h>

static int    copy_quotes(char **input, char **tmp)
{
    **tmp = **input;
    (*input)++;
    (*tmp)++;
    while (**input != '\'' && **input != '\"')
    {
        **tmp = **input;
        (*tmp)++;
        (*input)++;
        if (**input == 0)
            return (0);
    }
    **tmp = **input;
    (*tmp)++;
    return (1);
}

static void     copy_not_space(char **input, char **tmp, int *space_flag)
{
    if (**input == ' ' && *space_flag == 0)
    {
        *space_flag = 1;
        **tmp = **input;
        (*tmp)++;
    }
    else if (**input != ' ')
    {
        *space_flag = 0;
        **tmp = **input;
        (*tmp)++;
    }
}

static char     *del_space(char *input)
{
    char    *result;
    char    *tmp;
    int     space_flag;

    tmp = ft_strdup(input);
    result = tmp;
    space_flag = 1;
    while (*input)
    {
        if (*input == '\'' || *input == '\"')
        {
            space_flag = 0;
            if (!(copy_quotes(&input, &tmp)))
                return (0);
        }
        else
            copy_not_space(&input, &tmp, &space_flag);
        input++;
    }
    if (*(tmp - 1) == ' ')
        tmp--;
    *tmp = 0;
    return (result);
}

t_cmd     *creat_struct_cmd(void)
{
    t_cmd   *tmp;

    tmp = (t_cmd *)malloc(sizeof(t_cmd));
    if (tmp == 0)
        return (0); 
    tmp->next = 0;
    return (tmp);
}

int     cnt_cmd(char *str)
{
    int     cnt;
    int     i;

    cnt = 1;
    i = 0;
    while (str[i])
    {
        if (str[i] == '|' || str[i] == ';')
            cnt++;
        i++;
    }
    return (cnt);
}

char    *split_cmd_cut_str(char **str)
{
    char    *result;
    char    *start;
    int     cnt;

    cnt = 0;
    start = *str;
    while (**str != ';' && **str != '|' && **str)
    {
        (*str)++;
        cnt++;
    }
    result = ft_strldup(start, cnt + 1);
    if (result == 0)
        return (0);
    return (result);
}

char    **split_cmd(char *str)
{
    char    **result;
    char    *start;
    int     cnt;
    int     i;

    cnt = cnt_cmd(str);
    result = (char **)malloc(sizeof(char *) * (cnt + 1));
    result[cnt] = 0;
    if (result == 0)
        return (0);
    i = 0;
    while (*str)
    {
        result[i] = split_cmd_cut_str(&str);
        if (result[i] == 0)
            return (0);
        if (*str == 0)
            break ;
        str++;
        i++;
    }
    return (result);
}

void    cut_cmd_space(char **cut_cmd)
{
    int     i;
    char    *tmp;

    i = 0;
    while (cut_cmd[i])
    {
        tmp = cut_cmd[i];
        cut_cmd[i] = del_space(cut_cmd[i]);
        free(tmp);
        tmp = 0;
        i++;
    }
}

int     cnt_cmd_argv(char *cmd)
{
    int     cnt;
    int     i;

    cnt = 1;
    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '\'' || cmd[i] == '\"')
        {
            i++;
            while (cmd[i] != '\'' && cmd[i] != '\"')
                i++;
        }
        if (cmd[i] == ' ')
            cnt++;
        i++;
    }
    return (cnt);
}

int     cnt_cmd_argv_word(char **str, char **start, int word_cnt)
{
    word_cnt = 0;
    if (**str == ' ')
            (*str)++;
    else if (**str == '\'' || **str == '\"')
    {
        (*str)++;
        *start = *str;
        while (**str != '\'' && **str != '\"')
        {
            word_cnt++;
            (*str)++;
        }
    }
    else
    {
        *start = *str;
        while (**str != ' ' && **str != 0)
        {
            (*str)++;
            word_cnt++;
        }
    }
    return (word_cnt);
}

char    **add_cmd_argv(char *str, int cnt)
{
    char    **result;
    char    *start;
    int     word_cnt;
    int     i;

    result = (char **)malloc(sizeof(char *) * (cnt + 1));
    if (result == 0)
        return (0);
    result[cnt] = 0;
    i = 0;
    while (i < cnt && *str)
    {
        word_cnt = cnt_cmd_argv_word(&str, &start, word_cnt);
        result[i] = ft_strldup(start, word_cnt + 1);
        if (*str == 0)
            break ;
        str++;
        i++;
    }
    return (result);
}

int    add_list_cmd(t_cmd *head, char **cut_cmd)
{
    int     i;
    
    i = 0;
    while (cut_cmd[i])
    {
        head->next = creat_struct_cmd();
        if (head->next == 0)
            return (0);
        head = head->next;
        head->argc = cnt_cmd_argv(cut_cmd[i]);
        head->argv = add_cmd_argv(cut_cmd[i], head->argc);
        free(cut_cmd[i]);
        cut_cmd[i] = 0;
        i++;
    }
    return (1);
}

int     parse_input(t_cmd *cmd_head, char *input)
{
    char    **cut_cmd;

    cut_cmd = split_cmd(input);
    cut_cmd_space(cut_cmd);
    if (!add_list_cmd(cmd_head, cut_cmd))
        return (0);
    free(cut_cmd);
    cut_cmd = 0;
    return (1);
}

void    print_cmd(t_cmd *head)
{
    int     i;

    head = head->next;
    while (head)
    {
        printf("=========================\n");
        i = 0;
        printf("argc : %d\n", head->argc);
        while (head->argv[i])
        {
            printf("argv %d : %s\n", i, head->argv[i]);
            i++;    
        }
        printf("=========================\n");
        head = head->next;
    }
}

void    free_cmd(t_cmd *head)
{
    t_cmd   *tmp;
    int     i;
    
    head = head->next;
    while (head)
    {
        tmp = head->next;
        i = 0;
        while (head->argv[i])
        {
            free(head->argv[i]);
            head->argv[i] = 0;
            i++;
        }
        free(head->argv);
        head->argv = 0;
        free(head);
        head = tmp;
    }
}

int     main(int argc, char **argv, char **envp)
{
    t_cmd   cmd_head;
    char    *input = "ls -la > a   \"  12\"  | pwd ; pwd | cd ; cd     ";

    parse_input(&cmd_head, input);
    print_cmd(&cmd_head);
    free_cmd(&cmd_head);
    return (0);
}