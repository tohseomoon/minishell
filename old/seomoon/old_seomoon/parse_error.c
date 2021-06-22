/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:42:47 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/16 21:48:52 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			print_syntax_error(char *message)
{
	printf("bash: syntax error near unexpected token %s\n", message);
	//free_all();
	return (1);
}

int			check_redirection_error(char **argv)
{
	int		i;
	int		j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((ft_strcmp(argv[i][j], "<") == 0 ||
						ft_strcmp(argv[i][j], ">") == 0 ||
						ft_strcmp(argv[i][j], ">>") == 0) 
					&& argv[i][j + 1] == 0)
				return (print_syntax_error("`newline'"));
	}
	return (0);
}

int			check_pipe_error(char *command, int i)
{
	if (command[i + 1] == '|')
		return (print_syntax_error("`||'"));
	else if (i == 0 || command[i + 1] == 0)
		return (print_syntax_error("`|'"));
}

int			check_command_error(char **argv, char *command, int i)
{
	if (check_redirection_error(argv) || check_pipe_error(command, i))
		return (1);
	return (0);
}
