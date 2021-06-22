/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:44:26 by toh               #+#    #+#             */
/*   Updated: 2021/06/20 15:43:40 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_cmd *curr, int i, int fd)
{
	char	*line;
	int		tmp;

	while ((line = readline("> ")))
	{
		tmp = ft_strcmp(line, curr->argv[i + 1]);
		if (tmp == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	g_data.return_value = 0;
}

void	heredoc_cmd(t_cmd *curr, int i)
{
	pid_t	pid;
	int		status;

	pipe(curr->heredoc_pipe);
	curr->heredoc = 1;
	pid = fork();
	if (pid == 0)
	{
		heredoc(curr, i, curr->heredoc_pipe[1]);
		exit(g_data.return_value);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(curr->heredoc_pipe[1]);
	}
}
