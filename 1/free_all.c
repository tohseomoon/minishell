/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:40:44 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/15 21:24:00 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->argc)
	{
		free(cmd->argv[i]);
		i++;
	}
}

void		free_env(t_env *env)
{
	free(env->key);
	free(env->value);
}

void		free_path()
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

void		free_all()
{
	t_cmd	*curr_cmd;
	t_cmd	*tmp_cmd;
	t_env	*curr_env;
	t_env	*tmp_env;

	curr_cmd = g_data.cmd_head->next;
	curr_env = g_data.env_head->next;
	while (curr_cmd)
	{
		free_cmd(curr_cmd);
		tmp_cmd = curr_cmd;
		curr_cmd = curr_cmd->next;
		free(tmp_cmd);
	}
	free(g_data.cmd_head);
	while (curr_env)
	{
		free_env(curr_env);
		tmp_env = curr_env;
		curr_env = curr_env->next;
		free(tmp_env);
	}
	free(g_data.env_head);
	free_path();
}

/*
 	old_env, new_env;
	replace_env(), replace_backquote() 메모리 누수 확인;
*/
