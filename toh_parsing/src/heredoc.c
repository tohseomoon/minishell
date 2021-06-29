/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:44:26 by toh               #+#    #+#             */
/*   Updated: 2021/06/29 17:57:22 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_cmd *curr, int i, int fd)
{
	char	*line;

	write(1, "> ", 2);
	while (get_next_line(0, &line))
	{
		if (ft_strcmp(line, curr->argv[i + 1]) == 0)
			break ;
		write(1, "> ", 2);
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
