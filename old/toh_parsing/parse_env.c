/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:39:21 by toh               #+#    #+#             */
/*   Updated: 2021/06/15 14:46:03 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*find_key(char *str)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	result = ft_strldup(str, i + 1);
	return (result);
}

static char			*find_value(char *str)
{
	char	*result;

	while (*str != '=')
		str++;
	str++;
	result = ft_strdup(str);
	return (result);
}

int					parse_env(t_env *env_head, char **envp)
{
	int		i;
	t_env	*curr;
	t_env	*tmp;

	i = 0;
	curr = env_head;
	while (envp[i])
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (tmp == 0)
			return (0);
		tmp->key = find_key(envp[i]);
		tmp->value = find_value(envp[i]);
		tmp->new = 0;
		tmp->equal = 1;
		tmp->next = 0;
		curr->next = tmp;
		curr = curr->next;
		i++;
	}
	return (1);
}

static char			*find_path(void)
{
	t_env	*curr;
	char	*path;

	curr = g_data.env_head->next;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "PATH"))
			path = ft_strdup(curr->value);
		curr = curr->next;
	}
	return (path);
}

char				**parse_path(void)
{
	char	*path;
	char	**split_path;

	path = find_path();
	split_path = ft_split(path, ':');
	free(path);
	return (split_path);
}
