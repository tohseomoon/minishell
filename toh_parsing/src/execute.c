/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:01:17 by toh               #+#    #+#             */
/*   Updated: 2021/06/28 13:03:27 by toh              ###   ########.fr       */
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

static void		execute_cmd_path(t_cmd *curr, char **envp)
{
	pid_t	pid;
	int		status;

	g_data.running = 1;
	pid = fork();
	if (pid == 0)
	{
		check_pipe(curr);
		if (execve(curr->argv[0], curr->argv, envp) == -1)
		{
			printf("minishell: %s: %s\n", curr->argv[0], strerror(errno));
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		close(curr->pipe[1]);
		if (WIFEXITED(status))
			g_data.return_value = WEXITSTATUS(status);
		if (curr->heredoc == 1)
			curr->heredoc = 0;
		g_data.running = 0;
	}
}

static void		close_file(t_cmd *curr)
{
	if (curr->fd_in != 0)
		close(curr->fd_in);
	if (curr->fd_out != 1)
		close(curr->fd_out);
	if (curr->next == 0)
	{
		while (curr)
		{
			close(curr->pipe[0]);
			close(curr->pipe[1]);
			if (curr->heredoc_pipe[0] != 0)
				close(curr->heredoc_pipe[0]);
			if (curr->heredoc_pipe[1] != 0)
				close(curr->heredoc_pipe[1]);
			curr = curr->prev;
		}
	}
}

static void		check_commad(t_cmd *curr, char **envp, int i)
{
	i = 0;
	if ((i = redirection_open_file(curr)) > 0)
	{
		printf("minishell: %s: %s\n", curr->argv[i], strerror(errno));
		if (errno == 13)
			g_data.return_value = 126;
		else if (errno == 2)
			g_data.return_value = 1;
	}
	else if (curr->argc == 0)
		return ;
	else if (check_shell_builtin(curr))
		builtin_cmd(curr);
	else if (check_shell_builtin_fork(curr))
		builtin_cmd_fork(curr);
	else if (curr->argv[0][0] == '/' || curr->argv[0][0] == '.')
	{
		if (find_cmd_absolute_path(curr))
			execute_cmd_path(curr, envp);
	}
	else if (find_cmd_path(curr))
		execute_cmd_path(curr, envp);
	else
	{
		printf("minishell: %s: command not found\n", curr->argv[0]);
		g_data.return_value = 127;
	}
}

void			execute_command(char **envp)
{
	t_cmd	*curr;
	int		i;

	curr = g_data.cmd_head->next;
	i = 0;
	while (curr)
	{
		pipe(curr->pipe);
		check_commad(curr, envp, i);
		close_file(curr);
		curr = curr->next;
	}
}
