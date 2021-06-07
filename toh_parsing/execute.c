#include "../minishell.h"
#include <fcntl.h>
#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	setting_cmd(t_data *data)
{
	data->cmd_head = (t_cmd *)malloc(sizeof(t_cmd));
	data->cmd_head->next = (t_cmd *)malloc(sizeof(t_cmd));
	data->cmd_head->next->argc = 1;
	data->cmd_head->next->argv = (char **)malloc(sizeof(char *) * 5);
	data->cmd_head->next->argv[0] = ft_strdup("ls");
	data->cmd_head->next->argv[1] = ft_strdup("-la");
	data->cmd_head->next->argv[2] = 0;
	data->cmd_head->next->fd_in = 0;
	data->cmd_head->next->fd_out = 1;
	data->cmd_head->next->flag = 0;
	data->cmd_head->next->next = 0;
}

void	execute(t_data *data, char **envp)
{
	int		fd;
	int		ret;

	// 일반 실행, 인자 넣어서 실행, 리다이렉션이 있는 경우

	// > or >> or < 를 찾는다.
	// 해당조건에 따라 file을 open하고
	fd = open("b", O_WRONLY | O_CREAT , 0644);
	printf("%d\n", fd);
	// dup2함수로 fd_in, fd_out을 변경 후
	// argv의 해당 부분(> or 파일이름)을 free 및 0으로 초기화
	ret = dup2(fd, data->cmd_head->next->fd_out);
	//절대경로를 찾고 argv[0]을 수정한 뒤
	execve("/bin/ls", data->cmd_head->next->argv, envp);
	// 실행
	// 위의 실행 결과는 ls -la를 b라는 파일에 저장한다.

	// sort등의 < 도 위와같은 방법으로 실행 가능한지 확인

	// 파이프처리는 어떻게 할지 확인 후 코드 작성 시작
}

int		main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	ft_memset(&data, 0, sizeof(t_data));
	data.env_head = (t_env *)malloc(sizeof(t_env));
	parse_env(data.env_head, envp);
	setting_cmd(&data);
	execute(&data, envp);
}
