/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:01:55 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/24 16:22:29 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					check_remain_character(t_cmd *curr, char *command)
{
	int				i;
	int				len;
	char			*remain_str;

	i = 0;
	if (curr->continuous == 1 && command[i] == 0 || is_space(command[i]) || command[i] == ';')
	{
		if (curr->index != curr->argc)
			curr->index++;
		return (i);
	}
	len = get_command_len(command);
	remain_str = malloc(sizeof(char) * (len + 1));
	if (!remain_str)
		exit_shell();
	while (i < len)
	{
		remain_str[i] = command[i];
		i++;
	}
	remain_str[i] = '\0';
	curr->argv[curr->index] =
		ft_strjoin_free_s1(&(curr->argv[curr->index]), remain_str);
	free(remain_str);
	curr->index++;
	return (i);
}

static int			push_arg_quote(t_cmd *curr, char *command, char quote)
{
	int				i;
	int				j;
	int				len;

	len = 0;
	while (command[len] && command[len] != quote)
		len++;
	if (curr->continuous == 1)
		free(curr->argv[curr->index]);
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (!curr->argv[curr->index])
		exit_shell();
	i = 0;
	j = 0;
	while (command[i] && command[i] != quote)
	{
		if (command[i] == ESCAPE)
			i++;
		curr->argv[curr->index][j] = command[i];
		j++;
		i++;
	}
	curr->argv[curr->index][j] = '\0';
	return (i);
}

int					handle_single_quote(t_cmd *curr, char *command)
{
	int				i;

	command++;
	i = 0;
	while (command[i] && command[i] != S_QUOTE)
		i += push_arg_quote(curr, command, S_QUOTE);
	if (i == 0 && curr->continuous == 0)
	{
		curr->continuous = 1;
		//if (curr->argv[curr->index] == 0)
		curr->argv[curr->index] = ft_strdup("");
	}
	if (command[i] != S_QUOTE)
		return (handle_parse_error(S_QUOTE));
	return (i + 2);
}

int					handle_double_quote(t_cmd *curr, char *command)
{
	int				i;

	command++;
	i = 0;
	while (command[i] && command[i] != D_QUOTE)
	{
		if (is_symbol(command[i]))
			i += handle_symbol(curr, command + i);
		else
			i += push_arg_quote(curr, command + i, D_QUOTE);
	}
	if (i == 0 && curr->continuous == 0)
	{
		curr->continuous = 1;
		//if (curr->argv[curr->index] == 0)
		curr->argv[curr->index] = ft_strdup("");
	}
	if (command[i] != D_QUOTE)
		return (handle_parse_error(D_QUOTE));
	return (i + 2);
}

int					handle_quote(t_cmd *curr, char *command, int i)
{
	int				result;

	result = 0;
	printf("%s\n", command + i);
	if (command[i] == S_QUOTE)
	{
		result = handle_single_quote(curr, command + i);
		if (result < 0)
		{
			curr->index++;
			return (result);
		}
		if (command[i + result] != 0 && !is_seperator(command[i + result]))
			result += check_remain_character(curr, command + i + result);
	}
	else if (command[i] == D_QUOTE)
	{
		result = handle_double_quote(curr, command + i);
		if (result < 0)
		{
			curr->index++;
			return (result);
		}
		if (command[i + result] != 0 && !is_seperator(command[i + result]))
			result += check_remain_character(curr, command + i + result);
	}
	if (command[i + result] == 0)
		result += check_remain_character(curr, command + i + result);
	printf("resul %d\n", result);
	return (result);
}
