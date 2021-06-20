/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:01:55 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/20 16:00:27 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			push_arg_quote(t_cmd *curr, char *command, char quote)
{
	int		i;
	int		len;

	len = 0;
	while (command[len] && command[len] != quote)
		len++;
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (!curr->argv[curr->index])
		exit_shell();
	i = 0;
	while (*command && *command != quote)
	{
		curr->argv[curr->index][i] = *command;
		i++;
		command++;
	}
	curr->argv[curr->index][i] = '\0';
	curr->index++;
	return (i);
}

int			handle_single_quote(t_cmd *curr, char *command)
{
	int		j;

	command++;
	j = 0;
	while (command[j] && command[j] != S_QUOTE)
		j += push_arg_quote(curr, command, S_QUOTE);
	if (command[j] != S_QUOTE)
		return (handle_parse_error(S_QUOTE));
	return (j + 2);
}

int			handle_double_quote(t_cmd *curr, char *command)
{
	int		i;

	command++;
	i = 0;
	while (command[i] && command[i] != D_QUOTE)
	{
		if (command[i] == ESCAPE)
		{
			i++;
			i += push_arg_quote(curr, command + i, D_QUOTE);
		}
		else if (is_symbol(command[i]))
			i += handle_symbol(curr, command + i);
		else
			i += push_arg_quote(curr, command + i, D_QUOTE);
	}
	if (command[i] != D_QUOTE)
		return (handle_parse_error(D_QUOTE));
	return (i + 2);
}
