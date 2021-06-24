/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:42:47 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/23 22:18:49 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			handle_parse_error(int quote)
{
	if (quote == S_QUOTE)
		printf("minishell: single quotes not properly closed\n");
	else if (quote == D_QUOTE)
		printf("minishell: double quotes not properly closed\n");
	else if (quote == B_QUOTE)
		printf("minishell: back quotes not properly closed\n");
	return (-1);
}                          

int			handle_syntax_error(char *filename)
{
	if (filename == 0)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	else if (filename[0] == '#')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	else if (filename[0] == '&' || filename[0] == '|' || filename[0] == ';' ||
	filename[0] == '>' || filename[0] == '<')
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
		filename);
		return (1);
	}
	else if (filename[0] == '`')
	{
		printf("minishell: syntax error near unexpected token %s\n", filename);
		return (1);
	}
	return (0);
}

int			check_redirection_error(char **argv)
{
	int		i;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i])
	{
		if (!ft_strncmp(argv[i], ">>>>", 4))
			return (handle_syntax_error(">>"));
		else if (!ft_strncmp(argv[i], ">>>", 3))
			return (handle_syntax_error(">"));
		else if (!ft_strncmp(argv[i], "<<", 2) && ft_strlen(argv[i]) != 2)
			return (handle_syntax_error("<<"));
		if ((ft_strcmp(argv[i], "<") == 0 ||
				ft_strcmp(argv[i], ">") == 0 ||
				ft_strcmp(argv[i], ">>") == 0 ||
				ft_strcmp(argv[i], "<<") == 0)
			&& handle_syntax_error(argv[i + 1]))
		{
			g_data.return_value = 258;
			return (1);
		}
		i++;
	}
	return (0);
}

int			check_pipe_error(char *command, int i)
{
	i++;
	if (command[i] == 0)
		return (handle_syntax_error("`|'"));
	if (command[i] == ' ')
	{
		i++;
		while (is_space(command[i]))
			i++;
	}
	if (command[i] == 0)
		return (handle_syntax_error("`|'"));
	if (command[i] == '|' && command[i + 1] == '|')
		return (handle_syntax_error("`||'"));
	else if (command[i] == '|' && command[i - 1] == '|' )
		return (handle_syntax_error("`||'"));
	else if (command[i] == '|')
		return (handle_syntax_error("`|'"));
	else if (command[i] == ';' && command[i + 1] == ';')
		return (handle_syntax_error("`;;'"));
	else if (command[i] == ';')
		return (handle_syntax_error("`;'"));
	//else if (i == 0 || command[i + 1] == 0)
	//	return (handle_syntax_error("`|'"));
	//else if (!is_space(command[i - 1]) || !is_space(command[i + 1]))
	//	return (handle_syntax_error("`|'"));
	return (0);
}

int			check_semicolon_error(char *command, int i)
{
	i++;
	if (command[i] == 0)
		return (0);
	if (command[i] == ';')
		return (handle_syntax_error("`;;'"));
	if (command[i] == ' ')
	{
		while (is_space(command[i]))
			i++;
	}
	if (command[i] == ';' && command[i + 1] == ';')
		return (handle_syntax_error("`;;'"));
	else if (command[i] == ';')
		return (handle_syntax_error("`;'"));
	else if (command[i] == '|')
		return (handle_syntax_error("`|'"));
	return (0);
}

int			check_command_error(char **argv, char *command, int i)
{
	if (command[i] == 0)
		return (check_redirection_error(argv));
	if (command[i] == '|')
	{
		if (check_pipe_error(command, i))
		{
			g_data.return_value = 258;
			return (1);
		}
	}
	if (command[i] == ';')
	{
		if (check_semicolon_error(command, i))
		{
			g_data.return_value = 258;
			return (1);
		}
	}
	return (0);
}
