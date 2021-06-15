/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:01:55 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/15 14:32:38 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			push_arg_quote(t_cmd *curr, char *command, char quote)
{
	int		i;
	int		len;

	len = 0;
	while (command[len] && command[len] != quote)
		len++;
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (!curr->argv[curr->index])
		exit_shell("push_arg_quote(): Fail to allocate. ");
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
		exit_shell("Single quote not closed. ");
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
		exit_shell("Double quote not closed. ");
	return (i + 2);
}
