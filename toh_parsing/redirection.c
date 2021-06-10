#include "minishell.h"

static int		cnt_redirections(t_cmd *curr) // argc수정을 위한 '>' 체크
{
	int		cnt;
	int		i;

	cnt = 0;
	i = 0;
	while (curr->argv[i])
	{
		if (curr->argv[i][0] == '>' || curr->argv[i][0] == '<')
		{
			if (curr->argv[i + 1] == 0)
				return (-1);
			cnt++;
		}
		i++;
	}
	return(cnt);
}

static void		free_old_cmd_argv(t_cmd *curr) // 기존 argv free
{
	int		i;
	
	i = 0;
	while (curr->argv[i])
	{
		free(curr->argv[i]);
		curr->argv[i] = 0;
		i++;
	}
	free(curr->argv);
	curr->argv = 0;
}

static char		**creat_new_argv(t_cmd *curr) // 새로운 argv생성(리다이렉션 제거)
{
	char	**new_argv;
	int		i;
	int		j;
	
	new_argv = (char **)malloc(sizeof(char *) * curr->argc + 1);
	if (new_argv == 0)
		printf("error_allocate\n");
	new_argv[curr->argc] = 0;
	i = 0;
	j = 0;
	while (curr->argv[i])
	{
		if (curr->argv[i][0] != '>' && curr->argv[i][0] != '<')
		{
			new_argv[j] = ft_strdup(curr->argv[i]);
			j++;
		}
		else
			i++;
		i++;
	}
	return (new_argv);
}

static void		del_redirections(t_cmd *curr) // argv에서 리다이렉션 부분 삭제
{
	// 리다이렉션 이후에는 무조건 파일이름이 온다는 가정(파싱 부분에서 예외처리)
	char	**new_argv;
	char	*tmp;
	int		cnt;
	int		i;
	int		j;

	cnt = cnt_redirections(curr);
	if (cnt == -1)
		printf("error_redirection\n");
	curr->argc -= (cnt * 2);
	new_argv = creat_new_argv(curr);	
	free_old_cmd_argv(curr);
	curr->argv = new_argv;
}

int		redirection_open_file(t_cmd *curr) // 리다이렉션이 있다면 파일 오픈
{
	int		i;

	i = 0;
	while (curr->argv[i])
	{
		if (curr->argv[i][0] == '<')
			curr->fd_in = open(curr->argv[i + 1], O_RDONLY);
		else if (curr->argv[i][0] == '>')
		{
			if (curr->argv[i][1] == 0)
				curr->fd_out = open(curr->argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT , 0644);
			else if (curr->argv[i][1] == '>')
				curr->fd_out = open(curr->argv[i + 1], O_WRONLY | O_APPEND | O_CREAT , 0644);
		}
		if (curr->fd_out < 0 || curr->fd_in < 0)
			return (i);
		i++;
	}
	del_redirections(curr);
	return (0);
}