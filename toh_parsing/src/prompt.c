/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:11:51 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/30 14:13:17 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			clear_prompt(t_data *g)
{
	move_cursor(g);
	if (g->command)
		free(g->command);
	g->command = 0;
	g->h_flag = 0;
}

void			show_prompt(t_data *g)
{
	init_term(&g->term);
	while (1)
	{
		write(STDOUT_FILENO, "[minishell]$ ", 13);
		if (main_term(g) == 0)
		{
			reset_history(g);
			break ;
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g->term.save_term);
	save_history(&g_data);
}
