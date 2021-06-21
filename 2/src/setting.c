#include "minishell.h"

////////////////아래는 사용 안할 함수/////////////
void    print_env()
{
    t_env   *curr;

    curr = g_data.env_head->next;
    while (curr)
    {
        printf("=====================================================\n");
        printf("%s\n", curr->key);
        printf("%s\n", curr->value);
        printf("=====================================================\n");
        curr = curr->next;
    }
}

void	free_data() // 누수 체크를 위한 free 함수
{
	t_cmd	*curr_cmd;
	t_cmd	*cmd_tmp;
	t_env	*curr_env;
	t_env	*env_tmp;
	int		i;

	curr_cmd = g_data.cmd_head->next;
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
	free(g_data.cmd_head);
	
	curr_env = g_data.env_head->next;
	while (curr_env)
	{
		env_tmp = curr_env->next;
		free(curr_env->key);
		free(curr_env->value);
		free(curr_env);
		curr_env = env_tmp;
	}
	free(g_data.env_head);

	i = 0;
	while (g_data.path[i])
	{
		free(g_data.path[i]);
		i++;
	}
	free(g_data.path);
}

void	print_cmd() // cmd변화를 확인하기 위한 print함수
{
	t_cmd	*curr;
	int		i;

	curr = g_data.cmd_head->next;
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
