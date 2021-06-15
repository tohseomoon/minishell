/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:42:47 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/15 20:00:33 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void		check_command_error(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == "<" || argv[i][j] == ">" || argv[i][j] == ">>")
			{
				if (!argv[i][j + 1])
					exit_shell("");
			}
			else if (argv[i][j] == '|')
			{
				
			}
		}
	}
}
