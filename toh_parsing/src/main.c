/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:57:45 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/28 14:22:46 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			exit_shell(void)
{
	free_cmd_list();
	free_all();
	printf("minishell: Cannot allocate memory\n");
	exit(1);
}

void			print_command(void)
{
	int			i;
	t_cmd		*curr;

	i = 0;
	curr = g_data.cmd_head->next;
	while (curr)
	{
		i = 0;
		while (i < curr->argc)
		{
			printf("argv[%d]: %s\n", i, curr->argv[i]);
			i++;
		}
		curr = curr->next;
	}
}

void			init(char **envp)
{
	ft_memset(&g_data, 0, sizeof(t_data));
	g_data.cmd_head = malloc(sizeof(t_cmd));
	g_data.env_head = malloc(sizeof(t_env));
	g_data.token_head = malloc(sizeof(t_token));
	ft_memset(g_data.token_head, 0, sizeof(t_token));
	if (!g_data.cmd_head || !g_data.env_head || !g_data.token_head)
		exit_shell();
	parse_env(envp);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

static int		check_command(char *command)
{
	if (!command)
	{
		printf("exit\n");
		free_all();
		exit(g_data.return_value);
	}
	else if (ft_strlen(command) == 0)
	{
		free(command);
		return (1);
	}
	return (0);
}

int				main(int argc, char **argv, char **envp)
{
	t_cmd		*curr;

	if (argc != 1 || argv[1] != 0)
		return (1);
	init(envp);
	while (1)
	{
		g_data.command = readline("[minishell]$ ");
		if (check_command(g_data.command))
			continue ;
		add_history(g_data.command);
		if (parce_token() == -1)
		{
			free_token();
			continue ;
		}
		if (parce_cmd() == -1)
		{
			free_token();
			free_cmd_list();
			continue ;
		}
		execute_command(envp);
		free_cmd_list();
		g_data.command = 0;
	}
}
