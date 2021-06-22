/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:40:44 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/20 16:16:31 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_path(void)
{
	int		i;

	i = 0;
	while (g_data.path[i])
	{
		free(g_data.path[i]);
		i++;
	}
	free(g_data.path);
}

static void		free_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->argv[i])
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
}

void		free_env()
{
	t_env	*curr_env;
	t_env	*tmp_env;

	curr_env = g_data.env_head->next;
	while (curr_env)
	{
		tmp_env = curr_env;
		curr_env = curr_env->next;
		free(tmp_env->key);
		free(tmp_env->value);
		free(tmp_env);
	}
	free(g_data.env_head);
}

void		free_cmd_list()
{
	t_cmd	*curr_cmd;
	t_cmd	*tmp_cmd;

	curr_cmd = g_data.cmd_head->next;
	while (curr_cmd)
	{
		tmp_cmd = curr_cmd;
		curr_cmd = curr_cmd->next;
		free_cmd(tmp_cmd);
	}
}

/*
	replace_env(), replace_backquote() 메모리 누수 확인;
*/
