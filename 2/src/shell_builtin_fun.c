/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtin_fun.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:48:18 by toh               #+#    #+#             */
/*   Updated: 2021/06/21 10:16:33 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_shell_builtin(t_cmd *curr)
{
	if (ft_strcmp("exit", curr->argv[0]) == 0)
		return (1);
	else if ((ft_strcmp("export", curr->argv[0]) == 0) && curr->argc > 1)
		return (1);
	else if (ft_strcmp("unset", curr->argv[0]) == 0)
		return (1);
	else if (ft_strcmp("cd", curr->argv[0]) == 0)
		return (1);
	return (0);
}

static int				check_exit(void)
{
	t_cmd	*curr;

	curr = g_data.cmd_head->next;
	if (curr->next == 0 && curr->prev == 0 && !ft_strcmp("exit", curr->argv[0]))
		return (0);
	while (curr)
	{
		if (!ft_strcmp("exit", curr->argv[0]))
			return (1);
		curr = curr->next;
	}
	return (0);
}

void			builtin_cmd(t_cmd *curr)
{
	if (check_exit())
		return ;
	if (ft_strcmp("exit", curr->argv[0]) == 0)
		ft_exit(curr);
	else if (ft_strcmp("export", curr->argv[0]) == 0)
		ft_export(curr);
	else if (ft_strcmp("unset", curr->argv[0]) == 0)
		ft_unset(curr);
	else if (ft_strcmp("cd", curr->argv[0]) == 0)
		ft_cd(curr);
}

