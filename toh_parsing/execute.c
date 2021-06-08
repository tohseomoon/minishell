#include "../minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

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

////////////////////split/////////////
static int		count_arr(char const *s, char c)
{
	int		cnt;
	int		i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	cnt = 0;
	while (s[i])
	{
		cnt++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (cnt);
}

static void		free_str(char **result, int i)
{
	i--;
	while (i >= 0)
	{
		free(result[i]);
		result[i] = 0;
		i--;
	}
}

static char		**split_str(char **result, int arrcnt, char const *s, char c)
{
	int		i;
	int		word_cnt;
	char	*begin;

	i = 0;
	while (i < arrcnt)
	{
		while (*s == c)
			s++;
		begin = (char *)s;
		word_cnt = 0;
		while (*s && *s != c)
		{
			word_cnt++;
			s++;
		}
		result[i] = ft_strldup(begin, word_cnt + 1);
		if (result[i] == 0)
		{
			free_str(result, i);
			return (0);
		}
		i++;
	}
	return (result);
}

char			**ft_split(char const *s, char c)
{
	int		arr_cnt;
	char	**result;
	char	**tmp;

	if (s == 0)
		return (0);
	arr_cnt = count_arr(s, c);
	result = (char **)malloc(sizeof(char *) * (arr_cnt + 1));
	if (result == 0)
		return (0);
	result[arr_cnt] = 0;
	tmp = split_str(result, arr_cnt, s, c);
	if (tmp == 0)
	{
		free(result);
		result = 0;
	}
	return (result);
}
////////////////////////split/////////////////
void	free_data(t_data *data) // 누수 체크를 위한 free 함수
{
	t_cmd	*curr_cmd;
	t_cmd	*cmd_tmp;
	t_env	*curr_env;
	t_env	*env_tmp;
	int		i;

	curr_cmd = data->cmd_head->next;
	while (curr_cmd)
	{
		cmd_tmp = curr_cmd->next;
		i = 0;
		while (curr_cmd->argv[i])
		{
			if (curr_cmd->argv[i] != 0)
				free(curr_cmd->argv[i]);
			i++;
		}
		if (curr_cmd->argv != 0)
			free(curr_cmd->argv);
		free(curr_cmd);
		curr_cmd = cmd_tmp;
	}
	free(data->cmd_head);
	
	curr_env = data->env_head->next;
	while (curr_env)
	{
		env_tmp = curr_env->next;
		free(curr_env->key);
		free(curr_env->value);
		free(curr_env);
		curr_env = env_tmp;
	}
	free(data->env_head);

	i = 0;
	while (data->path[i])
	{
		free(data->path[i]);
		i++;
	}
	free(data->path);
}

void	print_cmd(t_data *data) // cmd변화를 확인하기 위한 print함수
{
	t_cmd	*curr;
	int		i;

	curr = data->cmd_head->next;
	while (curr)
	{
		printf("=========================\n");
		i = 0;
		printf("argc : %d\n", curr->argc);
		while (curr->argv[i])
		{
			printf("[%d] %s\n", i, curr->argv[i]);
			i++;
		}
		printf("fd_in : %d\n", curr->fd_in);
		printf("fd_out : %d\n", curr->fd_out);
		printf("=========================\n");
		curr = curr->next;
	}
}


void	setting_cmd(t_data *data) //파싱되었다고 가정하기 위한 구조체 셋팅
{
	data->cmd_head = (t_cmd *)malloc(sizeof(t_cmd));
	data->cmd_head->next = (t_cmd *)malloc(sizeof(t_cmd));
	data->cmd_head->next->argc = 4;
	data->cmd_head->next->argv = (char **)malloc(sizeof(char *) * 7);
	data->cmd_head->next->argv[0] = ft_strdup("ls");
	data->cmd_head->next->argv[1] = ft_strdup("-la");
	data->cmd_head->next->argv[2] = ft_strdup(">");
	data->cmd_head->next->argv[3] = ft_strdup("a");
	data->cmd_head->next->argv[4] = 0;
	data->cmd_head->next->argv[5] = 0;
	data->cmd_head->next->argv[6] = 0;
	data->cmd_head->next->fd_in = 0;
	data->cmd_head->next->fd_out = 1;
	data->cmd_head->next->flag = 0;
	data->cmd_head->next->next = 0;
}

int		cnt_redirections(t_cmd *curr) // argc수정을 위한 '>' 체크
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

void	free_old_cmd_argv(t_cmd *curr) // 기존 argv free
{
	int		i;
	
	i = 0;
	while (curr->argv[i])
	{
		free(curr->argv[i]);
		i++;
	}
	free(curr->argv);
}

void	del_redirections(t_cmd *curr) // argv에서 리다이렉션 부분 삭제
{
	// 리다이렉션 이후에는 무조건 파일이름이 온다는 가정(파싱 부분에서 예외처리)
	char	**new_argv;
	char	*tmp;
	int		cnt;
	int		i;
	int		j;

	cnt = cnt_redirections(curr);
	if (cnt == -1)
		exit(0);
	curr->argc -= (cnt * 2);
	new_argv = (char **)malloc(sizeof(char *) * curr->argc + 1);
	new_argv[curr->argc] = 0;
	if (new_argv == 0)
		exit(0);
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
	free_old_cmd_argv(curr);
	curr->argv = new_argv;
}

int		open_file(t_cmd *curr) // 리다이렉션이 있다면 파일 오픈
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

int		find_cmd_path(t_data *data, t_cmd *curr) // 명령어 경로 검색 및 수정
{
	DIR				*dp;
	struct dirent	*entry;
	char			*directory;
	int		i;

	i = 0;
	directory = 0;
	while (data->path[i])
	{
		dp = opendir(data->path[i]);
		if (dp == 0)
			return (0);
		while ((entry = readdir(dp)) != 0)
		{
			if (!ft_strcmp(entry->d_name, curr->argv[0]))
				directory = ft_strdup(data->path[i]);
		}
		closedir(dp);
		i++;
	}
	if (directory == 0)
		return (0);
	directory = ft_strjoin_free_s1(&directory, "/");
	directory = ft_strjoin_free_s1(&directory, curr->argv[0]);
	free(curr->argv[0]);
	curr->argv[0] = directory;
	return (1);
}

int		find_absolute_path(t_data *data, t_cmd *curr) //절대경로에 프로그램이 있는지 확인
{
	struct stat		buf;
	int				ret;

	ret = stat(curr->argv[0], &buf);
	if (ret == -1)
		return (0);
	return (1);
	// 해당 파일이 있다면 리턴 0
	// 없다면 리턴 -1
}

void	execute_cmd_path(t_cmd *curr, char **envp) // 찾은 경로로 실행
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		dup2(curr->fd_in, 0);
		dup2(curr->fd_out, 1);
		if (execve(curr->argv[0], curr->argv, envp) == -1)
		{
			printf("error\n");
			exit(0);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("status : %d\n", status);
	}
}

