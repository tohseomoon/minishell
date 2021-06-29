/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 08:38:45 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/29 12:51:58 by seomoon          ###   ########.fr       */
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

int			ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}

char		*add_char_to_str(char *str, char c)
{
	int		i;
	char	*result;

	if (!str)
	{
		result = malloc(sizeof(char) * 2);
		result[0] = c;
		result[1] = '\0';
	}
	else
	{
		result = malloc(sizeof(char) * (ft_strlen(str) + 2));
		if (!result)
			return (NULL);
		i = 0;
		while (str[i])
		{
			result[i] = str[i];
			i++;
		}
		result[i++] = c;
		result[i] = '\0';
		free(str);
	}
	return (result);
}

void		handle_keycode(t_data *g, int keycode)
{
	if (keycode == ARROW_UP)
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
