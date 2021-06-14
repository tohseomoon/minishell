#include "minishell.h"

int				check_shell_builtin_fork(t_cmd *curr)
{
	if (ft_strcmp("echo", curr->argv[0]) == 0)
		return (1);
	else if (ft_strcmp("env", curr->argv[0]) == 0)
		return (1);
	return (0);
}

int				check_shell_builtin(t_cmd *curr)
{
	if (ft_strcmp("exit", curr->argv[0]) == 0)
		return (1);
	return (0);
}

static void		find_builtin_cmd(t_data *data, t_cmd *curr)
{
	if (ft_strcmp("echo", curr->argv[0]) == 0)
		echo(data, curr);
	else if (ft_strcmp("env", curr->argv[0]) == 0)
		env(data);
}

void			builtin_cmd_fork(t_data *data, t_cmd *curr)
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
		find_builtin_cmd(data, curr);
		exit(data->return_value);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(curr->pipe[1]); // 파이프를 닫아야 받을 수 있음 EOF가 전송된다.
	}
}

void			builtin_cmd(t_data *data, t_cmd *curr)
{
	if (ft_strcmp("exit", curr->argv[0]) == 0)
		ft_exit(data, curr);
}