void	execute(t_data *data, char **envp) //실행부분 메인 함수
{
	//에러 명령어 경우 구조체에 정보가 없다고 가정 // 혹은 flag?
	t_cmd	*curr;
	int		i;

	curr = data->cmd_head->next;
	while (curr)
	{
		if ((i = open_file(curr)) > 0)
			printf("bash: %s: No such file or directory\n", curr->argv[i + 1]);
			  //리다이렉션 체크 후 파일 열기
			
		/*
		else if (billitin_cmd())
			// if 쉘 빌트인인지 확인
		*/
		else if (curr->argv[0][0] == '/')
		{
			if (find_absolute_path(data, curr))
				execute_cmd_path(curr, envp);// 실행하기
			else	
				printf("bash : %s: No such file or directory\n", curr->argv[0]);
		}
		else if(find_cmd_path(data, curr))
			execute_cmd_path(curr, envp);	 
		else
			printf("bash : %s: command not found\n", curr->argv[0]);
		curr = curr->next;
		// 어딘가에 pipe를 넣어야 함
	}

}
char	*find_path(t_data *data) // env list에서 path 찾아오기
{
	t_env	*curr;
	char	*path;
	
	curr = data->env_head->next;
	while(curr)
	{
		if (!ft_strcmp(curr->key, "PATH"))
			path = ft_strdup(curr->value);
		curr = curr->next;
	}
	return (path);
}

char	**parse_path(t_data *data) // 찾은 path로 스플릿
{
	char	*path;
	char	**split_path;

	path = find_path(data);
	split_path = ft_split(path, ':');
	free(path);
	return (split_path);
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
