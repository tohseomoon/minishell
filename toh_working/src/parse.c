/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:25:32 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/24 16:10:41 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					is_continuous_quotes(char *command, int *i)
{	

	while (!(command[*i] != D_QUOTE && command[*i] != S_QUOTE)) 
	{
		if (ft_strlen(command + *i) >= 2)
		{
			if ((command[*i] == D_QUOTE) && (command[*i + 1] == D_QUOTE))
				(*i) += 2;
			else if ((command[*i] == S_QUOTE) && (command[*i + 1] == S_QUOTE))
				(*i) += 2;
			else
				break ;
		}
		else
			break ;
	}
}	

int					push_arg(t_cmd *curr, char *command)
{
	int				i;
	int				j;
	int				len;

	len = 0;
	while (command[len] && !is_space(command[len]))
	{
		is_continuous_quotes(command, &len);
		if (is_seperator(command[len]))
			break ;
		len++;
	}
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (!curr->argv[curr->index])
		exit_shell();
	i = 0;
	j = 0;
	//아래
	while (command[i] && !is_space(command[i]))
	{
		if (command[i] == '|' || command[i] == ';')
			break ;
		is_continuous_quotes(command, &i);
		if (is_seperator(command[i]))
			break ;
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
//			if (i != 0 &&!is_space(command[i - 1]))
//				free(curr->argv[curr->index]);
			printf("1\n");
			result = handle_operator(curr, command, i);
			if (result < 0)
			{
				//curr->argv[curr->index - 1] = NULL;
				return (result);
			}
			i += result;

		}
		else
		{
//			if (i != 0 &&!is_space(command[i - 1]))
//				free(curr->argv[curr->index]);
			printf("2\n");
			result = push_arg(curr, command + i);
			if (result < 0)
			{
				//curr->argv[curr->index - 1] = NULL;
				return (result);
			}
			i += result;
		}
	}
	curr->argv[curr->index] = NULL;
	return (i);
}

int					return_error(t_cmd *curr)
{
	if (curr->argc < curr->index)
	{
		curr->index--;
		free(curr->argv[curr->index]);
	}
	curr->argv[curr->index] = NULL;
	return (0);
}

int					init_error(t_cmd *curr)
{
	curr->argv[curr->index] = NULL;
	return (0);
}

int					parse_command(char *command, t_cmd *curr)
{
	int				i;
	int				result;

	i = 0;
	while (command[i] != '\0')
	{
		if (init_argv(curr, command, i) == 0)
			return (init_error(curr));
		result = split_command(curr, command + i);
		if (result < 0)
			return (return_error(curr));
		i += result;
		if (command[i] == '|' || command[i] == ';')
		{
			if (command[i] == '|')
				curr->type = 1;
			if (check_command_error(curr->argv, command, i))
				return (0);
			if (command[i] == 0 || command[i + 1] == 0)
				break ;
			add_new_cmd(curr);
			curr = curr->next;
			i++;
		}
	}
	if (check_command_error(curr->argv, command, i))
		return (0);
	return (1);
}
