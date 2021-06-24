/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:57:45 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/24 15:06:38 by toh              ###   ########.fr       */
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
	//signal(SIGINT, handler);
	//signal(SIGQUIT, handler);
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
/*
static void			del_quotes(void)
{
	char	*new_command;
	int		str_len;
	int		i;
	int		j;

	str_len = ft_strlen(g_data.command);
	new_command = (char *)malloc(sizeof(char) * (str_len + 1));
	if (new_command == 0)
		exit_shell();
	i = 0;
	j = 0;
	while (i < str_len)
	{
		if (g_data.command[i] == S_QUOTE && g_data.command[i + 1] == S_QUOTE)
			i += 2;
		else if (g_data.command[i] == D_QUOTE && g_data.command[i + 1] == D_QUOTE)
			i += 2;
		new_command[j] = g_data.command[i];
		i++;
		j++;
	}
	new_command[j] = 0;
	free(g_data.command);
	g_data.command = new_command;
}
*/
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
		curr = init_cmd();
		//if (ft_strlen(g_data.command) > 2)
		//	del_quotes();
		if (parse_command(g_data.command, curr) == 0)
		{
			free(g_data.command);
			free_cmd_list();
			continue ;
		}
		free(g_data.command);
		//print_cmd();

		execute_command(envp);
		free_cmd_list();
	}
}
