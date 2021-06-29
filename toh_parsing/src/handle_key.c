/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 08:21:25 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/29 12:26:37 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			move_cursor(t_data *g)
{
	t_pos		pos;
	int			len;

	if (g->command != 0)
		len = ft_strlen(g->command);
	else
		len = 0;
	set_cursor(&pos.col, &pos.row);
	pos.col -= len;
	if (pos.col < 0)
	{
		pos.row--;
		pos.col = g->max.col + pos.col;
	}
	tputs(tgoto(g->term.cm, pos.col, pos.row), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
}

void			press_up(t_data *g)
{
	if (!g->h_head)
		return ;
	if (g->command != 0 && g->h_flag == 0)
		g->h_head = push_front_history(g->command, g->h_head, 0);
	if ((g->h_head->next != 0 && g->h_flag != 0) || g->h_head->flag == 0)
		g->h_head = g->h_head->next;
	g->h_flag = 1;
	move_cursor(g);
	write(1, g->h_head->command, ft_strlen(g->h_head->command));
	if (g->command)
		free(g->command);
	g->command = ft_strdup(g->h_head->command);
}

void			clear_prompt(t_data *g)
{
	move_cursor(g);
	if (g->command)
		free(g->command);
	g->command = 0;
	g->h_flag = 0;
}

void			press_down(t_data *g)
{
	if (g->h_head == 0 || (g->h_head->prev == 0
			&& g->h_head->flag == 0))
		return ;
	if (g->h_head->prev == 0)
		clear_prompt(g);
	else
	{
		g->h_head = g->h_head->prev;
		move_cursor(g);
		if (g->command)
			free(g->command);
		g->command = 0;
		write(1, g->h_head->command, ft_strlen(g->h_head->command));
		g->command = ft_strdup(g->h_head->command);
	}
}
