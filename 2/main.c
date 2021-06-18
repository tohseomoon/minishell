/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:57:45 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/18 16:05:23 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			exit_shell(char *message) //temporary
{
	printf("%s\n", message);
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
		exit_shell("Cannot allocate memory");
	parse_env(envp);
	//아래 부터 추가
}

int				main(int argc, char **argv, char **envp)
{
	char		*command;

	init(envp);
	while (1)
	{
		command = readline("[minishell]$ ");
		if (!command)
			break ;
		add_history(command);
		if (parse_command(command) == 0)
			continue ;
		execute_command(envp);
		//free(command);
		//free_all();
	}
}
