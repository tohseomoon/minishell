/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtin_fun.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:48:18 by toh               #+#    #+#             */
/*   Updated: 2021/06/30 13:39:00 by toh              ###   ########.fr       */
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

static int		check_exit(t_cmd *curr)
{
	while (curr)
	{
		curr = curr->next;
		if (curr == 0)
			return (0);
		if (!ft_strcmp("exit", curr->argv[0]))
			return (1);
	}
	return (0);
}

void			builtin_cmd(t_cmd *curr)
{
	if (check_exit(curr))
		return ;
	if (ft_strcmp("exit", curr->argv[0]) == 0)
		ft_exit(curr, 0);
	else if (ft_strcmp("export", curr->argv[0]) == 0)
		ft_export(curr);
	else if (ft_strcmp("unset", curr->argv[0]) == 0)
		ft_unset(curr);
	else if (ft_strcmp("cd", curr->argv[0]) == 0)
		ft_cd(curr);
}
