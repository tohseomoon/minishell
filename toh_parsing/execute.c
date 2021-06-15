/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:01:17 by toh               #+#    #+#             */
/*   Updated: 2021/06/15 14:42:45 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		check_pipe(t_cmd *curr)
{
	if (curr->heredoc == 1)
	{
		dup2(curr->heredoc_pipe[0], 0);
		if (curr->next != 0 && curr->prev == 0)
			dup2(curr->pipe[1], 1);
	}
	else
	{
		if (curr->next != 0 && curr->prev == 0)
			dup2(curr->pipe[1], 1);
		else if (curr->next != 0 && curr->prev != 0)
		{
			dup2(curr->prev->pipe[0], 0);
			dup2(curr->pipe[1], 1);
		}
		else if (curr->prev != 0 && curr->next == 0)
			dup2(curr->prev->pipe[0], 0);
	}
}

void		execute_cmd_path(t_cmd *curr, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		check_pipe(curr);
		if (curr->fd_in != 0 && curr->heredoc != 1)
			dup2(curr->fd_in, 0);
		if (curr->fd_out != 1)
			dup2(curr->fd_out, 1);
		if (execve(curr->argv[0], curr->argv, envp) == -1)
		{
			printf("bash: %s: %s\n", curr->argv[0], strerror(errno));
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		close(curr->pipe[1]);
		g_data.return_value = WEXITSTATUS(status);
		if (curr->heredoc == 1)
		{
			curr->heredoc = 0;
			close(curr->heredoc_pipe[0]);
		}
	}
}

void		close_file(t_cmd *curr)
{
	if (curr->fd_in != 0)
		close(curr->fd_in);
	if (curr->fd_out != 1)
		close(curr->fd_out);
	if (curr->prev != 0)
		close(curr->prev->pipe[0]);
}

void	execute(char **envp)
{
	t_cmd	*curr;
	int		i;

	curr = g_data.cmd_head->next;
	while (curr)
	{
		pipe(curr->pipe);
		if ((i = redirection_open_file(curr)) > 0)
			printf("bash: %s: No such file or directory\n", curr->argv[i + 1]);
		else if (check_shell_builtin_fork(curr))
			builtin_cmd_fork(curr);
		else if (check_shell_builtin(curr))
			builtin_cmd(curr);
		else if (curr->argv[0][0] == '/')
		{
			if (find_cmd_absolute_path(curr))
				execute_cmd_path(curr, envp);
		}
		else if (find_cmd_path(curr))
			execute_cmd_path(curr, envp);
		else
			printf("bash : %s: command not found\n", curr->argv[0]);
		close_file(curr);
		curr = curr->next;
	}
}

int			main(int argc, char **argv, char **envp)
{
	ft_memset(&g_data, 0, sizeof(t_data));
	g_data.env_head = (t_env *)malloc(sizeof(t_env));
	parse_env(g_data.env_head, envp);
	setting_cmd();
	//print_cmd();
	g_data.path = parse_path();
	g_data.old_env = arr_env_string();
	execute(envp);
	//print_cmd();
	free_data();
	//while(1);
}
