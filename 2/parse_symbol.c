/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:04:28 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/20 12:28:19 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*find_env_value(char *key)
{
	t_env	*curr;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(g_data.return_value));
	curr = g_data.env_head->next;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	//exit_shell("Cannot find matching value");
	return (NULL);
}

int			replace_env(t_cmd *curr, char *command)
{
	int		i;
	int		len;
	char	*key;

	command++;
	len = 0;
	while (command[len] && !is_space(command[len]) &&
			command[len] != D_QUOTE)
		len++;
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		exit_shell();
	i = 0;
	while (i < len)
	{
		key[i] = command[i];
		i++;
	}
	key[i] = '\0';
	// 메모리 누수 가능성 있음
	curr->argv[curr->index] = find_env_value(key);
	free(key);
	return (len + 1);
}

int			replace_back_quote(t_cmd *curr, char *command)
{
	int		i;
	int		len;
	char	*cmd;

	command++;
	len = 0;
	while (command[len] && command[len] != '`')
		len++;
	if (command[len] != '`')
		return (handle_parse_error(B_QUOTE));
	cmd = malloc(sizeof(char) * (len + 1));
	if (!cmd)
		exit_shell();
	i = 0;
	while (i < len)
		cmd[i++] = *(command++);
	cmd[i] = '\0';
	curr->argv[curr->index] = cmd; // execute_cmd(cmd);
	free(cmd);
	return (len + 2);
}

int			replace_path_home(t_cmd *curr)
{
	curr->argv[curr->index] = find_env_value("HOME");
	return (ft_strlen("~"));
}

int			handle_symbol(t_cmd *curr, char *command)
{
	int		i;
	int		result;

	i = 0;
	if (command[i] == '$')
		i += replace_env(curr, command);
	else if (command[i] == '`')
	{
		result = replace_back_quote(curr, command);
		if (result < 0)
			return (-1);
		i += result;
	}
	else if (command[i] == '~')
		i += replace_path_home(curr);
	curr->index++;
	return (i);
}
