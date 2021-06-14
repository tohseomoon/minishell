#include "minishell.h"

void	heredoc(t_data *data, t_cmd *curr, int i, int fd)
{
	char	*line;
	int		tmp;

	write(1, "> ", 2);
	while (get_next_line(0, &line))
	{
		tmp = ft_strcmp(line, curr->argv[i + 1]);
		if (tmp == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		write(1, "> ", 2);
		free(line);
	}
	free(line);
	data->return_value = 0;
}

void			heredoc_cmd(t_data *data, t_cmd *curr, int i)
{
	pid_t	pid;
	int		status;
	
	pipe(curr->heredoc_pipe);
	curr->heredoc = 1;
	pid = fork();
	if (pid == 0)
	{
		heredoc(data, curr, i, curr->heredoc_pipe[1]);
		exit(data->return_value);
	}
	else
	{
		close(curr->heredoc_pipe[1]); // 파이프를 닫아야 같은 번호로 프로세스끼리 연결 됨
		waitpid(pid, &status, 0);
		// printf("status : %d\n", status); status값으로 자식 프로세스의 상태를 받는 것 같음
		// 에러 처리 할때 사용해야 할 수 있음
	}
}