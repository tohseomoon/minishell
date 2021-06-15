/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:43:15 by toh               #+#    #+#             */
/*   Updated: 2021/06/15 18:10:39 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_env_str(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = 0;
		i++;
	}
	free(env);
}

void	ft_export(t_cmd *curr)
{
	int		i;

	if (curr->argc == 1)
	{
		g_data.old_env = arr_env_string();
		g_data.new_env = arr_new_env_string();
		print_sort_env();
		free_env_str(g_data.new_env);
		g_data.new_env = 0;
		free_env_str(g_data.old_env);
		g_data.old_env = 0;
	}
	else
	{
		i = 1;
		while(curr->argv[i])
		{
			
		}	
	}
}
