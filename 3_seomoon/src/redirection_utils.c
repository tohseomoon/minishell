/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:17:50 by toh               #+#    #+#             */
/*   Updated: 2021/06/21 11:18:08 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		cnt_redirections(t_cmd *curr)
{
	int		cnt;
	int		i;

	cnt = 0;
	i = 0;
	while (curr->argv[i])
	{
		if (curr->argv[i][0] == '>' || curr->argv[i][0] == '<')
		{
			if (curr->argv[i + 1] == 0)
				return (-1);
			cnt++;
		}
		i++;
	}
	return (cnt);
}

static void		free_old_cmd_argv(t_cmd *curr)
{
	int		i;

	i = 0;
	while (curr->argv[i])
	{
		free(curr->argv[i]);
		curr->argv[i] = 0;
		i++;
	}
	free(curr->argv);
	curr->argv = 0;
}

static char		**creat_new_argv(t_cmd *curr)
{
	char	**new_argv;
	int		i;
	int		j;

	new_argv = (char **)malloc(sizeof(char *) * (curr->argc + 1));
	if (new_argv == 0)
		return (0);
	new_argv[curr->argc] = 0;
	i = 0;
	j = 0;
	while (curr->argv[i])
	{
		if (curr->argv[i][0] != '>' && curr->argv[i][0] != '<')
		{
			new_argv[j] = ft_strdup(curr->argv[i]);
			j++;
			i++;
		}
		else
			i += 2;
	}
	return (new_argv);
}

void			del_redirections(t_cmd *curr)
{
	char	**new_argv;
	int		cnt;

	cnt = cnt_redirections(curr);
	if (cnt == 0 || cnt == -1)
		return ;
	curr->argc -= (cnt * 2);
	new_argv = creat_new_argv(curr);
	free_old_cmd_argv(curr);
	curr->argv = new_argv;
}
