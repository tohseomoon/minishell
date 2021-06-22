/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:16:49 by toh               #+#    #+#             */
/*   Updated: 2021/06/21 11:17:28 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			key_isallowed(char *str)
{
	int		i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] != '=' && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int			add_path(t_env *curr, char *str)
{
	char	*value;
	char	*add_path;

	value = find_value(str);
	if (value == 0)
		return (0);
	if (!ft_strncmp(value, "$PATH:", 6))
	{
		add_path = ft_strdup(&(value[5]));
		if (add_path == 0)
			exit_shell();
		curr->value = ft_strjoin_free_s1(&curr->value, add_path);
		if (curr->value == 0)
			exit_shell();
		free(value);
		free(add_path);
		return (1);
	}
	return (0);
}

static int	create_path(t_env *tmp, char *str)
{
	char	*value;

	value = find_value(str);
	if (!ft_strncmp(value, "$PATH:", 6))
	{
		tmp->value = ft_strdup(&(value[5]));
		if (tmp->value == 0)
			exit_shell();
		free(value);
		return (1);
	}
	return (0);
}

void		creat_add_env(t_cmd *curr, t_env *tmp, int i)
{
	tmp->key = find_key(curr->argv[i]);
	if (!ft_strcmp(tmp->key, "PATH"))
	{
		if (!create_path(tmp, curr->argv[i]))
			tmp->value = find_value(curr->argv[i]);
	}
	else
		tmp->value = find_value(curr->argv[i]);
	tmp->equal = 1;
}
