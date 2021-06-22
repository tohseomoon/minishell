/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 12:54:30 by toh               #+#    #+#             */
/*   Updated: 2021/06/16 15:53:54 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_echo_argv(t_cmd *curr, int n_flag, int i)
{
	while (curr->argv[i])
	{
		write(1, curr->argv[i], ft_strlen(curr->argv[i]));
		if (curr->argv[i + 1] != 0)
			write(1, " ", 1);
		i++;
	}
}

static int		check_flag(char **argv, int *n_flag)
{
	int		i;
	int		j;

	i = 1;
	while (argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] != 'n')
				return (i);
			j++;
		}
		*n_flag = 1;
		i++;
		if (argv[i] == 0)
			return (-1);
	}
	return (i);
}

void			ft_echo(t_cmd *curr)
{
	int		n_flag;
	int		i;

	n_flag = 0;
	if (curr->argc == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	i = check_flag(curr->argv, &n_flag);
	if (i != -1)
		print_echo_argv(curr, n_flag, i);
	if (n_flag == 0)
		write(1, "\n", 1);
	g_data.return_value = 0;
}
