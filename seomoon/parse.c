/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:25:32 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/16 22:09:40 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			count_words(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] && !is_command_end(str[i]))
	{
		if (!is_seperator(str[i]) &&
				(is_seperator(str[i + 1]) || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int			push_arg(t_cmd *curr, char *command)
{
	int		i;
	int		len;

	len = 0;
	while (command[len] && !is_seperator(command[len]))
		len++;
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (!curr->argv[curr->index])
		exit_shell("Cannot allocate memory");
	i = 0;
	while (*command && !is_seperator(*command))
	{
		curr->argv[curr->index][i] = *command;
		i++;
		command++;
	}
	curr->argv[curr->index][i] = '\0';
	curr->index++;
	return (i);
}

int			split_command(t_cmd *curr, char *command)
{
	int		i;

	i = 0;
	curr->index = 0;
	while (command[i] && !is_command_end(command[i]))
	{
		if (command[i] == S_QUOTE)
			i += handle_single_quote(curr, command + i);
		else if (command[i] == D_QUOTE)
			i += handle_double_quote(curr, command + i);
		else if (is_symbol(command[i]))
			i += handle_symbol(curr, command + i);
		else if (command[i] == '~')
			i += handle_symbol(curr, command + i);
		else
			i += push_arg(curr, command + i);
		while (command[i] && is_space(command[i]))
			i++;
	}
	curr->argv[curr->index] = NULL;
	return (i);
}

/*
void		add_command(t_cmd *curr)
{
	t_cmd	*tmp;

	tmp = curr;
	curr->next = malloc(sizeof(t_cmd));
	curr = curr->next;
	curr->prev = tmp;
}
*/

int			parse_command(char *command)
{
	int		i;
	t_cmd	*curr;
	t_cmd	*tmp;

	g_data.cmd_head->next = malloc(sizeof(t_cmd));
	curr = g_data.cmd_head->next;
	ft_memset(curr, 0, sizeof(t_cmd));
	curr->fd_out = 1;
	i = 0;
	while (command[i] != '\0')
	{
		command = ft_strtrim(command + i);
		curr->argc = count_words(command);
		curr->argv = malloc(sizeof(char *) * (curr->argc + 1));
		i = split_command(curr, command);
		if (command[i] == '|')
		{
			if (check_command_error(curr->argv, command, i))
				return (0);
			tmp = curr;
			curr->next = malloc(sizeof(t_cmd));
			curr = curr->next;
			ft_memset(curr, 0, sizeof(t_cmd));
			curr->prev = tmp;
			curr->fd_out = 1;
			i++;
		}
	}
	if (check_command_error(curr->argv, command, i))
		return (0);
	curr->next = NULL;
	return (1);
}
