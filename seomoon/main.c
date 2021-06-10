/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 18:58:30 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/10 21:20:50 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include<stdio.h>

void	exit_minishell(void)
{
	exit(0);
}

void	show_prompt(void)
{
	ft_putstr_fd("minishell$ ", STDOUT);
}

void	get_input(char **input, t_env *env_head)
{

	get_next_line(STDIN, input);
	if (ft_strcmp(*input, "exit") == 0)
	{
		free(*input);
		printf("exit\n");
		exit_minishell();
		return ;
	}
	if (ft_strcmp(*input, "env") == 0)
		print_env(env_head);
}

int		main(int argc, char **argv, char **envp)
{
	char 	*input;
	t_env   env_head;
	t_cmd	cmd_head;
    
    parse_env(&env_head, envp);
	while (1)
	{
		show_prompt();
		get_input(&input, &env_head);
		parse_input(&cmd_head, &env_head, input);
		free(input);
		//print_command(cmd_head);
	}
}
