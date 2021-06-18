#include "minishell.h"

static void		find_builtin_cmd(t_cmd *curr)
{
	if (ft_strcmp("echo", curr->argv[0]) == 0)
		ft_echo(curr);
	else if (ft_strcmp("env", curr->argv[0]) == 0)
		ft_env();
	else if (ft_strcmp("pwd", curr->argv[0]) == 0)
		ft_pwd();
		else if (ft_strcmp("export", curr->argv[0]) == 0)
		ft_export_fork(curr);
}

void			builtin_cmd_fork(t_cmd *curr)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		check_pipe(curr);
		if (curr->fd_in != 0)
			dup2(curr->fd_in, 0);
		if (curr->fd_out != 1)
			dup2(curr->fd_out, 1);
		find_builtin_cmd(curr);
		exit(g_data.return_value);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(curr->pipe[1]);
	}
}