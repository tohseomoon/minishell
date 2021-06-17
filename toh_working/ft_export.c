/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:43:15 by toh               #+#    #+#             */
/*   Updated: 2021/06/17 21:31:13 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_env_str(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = 0;
		i++;
	}
	free(env);
}

void	ft_export_fork(t_cmd *curr)
{
	g_data.env = arr_env_string();
	print_sort_env();
	free_env_str(g_data.env);
	g_data.env = 0;
	g_data.return_value = 0;
}

static int		add_path(t_env *curr, char *str)
{
	char	*value;
	char	*add_path;

	value = find_value(str);
	if (!ft_strncmp(value, "$PATH:", 6))
	{
		add_path = ft_strdup(&(value[5]));
		if (add_path == 0)
			printf("allocate");
		curr->value = ft_strjoin_free_s1(&curr->value, add_path);
		if (curr->value == 0)
			printf("allocate");
		free(value);
		free(add_path);
		return (1);
	}
	return (0);
}

int		change_value(char *str)
{
	t_env	*curr;
	char	*key;

	key = find_key(str);
	curr = g_data.env_head->next;
	while (curr)
	{
		if (ft_strcmp(key, curr->key) == 0)
		{
			if (!ft_strcmp(key, "PATH"))
			{
				if (add_path(curr, str))
				{
					free(key);
					return (1);
				}
			}
			free(curr->value);
			curr->value = find_value(str);
			curr->equal = 1;
			if (curr->value == 0)
				curr->equal = 0;
			free(key);
			key = 0;
			return (1);
		}
		curr = curr->next;
	}
	free(key);
	key = 0;
	return (0);
}

int		key_isallowed(char *str)
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

int		check_keys(char **keys)
{
	int		i;

	i = 1;
	while (keys[i])
	{
		if (!key_isallowed(keys[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", keys[i]);
			g_data.return_value = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

static int		create_path(t_env *tmp, char *str)
{
	char	*value;
	
	value = find_value(str);
	if (!ft_strncmp(value, "$PATH:", 6))
	{
		tmp->value = ft_strdup(&(value[5]));
		if (tmp->value == 0)
			printf("allocate");
		free(value);
		return (1);
	}
	return (0);
}

void	add_env(t_cmd *curr, t_env *env_curr, int i)
{
	t_env	*tmp;
	
	tmp = (t_env *)malloc(sizeof(t_env));
	if (tmp == 0)
		printf("Error_allocate\n");
	if (!ft_strchr(curr->argv[i], '='))
	{
		tmp->key = ft_strdup(curr->argv[i]);
		if (tmp->key == 0)
			printf("Error_allocate\n");
		tmp->value = 0;
		tmp->equal = 0;
	}
	else
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
	tmp->next = 0;
	env_curr->next = tmp;
	env_curr = env_curr->next;
}

void	ft_export(t_cmd *curr)
{
	t_env	*tmp;
	t_env	*env_curr;
	int		i;

	env_curr = g_data.env_head->next;
	while (env_curr->next)
		env_curr = env_curr->next;
	i = 1;
	if (!check_keys(curr->argv))
		return ;
	while(curr->argv[i])
	{
		if (!change_value(curr->argv[i]))
			add_env(curr, env_curr, i);
		i++;
	}
	g_data.return_value = 0;
}
