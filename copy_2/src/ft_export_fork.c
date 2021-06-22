/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:07:12 by toh               #+#    #+#             */
/*   Updated: 2021/06/21 11:07:13 by toh              ###   ########.fr       */
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

void			ft_export_fork(void)
{
	g_data.env = arr_env_string();
	print_sort_env();
	free_env_str(g_data.env);
	g_data.env = 0;
	g_data.return_value = 0;
}
