/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:39:21 by toh               #+#    #+#             */
/*   Updated: 2021/06/07 22:01:24 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include<stdio.h>

static char    *find_key(char *str)
{
    char    *result;
    int     i;

    i = 0;
    while (str[i] != '=')
        i++;
    result = ft_strldup(str, i + 1);
    return (result);
}

static char    *find_value(char *str)
{
    char    *result;

    while (*str != '=')
        str++;
    str++;
    result = ft_strdup(str);
    return (result);
}


int   parse_env(t_env *env_head, char **envp)
{
    int     i;
    t_env   *curr;
    t_env   *tmp;

    i = 0;
    curr = env_head;
    while (envp[i])
    {
        tmp = (t_env *)malloc(sizeof(t_env));
        if (tmp == 0)
            return (0);
        tmp->key = find_key(envp[i]);
        tmp->value = find_value(envp[i]);
        tmp->next = 0;
        curr->next = tmp;
        curr = curr->next;
        i++;
    }
    return (1);
}

void    print_env(t_env *env_head)
{
    t_env   *curr;

    curr = env_head->next;
    while (curr)
    {
        printf("=====================================================\n");
        printf("%s\n", curr->key);
        printf("%s\n", curr->value);
        printf("=====================================================\n");
        curr = curr->next;
    }
}
