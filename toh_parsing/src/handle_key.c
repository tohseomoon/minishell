/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 08:21:25 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/30 14:12:58 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			press_backspace(t_data *g)
{
	int			col;
	int			row;

	set_cursor(&col, &row);
	if (!g->command || (g->start.row >= row && g->start.col >= col))
		return ;
	col--;
	if (col < 0)
	{
		row--;
		col = g->max.col;
	}
	tputs(tgoto(g->term.cm, col, row), 1, ft_putchar);
	tputs(g->term.ce, 1, ft_putchar);
	g->command = remove_last_char(g->command);
}

void			press_eof(t_data *g)
{
	if (!g->command)
	{
		printf("exit\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &g->term.save_term);
		exit(0);
	}
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

void			handle_keycode(t_data *g, int keycode)
{
	if (keycode == BACKSPACE)
		press_backspace(g);
	else if (keycode == CTRL_D)
		press_eof(g);
	else if (keycode == ARROW_UP)
		press_up(g);
	else if (keycode == ARROW_DOWN)
		press_down(g);
	else
	{
		if (ft_isprint(keycode))
		{
			g->command = add_char_to_str(g->command, (char)keycode);
			write(STDOUT_FILENO, &keycode, 1);
		}
	}
}
