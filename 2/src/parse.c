/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:25:32 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/22 14:23:42 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		curr->argv[curr->index][j++] = command[i++];
	}
	curr->argv[curr->index][j] = '\0';
	curr->index++;
	return (i);
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

int					return_error(t_cmd *curr)
{
	curr->argv[curr->index] = NULL;
	return (0);
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
		init_argv(curr, command, i);
		result = split_command(curr, command + i);
		if (result < 0)
			return (return_error(curr));
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
