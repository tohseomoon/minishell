/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 06:31:28 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/29 11:02:18 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_term(t_term *term)
{
	// set term
	tcgetattr(STDIN_FILENO, &term->new_term);
	term->new_term.c_lflag &= ~ICANON;
	term->new_term.c_lflag &= ~ECHO;
	term->new_term.c_cc[VMIN] = 1;
	term->new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term->new_term);

	// init termcap
	tgetent(NULL, "xterm");
	term->cm = tgetstr("cm", NULL);
	term->ce = tgetstr("ce", NULL);
}

int				main_term(t_data *g)
{
	int			keycode;

	set_cursor(&g->curr.col, &g->curr.row);
	keycode = 0;
	while (read(STDIN_FILENO, &keycode, sizeof(int)) > 0)
	{
		handle_keycode(g, keycode);
		keycode = 0;
	}
	return (0);
}
