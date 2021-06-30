/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 12:55:20 by toh               #+#    #+#             */
/*   Updated: 2021/06/30 12:59:26 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			check_pipe(t_cmd *curr)
{
	if (curr->heredoc == 1)
	{
		dup2(curr->heredoc_pipe[0], 0);
		if (curr->next != 0 && curr->prev == 0)
			dup2(curr->pipe[1], 1);
	}
	else if (curr->type == 1)
	{
		if (curr->prev == 0)
			dup2(curr->pipe[1], 1);
		else if (curr->prev->type == 0 && curr->next != 0)
			dup2(curr->pipe[1], 1);
		else if (curr->next != 0 && curr->prev != 0 && curr->prev->type == 1)
		{
			dup2(curr->prev->pipe[0], 0);
			dup2(curr->pipe[1], 1);
		}
	}
	else if (curr->prev != 0 && curr->prev->type == 1)
		dup2(curr->prev->pipe[0], 0);
	if (curr->fd_in != 0 && curr->heredoc != 1)
		dup2(curr->fd_in, 0);
	if (curr->fd_out != 1)
		dup2(curr->fd_out, 1);
}
