#include "minishell.h"

////////////////아래는 사용 안할 함수/////////////
void    print_env(t_env *env_head)
{
    t_env   *curr;

    curr = env_head->next;
    while (curr)
    {
        printf("=====================================================\n");
        printf("%s\n", curr->key);
        printf("%s\n", curr->value);
        printf("=====================================================\n");
        curr = curr->next;
    }
}

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
			printf("<%d> %s\n", i, curr->argv[i]);
			i++;
		}
		printf("pipe[0] : %d\n", curr->pipe[0]);
		printf("pipe[1] : %d\n", curr->pipe[1]);
		printf("h_pipe[0] : %d\n", curr->heredoc_pipe[0]);
		printf("h_pipe[1] : %d\n", curr->heredoc_pipe[1]);
		printf("fd_in : %d\n", curr->fd_in);
		printf("fd_out : %d\n", curr->fd_out);
		printf("=========================\n");
		curr = curr->next;
	}
}


void	setting_cmd(t_data *data) //파싱되었다고 가정하기 위한 구조체 셋팅
{
	t_cmd	*curr;
	t_cmd	*tmp;
	
	data->cmd_head = (t_cmd *)malloc(sizeof(t_cmd));
	
	data->cmd_head->next = (t_cmd *)malloc(sizeof(t_cmd));
	ft_memset(data->cmd_head->next, 0, sizeof(t_cmd));
	data->cmd_head->next->argc = 3;
	data->cmd_head->next->argv = (char **)malloc(sizeof(char *) * 7);
	data->cmd_head->next->argv[0] = ft_strdup("cat");
	data->cmd_head->next->argv[1] = ft_strdup("<<");
	data->cmd_head->next->argv[2] = ft_strdup("abc");
	data->cmd_head->next->argv[3] = 0;
	data->cmd_head->next->argv[4] = 0;
	data->cmd_head->next->argv[5] = 0;
	data->cmd_head->next->fd_in = 0;
	data->cmd_head->next->fd_out = 1;
	data->cmd_head->next->next = 0;
	data->cmd_head->next->prev = 0;

	data->cmd_head->next->next = (t_cmd *)malloc(sizeof(t_cmd));
	ft_memset(data->cmd_head->next->next, 0, sizeof(t_cmd));
	data->cmd_head->next->next->argc = 2;
	data->cmd_head->next->next->argv = (char **)malloc(sizeof(char *) * 6);
	data->cmd_head->next->next->argv[0] = ft_strdup("grep");
	data->cmd_head->next->next->argv[1] = ft_strdup("a");
	data->cmd_head->next->next->argv[2] = 0;
	data->cmd_head->next->next->argv[3] = 0;
	data->cmd_head->next->next->argv[4] = 0;
	data->cmd_head->next->next->argv[5] = 0;
	data->cmd_head->next->next->fd_in = 0;
	data->cmd_head->next->next->fd_out = 1;
	data->cmd_head->next->next->next = 0;
	data->cmd_head->next->next->prev = data->cmd_head->next;

	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	tmp->argc = 3;
	tmp->argv = (char **)malloc(sizeof(char *) * 7);
	tmp->argv[0] = ft_strdup("sort");
	tmp->argv[1] = ft_strdup(">");
	tmp->argv[2] = ft_strdup("c");
	tmp->argv[3] = 0;
	tmp->argv[4] = 0;
	tmp->argv[5] = 0;
	tmp->argv[6] = 0;
	tmp->fd_in = 0;
	tmp->fd_out = 1;
	tmp->next = 0;
	tmp->prev = data->cmd_head->next->next;
	data->cmd_head->next->next->next = tmp;

}