/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:39:21 by toh               #+#    #+#             */
/*   Updated: 2021/06/18 16:06:11 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*find_key(char *str)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	result = ft_strldup(str, i + 1);
	return (result);
}

char			*find_value(char *str)
{
	char	*result;

	if (!ft_strchr(str, '='))
		return (0);
	while (*str != '=')
		str++;
	str++;
	result = ft_strdup(str);
	return (result);
}

static int			check_oldpwd(t_env *tmp, int i, char **envp)
{
	tmp->key = find_key(envp[i]);
	if (!ft_strcmp(tmp->key, "OLDPWD"))
	{
		free (tmp->key);
		i++;
		tmp->key = find_key(envp[i]);
	}
	return (i);
}

int					parse_env(char **envp)
{
	int		i;
	t_env	*curr;
	t_env	*tmp;

	i = 0;
	curr = g_data.env_head;
	while (envp[i])
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (tmp == 0)
			printf("alloccata");
		tmp->equal = 1;
		tmp->next = 0;
		i = check_oldpwd(tmp, i, envp);
		tmp->value = find_value(envp[i]);
		curr->next = tmp;
		curr = curr->next;
		i++;
	}
	return (1);
}