/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:57:45 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/22 15:44:33 by seomoon          ###   ########.fr       */
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
	if (!g_data.cmd_head || !g_data.env_head)
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
	char		*command;
	t_cmd		*curr;

	if (argc != 1 || argv[1] != 0)
		return (1);
	init(envp);
	while (1)
	{
		command = readline("[minishell]$ ");
		if (check_command(command))
			continue ;
		add_history(command);
		curr = init_cmd();
		if (parse_command(command, curr) == 0)
		{
			free(command);
			free_cmd_list();
			continue ;
		}
		free(command);
		execute_command(envp);
		free_cmd_list();
	}
}
