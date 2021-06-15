/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:57:45 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/15 16:27:37 by seomoon          ###   ########.fr       */
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
	parse_env(envp);
	g_data.path = parse_path();
	//g_data.old_env = arr_env_string();
	//시그널 처리
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
		if (ft_strcmp(command, "exit") == 0)
		{
			free(command);
			break ;
		}
		add_history(command);
		parse_command(command);
		execute_command(envp);
		free(command);
		//free_data();
		//print_command();
	}
}
