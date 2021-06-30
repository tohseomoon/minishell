/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:16:18 by toh               #+#    #+#             */
/*   Updated: 2021/06/30 13:37:05 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_data.running == 1)
		{
			write(1, "\n", 1);
			g_data.return_value = 130;
		}
		else
		{
			write(1, "\n[minishell]$ ", 14);
			if (g_data.command)
				free(g_data.command);
			g_data.command = 0;
			g_data.return_value = 1;
		}
	}
	else if (signo == SIGQUIT)
	{
		if (g_data.running == 1)
		{
			write(1, "Quit: 3\n", 9);
			g_data.return_value = 131;
		}
	}
}
