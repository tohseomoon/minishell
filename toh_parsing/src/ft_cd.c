/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:06:26 by toh               #+#    #+#             */
/*   Updated: 2021/06/28 16:52:31 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*find_env_value(char *key)
{
	t_env	*curr;

	curr = g_data.env_head->next;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
			return (curr->value);
		curr = curr->next;
	}
	return (0);
}

static int		change_directory(char *command, int *flag)
{
	char	*path;
	int		result;

	if (command == 0 || (command[0] == '~' && command[1] == 0))
	{
		path = ft_strdup(find_env_value("HOME"));
		*flag = 1;
	}
	else if (command[0] == '-' && command[1] == 0)
	{
		path = ft_strdup(find_env_value("OLDPWD"));
		if (path != 0)
			printf("%s\n", path);
		*flag = 2;
	}
	else
		path = ft_strdup(command);
	result = chdir(path);
	if (path != 0)
		free(path);
	path = 0;
	return (result);
}

static void		add_env(char *key, char *value)
{
	t_env	*tmp;
	t_env	*curr;

	curr = g_data.env_head->next;
	while (curr->next)
		curr = curr->next;
	tmp = (t_env *)malloc(sizeof(t_env));
	if (tmp == 0)
		exit_shell();
	curr->next = tmp;
	curr = curr->next;
	curr->key = ft_strdup(key);
	curr->value = ft_strdup(value);
	curr->next = 0;
}

static void		update_pwd(char *key, char *new_value)
{
	t_env	*curr;
	int		flag;

	flag = 0;
	curr = g_data.env_head->next;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
		{
			free(curr->value);
			curr->value = ft_strdup(new_value);
			flag = 1;
			break ;
		}
		curr = curr->next;
	}
	if (flag == 0)
		add_env(key, new_value);
}

void			ft_cd(t_cmd *curr)
{
	char	*buf;
	int		result;
	int		flag;

	flag = 0;
	buf = 0;
	result = change_directory(curr->argv[1], &flag);
	g_data.return_value = 1;
	if (result == 0)
	{
		buf = getcwd(buf, 0);
		update_pwd("OLDPWD", find_env_value("PWD"));
		update_pwd("PWD", buf);
		free(buf);
		g_data.return_value = 0;
	}
	else if (result == -1 && flag == 1)
		printf("minishell: cd: HOME not set\n");
	else if (result == -1 && flag == 2)
		printf("minishell: cd: OLDPWD not set\n");
	else
		printf("minishell: %s: %s\n", curr->argv[1], strerror(errno));
}
