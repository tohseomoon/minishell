#include "minishell.h"

void	check_pipe(t_cmd *curr) // 현재 노드와 전, 후 노드를 확인하여 파이프 처리
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

void		execute_cmd_path(t_data *data, t_cmd *curr, char **envp) // 찾은 경로로 실행
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
		if (execve(curr->argv[0], curr->argv, envp) == -1)
		{
			printf("bash: %s: %s\n", curr->argv[0], strerror(errno));
			exit(1); 
		}
	}
	else
	{
		close(curr->pipe[1]); // 파이프를 닫아야 같은 번호로 프로세스끼리 연결 됨
		waitpid(pid, &status, 0);
		data->return_value = WEXITSTATUS(status);
	}
}

void	close_file(t_cmd *curr)
{
	if (curr->fd_in != 0)
		close(curr->fd_in);
	if (curr->fd_out != 1)
		close(curr->fd_out);
	if (curr->prev != 0)
		close(curr->prev->pipe[0]); // 전 명령어의 pipe_in은 사용이 끝남
}


void	execute(t_data *data, char **envp) //실행부분 메인 함수
{
	//에러 명령어 경우 구조체에 정보가 없다고 가정 // 혹은 flag?
	t_cmd	*curr;
	int		i;

	curr = data->cmd_head->next;
	while (curr)
	{
		if (curr->next != 0)
			pipe(curr->pipe);
		if ((i = redirection_open_file(curr)) > 0)
			printf("bash: %s: No such file or directory\n", curr->argv[i + 1]);
			  //리다이렉션 체크 후 파일 열기
		else if (check_shell_builtin(curr)) // 쉘 빌트인 확인
			builtin_cmd(data, curr);
		else if (curr->argv[0][0] == '/')
		{
			if (find_cmd_absolute_path(data, curr))
				execute_cmd_path(data, curr, envp);// 실행하기
		}
		else if(find_cmd_path(data, curr))
			execute_cmd_path(data, curr, envp);	 
		else
			printf("bash : %s: command not found\n", curr->argv[0]);
		close_file(curr);
		curr = curr->next;
	}
}

int		main(int argc, char **argv, char **envp) // 일단 돌리기 위해
{
	t_data	data;
	
	ft_memset(&data, 0, sizeof(t_data));
	data.env_head = (t_env *)malloc(sizeof(t_env));
	parse_env(data.env_head, envp);
	setting_cmd(&data);
	print_cmd(&data);
	data.path = parse_path(&data);
	execute(&data, envp);
	print_cmd(&data);
	free_data(&data);
}
