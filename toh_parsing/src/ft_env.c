/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 12:55:20 by toh               #+#    #+#             */
/*   Updated: 2021/06/23 21:39:00 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd)
{
	t_env	*curr;

	if (cmd->argv[1] == 0)
	{
		curr = g_data.env_head->next;
		while (curr)
		{
			if (curr->equal == 1)
				printf("%s=%s\n", curr->key, curr->value);
			curr = curr->next;
		}
		g_data.return_value = 0;
	}
	else
	{
		printf("env: %s: No such file or directory\n", cmd->argv[1]);
		g_data.return_value = 127;
	}
}
