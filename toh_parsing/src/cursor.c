/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 08:38:45 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/29 11:09:39 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		ret;

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

void handle_keycode(t_data *g, int keycode)
{
	if (keycode == ARROW_UP)
		press_up(g);
	else if (keycode == ARROW_DOWN)
		press_down(g);
}