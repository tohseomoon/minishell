#include "minishell.h"

int				check_shell_builtin(t_cmd *curr)
{
	if (ft_strcmp("echo", curr->argv[0]) == 0)
		return (1);
	return (0);
}

static void		find_builtin_cmd(t_data *data, t_cmd *curr)
{
	if (ft_strcmp("echo", curr->argv[0]) == 0)
		echo(data, curr);
}

void			builtin_cmd(t_data *data, t_cmd *curr)
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
		close(curr->pipe[1]); // 파이프를 닫아야 같은 번호로 프로세스끼리 연결 됨
		waitpid(pid, &status, 0);
		// printf("status : %d\n", status); status값으로 자식 프로세스의 상태를 받는 것 같음
		// 에러 처리 할때 사용해야 할 수 있음
	}
}
