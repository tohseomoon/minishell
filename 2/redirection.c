/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:11:32 by toh               #+#    #+#             */
/*   Updated: 2021/06/18 16:06:34 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		left_redirection(t_cmd *curr, int i)
{
	if (curr->argv[i][1] == 0)
	{
		curr->fd_in = open(curr->argv[i + 1], O_RDONLY);
		curr->heredoc = 0;
	}
	else if (curr->argv[i][1] == '<')
		heredoc_cmd(curr, i);
}

static void		right_redirection(t_cmd *curr, int i)
{
	if (curr->argv[i][1] == 0)
		curr->fd_out = open(curr->argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (curr->argv[i][1] == '>')
		curr->fd_out = open(curr->argv[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
}

int				redirection_open_file(t_cmd *curr)
{
	int		i;

	i = 0;
	while (curr->argv[i])
	{
		if (curr->argv[i][0] == '<')
			left_redirection(curr, i);
		else if (curr->argv[i][0] == '>')
			right_redirection(curr, i);
		if (curr->fd_out < 0 || curr->fd_in < 0)
			return (i);
		i++;
	}
	del_redirections(curr);
	return (0);
}