/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:43:15 by toh               #+#    #+#             */
/*   Updated: 2021/06/23 21:22:39 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				return_free_key(char **key, int ret)
{
	free(*key);
	*key = 0;
	return (ret);
}

static int				change_value(char *str)
{
	t_env	*curr;
	char	*key;

	key = find_key(str);
	curr = g_data.env_head->next;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
		{
			if (!ft_strcmp(key, "PATH") && add_path(curr, str))
				return (return_free_key(&key, 1));
			free(curr->value);
			curr->value = find_value(str);
			curr->equal = 1;
			if (curr->value == 0)
				curr->equal = 0;
			return (return_free_key(&key, 1));
		}
		curr = curr->next;
	}
	return (return_free_key(&key, 0));
}

static int				check_keys(char **keys, int i)
{
	if (!key_isallowed(keys[i]))
	{
		printf("minishell: export: `%s': not a valid identifier\n",
				keys[i]);
		g_data.return_value = 1;
		return (i + 1);
	}
	return (i);
}

static void				add_env(t_cmd *curr, t_env *env_curr, int i)
{
	t_env	*tmp;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (tmp == 0)
		exit_shell();
	if (!ft_strchr(curr->argv[i], '='))
	{
		tmp->key = ft_strdup(curr->argv[i]);
		if (tmp->key == 0)
			exit_shell();
		tmp->value = 0;
		tmp->equal = 0;
	}
	else
		creat_add_env(curr, tmp, i);
	tmp->next = 0;
	env_curr->next = tmp;
}

void					ft_export(t_cmd *curr)
{
	t_env	*env_curr;
	int		i;

	g_data.return_value = 0;
	env_curr = g_data.env_head->next;
	while (env_curr->next)
		env_curr = env_curr->next;
	i = 1;
	while (curr->argv[i])
	{
		i = check_keys(curr->argv, i);
		if (curr->argv[i] == 0)
			break ;
		if (!change_value(curr->argv[i]))
		{
			add_env(curr, env_curr, i);
			env_curr = env_curr->next;
		}
		i++;
	}
}
