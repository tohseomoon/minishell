/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:42:47 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/16 17:56:36 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_error(int type, char *message)
{
	if (type == SYNTAX_ERROR)
		printf("bash: syntax error near unexpected token %s\n", message);
	free_all();

}

int			check_command_error(char **argv)
{
	int		i;
	int		type;

	i = 0;
	type = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((ft_strcmp(argv[i][j], "<") == 0 ||
						ft_strcmp(argv[i][j], ">") == 0 ||
						ft_strcmp(argv[i][j], ">>") == 0) 
					&& argv[i][j + 1] == 0)
				print_error("`newline'", SYNTAX_ERROR);
			else if (ft_strcmp(argv[i][j], "|") && argv[i][j + 1] == 0)
				print_error("`|'", SYNTAX_ERROR);
			else if (ft_strcmp(argv[i][j], "||") && argv[i][j + 1] == 0)
				print_error("`||'", SYNTAX_ERROR);
			else if (ft_strcmp(
	}
	return (type);
}
