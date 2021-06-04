#include "../minishell.h"
#include <stdio.h>

static int    copy_quotes(char **input, char **tmp)
{
    (*input)++;
    while (**input != '\'' && **input != '\"')
    {
        **tmp = **input;
        (*tmp)++;
        (*input)++;
        if (**input == 0)
            return (0);
    }
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
    space_flag = 0;
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
    *tmp = 0;
    return (result);
}

void    parse_input(t_cmd *cmd_head, char *input)
{
    char    *str;
    char    *tmp;
    t_cmd   *curr;
    t_cmd   *cmd_tmp;
    int     cnt;
    int     i;

    str = del_space(input);
    tmp = str;
    curr = cmd_head->next;
    i = 0;
    while (tmp)
    {
        if (*tmp != '|' && *tmp != ';')
        {
            i = 0;
            cmd_tmp = (t_cmd *)malloc
            curr = curr->next;
        }
    }
}


int     main(void)
{
    printf("%s\n", del_space("ls        -la > a         >> b | grep \"          a\" ; pwd"));
}
/*
aa    "     ddd"


ls -la > a >> b | grep "a" ; pwd

*/