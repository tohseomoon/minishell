/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:39:21 by toh               #+#    #+#             */
/*   Updated: 2021/06/04 18:59:11 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct      s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}                   t_env;

char	*ft_strldup(const char *s1, int n)
{
	int		str_len;
	char	*str;

    str_len = ft_strlen(s1);
    if (n > str_len)
        return (0);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == 0)
		return (0);
	ft_strlcpy(str, s1, n);
    str[n] = 0;
	return (str);
}

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


int   parse_env(t_env *env_head, char **env)
{
    int     i;
    t_env   *curr;
    t_env   *tmp;

    i = 0;
    curr = env_head;
    while (env[i])
    {
        tmp = (t_env *)malloc(sizeof(t_env));
        if (tmp == 0)
            return (0);
        tmp->key = find_key(env[i]);
        tmp->value = find_value(env[i]);
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
int     main(int argc, char *argv[], char *env[])
{
    t_env   env_head;
    
    parse_env(&env_head, env);
    print_env(&env_head);
    
}