/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:04:28 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/22 13:39:12 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*find_env_value(char *key)
{
	t_env	*curr;

	if (ft_strcmp(key, "?") == 0)
	{
		free(key);
		return (ft_itoa(g_data.return_value));
	}
	curr = g_data.env_head->next;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(key);
			return (curr->value);
		}
		curr = curr->next;
	}
	free(key);
	return (ft_strdup(""));
}

static int			replace_env(t_cmd *curr, char *command)
{
	int		i;
	int		len;
	char	*key;

	command++;
	if (*command == D_QUOTE)
	{
		curr->argv[curr->index] = ft_strdup("$");
		return (1);
	}
	len = 0;
	while (is_letter(command[len]) || command[len] == '?')
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
	curr->argv[curr->index] = ft_strdup(find_env_value(key));
	return (len + 1);
}

static int			replace_back_quote(t_cmd *curr, char *command)
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
	curr->argv[curr->index] = cmd;
	free(cmd);
	return (len + 2);
}

static int			replace_path_home(t_cmd *curr)
{
	curr->argv[curr->index] = ft_strdup(find_env_value("HOME"));
	return (ft_strlen("~"));
}

int					handle_symbol(t_cmd *curr, char *command)
{
	int		i;
	int		result;

	i = 0;
	if (command[i] == '$')
	{
		result = replace_env(curr, command);
		if (result < 0)
			return (i + push_arg(curr, command));
		i += result;
	}
	else if (command[i] == '`')
	{
		result = replace_back_quote(curr, command);
		if (result < 0)
			return (-1);
		i += result;
	}
	else if (command[i] == '~')
		i += replace_path_home(curr);
	if (command[i] == S_QUOTE || command[i] == D_QUOTE)
		return (i);
	i += check_remain_character(curr, command + i);
	return (i);
}
