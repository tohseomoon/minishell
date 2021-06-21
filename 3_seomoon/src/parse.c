/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:25:32 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/21 12:56:19 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			count_words(char *str)
{
	int				i;
	int				count;

	i = 0;
	while (is_space(str[i]))
		i++;
	count = 0;
	while (str[i] && !is_command_end(str[i]))
	{
		if (!is_space(str[i]) &&
				(is_space(str[i + 1]) || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int					push_arg(t_cmd *curr, char *command)
{
	int				i;
	int				len;

	len = 0;
	while (command[len] && !is_seperator(command[len]))
		len++;
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (!curr->argv[curr->index])
		exit_shell();
	i = 0;
	while (*command && !is_space(*command))
	{
		curr->argv[curr->index][i] = *command;
		i++;
		command++;
	}
	curr->argv[curr->index][i] = '\0';
	curr->index++;
	return (i);
}

static int			split_command(t_cmd *curr, char *command)
{
	int				i;
	int				result;

	i = 0;
	curr->index = 0;
	while (command[i] && !is_command_end(command[i]))
	{
		if (command[i] == S_QUOTE || command[i] == D_QUOTE)
		{
			result = handle_quote(curr, command, i);
			if (result < 0)
				return (result);
			i += result;
		}
		else if (command[i] == ESCAPE)
			i += handle_escape(curr, command + i, 0);
		else if (is_symbol(command[i]) || command[i] == '~')
		{
			result = handle_symbol(curr, command + i);
			if (result < 0)
				return (result);
			i += result;
		}
		else
			i += push_arg(curr, command + i);
		while (command[i] && is_space(command[i]))
			i++;
	}
	curr->argv[curr->index] = NULL;
	return (i);
}

void				add_new_cmd(t_cmd *curr)
{
	t_cmd			*tmp;

	tmp = curr;
	curr->next = malloc(sizeof(t_cmd));
	if (!curr->next)
		exit_shell();
	curr = curr->next;
	ft_memset(curr, 0, sizeof(t_cmd));
	curr->prev = tmp;
	curr->fd_out = 1;
}

t_cmd				*init_cmd(void)
{
	t_cmd			*curr;

	g_data.cmd_head->next = malloc(sizeof(t_cmd));
	if (!g_data.cmd_head->next)
		exit_shell();
	curr = g_data.cmd_head->next;
	ft_memset(curr, 0, sizeof(t_cmd));
	curr->fd_out = 1;
	return (curr);
}

int					parse_command(char *command)
{
	int				i;
	t_cmd			*curr;

	curr = init_cmd();
	i = 0;
	while (command[i] != '\0')
	{
		curr->argc = count_words(command);
		curr->argv = malloc(sizeof(char *) * (curr->argc + 1));
		if (!curr->argv)
			exit_shell();
		i = split_command(curr, command);
		if (i < 0)
			return (0);
		if (command[i] == '|')
		{
			if (check_command_error(curr->argv, command, i))
				return (0);
			add_new_cmd(curr);
			i++;
		}
	}
	if (check_command_error(curr->argv, command, i))
		return (0);
	return (1);
}
