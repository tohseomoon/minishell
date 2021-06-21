/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:01:55 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/21 16:46:19 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					check_remain_character(t_cmd *curr, char *command)
{
	int				i;
	int				len;
	char			*remain_str;

	i = 0;
	if (command[i] == 0 || is_space(command[i]))
	{
		curr->index++;
		return (i);
	}
	len = 0;
	while (command[len] && !is_space(command[len]))
		len++;
	remain_str = malloc(sizeof(char) * (len + 1));
	if (!remain_str)
		exit_shell();
	while (i < len)
	{
		remain_str[i] = command[i];
		i++;
	}
	remain_str[i] = '\0';
	printf("%s\n", remain_str);
	curr->argv[curr->index] = ft_strjoin_free_s1(&(curr->argv[curr->index]), remain_str);
	curr->index++;
	return (i);
}

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
	while (command[i] && command[i] != quote)
	{
		curr->argv[curr->index][i] = command[i];
		i++;
	}
	curr->argv[curr->index][i] = '\0';
	return (i);
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
		curr->argv[curr->index] = ft_strdup("");
	return (i + 2);
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
		curr->argv[curr->index] = ft_strdup("");
	return (i + 2);
}

int			handle_quote(t_cmd *curr, char *command, int i)
{
	int		result;

	result = 0;
	if (command[i] == S_QUOTE)
	{
		result = handle_single_quote(curr, command + i);
		if (result < 0)
			return (result);
	}
	else if (command[i] == D_QUOTE)
	{
		result = handle_double_quote(curr, command + i);
		if (result < 0)
			return (result);
	}
	result += check_remain_character(curr, command + i + result);
	return (result);
}
