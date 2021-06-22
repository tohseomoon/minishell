/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:57:45 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/22 12:43:10 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			exit_shell()
{
	free_cmd_list();
	free_env();
	printf("minishell: Cannot allocate memory\n");
	exit(1);
}

void			print_command()
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
	/*
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	*/
}

int				main(int argc, char **argv, char **envp)
{
	char		*command;

	if (argc != 1 || argv[1] != 0)
		return (1);
	init(envp);
	while (1)
	{
		command = readline("[minishell]$ ");
		if (!command || ft_strlen(command) == 0)
		{
			free(command);
			continue ;
		}
		add_history(command);
		if (parse_command(command) == 0)
		{
			free(command);
			free_cmd_list();
			continue ;
		}
		free(command);
		print_command();
		execute_command(envp);
		free_cmd_list();
	}
}
