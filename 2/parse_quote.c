/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:01:55 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/20 20:30:54 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			push_arg_quote(t_cmd *curr, char *command, char quote)
{
	int		i;
	int		len;

	len = 0;
	while (command[len] && !is_command_end(command[len]) && !is_space(command[len]))
		len++;
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (!curr->argv[curr->index])
		exit_shell();
	i = 0;
	while (*command && *command != quote)
	{
		/*
		while (*command == ESCAPE && (*(command + 1) == ESCAPE || is_symbol(*(command + 1))))
			command++;
		*/
		curr->argv[curr->index][i] = *command;
		i++;
		command++;
	}
	if (*command == quote && *(command + 1))
	{
		while (*command)
		{
			curr->argv[curr->index][i] = *command;
			i++;
			command++;
		}
	}
	curr->argv[curr->index][i] = '\0';
	curr->index++;
	return (i);
}

int			handle_single_quote(t_cmd *curr, char *command)
{
	int		i;

	command++;
	i = 0;
	while (command[i] && command[i] != S_QUOTE)
		i += push_arg_quote(curr, command, S_QUOTE);
	if (command[i] != S_QUOTE)
		return (handle_parse_error(S_QUOTE));
	if (i == 0)
		i += push_arg_quote(curr, command, S_QUOTE);
	return (i + 2);
}

int			handle_escape(t_cmd *curr, char *command, int quote)
{
	int		i;

	i = 0;
	if (command[i + 1] == ESCAPE || is_symbol(command[i + 1]))
	{
		i++;
		if (quote)
			i += push_arg_quote(curr, command + i, quote);
		else
			i += push_arg(curr, command + i);
	}
	else
	{
		if (quote)
			i += push_arg_quote(curr, command + i, quote);
		else
			i += push_arg(curr, command + i);
	}
	return (i);
}

int			handle_double_quote(t_cmd *curr, char *command)
{
	int		i;

	command++;
	i = 0;
	while (command[i] && command[i] != D_QUOTE)
	{
		if (command[i] == ESCAPE)
			i += handle_escape(curr, command + i, D_QUOTE);
		else if (is_symbol(command[i]))
			i += handle_symbol(curr, command + i);
		else
			i += push_arg_quote(curr, command + i, D_QUOTE);
	}
	if (command[i] != D_QUOTE)
		return (handle_parse_error(D_QUOTE));
	if (i == 0)
		i += push_arg_quote(curr, command, D_QUOTE);
	return (i + 2);
}
