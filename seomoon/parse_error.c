/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:42:47 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/17 01:36:23 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			print_syntax_error(char *message)
{
	printf("bash: syntax error near unexpected token %s\n", message);
	g_data.return_value = 258;
	//free_all();
	return (1);
}

int			check_redirection_error(char **argv)
{
	int		i;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i])
	{
		if ((ft_strcmp(argv[i], "<") == 0 ||
					ft_strcmp(argv[i], ">") == 0 ||
					ft_strcmp(argv[i], ">>") == 0 ||
					ft_strcmp(argv[i], "<<") == 0)
				&& argv[i + 1] == 0)
			return (print_syntax_error("`newline'"));
		i++;
	}
	return (0);
}

int			check_pipe_error(char *command, int i)
{
	if (command[i + 1] == '|')
		return (print_syntax_error("`||'"));
	else if (i == 0 || command[i + 1] == 0)
		return (print_syntax_error("`|'"));
	return (0);
}

int			check_command_error(char **argv, char *command, int i)
{
	if (command[i] == 0)
		return (check_redirection_error(argv));
	else if (command[i] == '|')
	{
		if (check_redirection_error(argv) || check_pipe_error(command, i))
			return (1);
	}
	return (0);
}
