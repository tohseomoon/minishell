/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:40:44 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/21 21:21:54 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_path(void)
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

void			free_all(void)
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
	free(g_data.cmd_head);
}

void			free_cmd_list(void)
{
	t_cmd	*curr;
	t_cmd	*tmp;

	curr = g_data.cmd_head->next;
	while (curr)
	{
		tmp = curr->next;
		free_cmd(curr);
		free(curr);
		curr = tmp;
	}
}
