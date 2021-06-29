/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:57:45 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/29 11:01:42 by toh              ###   ########.fr       */
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

void			init_data(char **envp)
{
	ft_memset(&g_data, 0, sizeof(t_data));
	g_data.cmd_head = malloc(sizeof(t_cmd));
	g_data.env_head = malloc(sizeof(t_env));
	g_data.token_head = malloc(sizeof(t_token));
	ft_memset(g_data.token_head, 0, sizeof(t_token));
	if (!g_data.cmd_head || !g_data.env_head || !g_data.token_head)
		exit_shell();
	parse_env(envp);
	g_data.home = change_env_str("HOME");
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	tcgetattr(STDIN_FILENO, &g_data.term.save_term);
}

void			show_prompt(t_data *g)
{
	init_term(&g->term);
	while (1)
	{
		write(STDOUT_FILENO, "[minishell]$ ", 13);
		if (main_term(g) == 0)
		{
			reset_history(g);
			break ;
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g->term.save_term);
}

int				main(int argc, char **argv, char **envp)
{
	t_cmd		*curr;

	if (argc != 1 || argv[1] != 0)
		return (1);
	init_data(envp);
	while (1)
	{
		show_prompt(&g_data);

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
