/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 08:38:45 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/30 14:15:08 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		move_cursor(t_data *g)
{
	t_pos	pos;
	int		len;

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

int			get_nbr_len(int n)
{
	int		len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void		get_current_cursor(char buff[255])
{
	int			ret;

	write(STDIN_FILENO, "\033[6n", 4);
	ret = read(STDIN_FILENO, buff, 254);
	if (ret < 0)
		ret = 0;
	buff[ret] = '\0';
}

void		set_cursor(int *col, int *row)
{
	int		i;
	int		flag;
	char	buff[255];
	int		ret;

	get_current_cursor(buff);
	i = 0;
	flag = ROW;
	while (buff[i++])
	{
		if (ft_isdigit(buff[i]))
		{
			if (flag == ROW)
				*row = ft_atoi(&buff[i]) - 1;
			else
			{
				*col = ft_atoi(&buff[i]) - 1;
				break ;
			}
			flag = COL;
			i += get_nbr_len(*row) - 1;
		}
	}
}

void		init_cursor(t_data *g)
{
	struct winsize	win;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	g->max.col = win.ws_col;
	g->max.row = win.ws_row;
	set_cursor(&g->start.col, &g->start.row);
}
