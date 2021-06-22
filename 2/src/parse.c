/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:25:32 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/22 12:49:25 by seomoon          ###   ########.fr       */
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
				(is_space(str[i + 1]) || is_command_end(str[i + 1])))
			count++;
		i++;
	}
	return (count);
}

int					push_arg(t_cmd *curr, char *command)
{
	int				i;
	int				j;
	int				len;

	len = 0;
	while (command[len] && !is_seperator(command[len]))
		len++;
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (!curr->argv[curr->index])
		exit_shell();
	i = 0;
	j = 0;
	while (command[i] && !is_space(command[i]))
	{
		if (command[i] == '|')
		{
			handle_syntax_error("`|'");
			return (-1);
		}
		curr->argv[curr->index][j] = command[i];
		i++;
		j++;
	}
	curr->argv[curr->index][j] = '\0';
	curr->index++;
	return (i);
}

int					is_operator(char c)
{
	if (c == S_QUOTE || c == D_QUOTE || is_symbol(c) || c == '~')
		return (1);
	return (0);
}

int					handle_operator(t_cmd *curr, char *command, int i)
{
	int				result;

	result = 0;
	if (command[i] == S_QUOTE || command[i] == D_QUOTE)
		result = handle_quote(curr, command, i);
	else if (is_symbol(command[i]) || command[i] == '~')
		result = handle_symbol(curr, command + i);
	return (result);
}

static int			split_command(t_cmd *curr, char *command)
{
	int				i;
	int				result;

	i = 0;
	curr->index = 0;
	while (command[i] && !is_command_end(command[i]))
	{
		if (is_space(command[i]))
			i++;
		else if (is_operator(command[i]))
		{
			result = handle_operator(curr, command, i);
			if (result < 0)
				return (result);
			i += result;
		}
		else
		{
			result = push_arg(curr, command + i);
			if (result < 0)
				return (result);
			i += result;
		}
	}
	curr->argv[curr->index] = NULL;
	return (i);
}

void				add_new_cmd(t_cmd *curr)
{
	t_cmd			*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_shell();
	ft_memset(new, 0, sizeof(t_cmd));
	new->prev = curr;
	new->fd_out = 1;
	curr->next = new;
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
	int				result;
	t_cmd			*curr;

	curr = init_cmd();
	i = 0;
	while (command[i] != '\0')
	{
		curr->argc = count_words(command + i);
		curr->argv = malloc(sizeof(char *) * (curr->argc + 1));
		if (!curr->argv)
			exit_shell();
		result = split_command(curr, command + i);
		if (result < 0)
		{
			curr->argv[curr->index] = NULL;
			return (0);
		}
		i += result;
		if (command[i] == '|')
		{
			if (check_command_error(curr->argv, command, i))
				return (0);
			add_new_cmd(curr);
			curr = curr->next;
			i++;
		}
	}
	if (check_command_error(curr->argv, command, i))
		return (0);
	return (1);
}
