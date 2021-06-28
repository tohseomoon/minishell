/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:11:12 by toh               #+#    #+#             */
/*   Updated: 2021/06/23 21:19:54 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		remove_env(t_env *curr)
{
	t_env	*tmp;

	tmp = curr->next;
	curr->next = curr->next->next;
	free(tmp->key);
	tmp->key = 0;
	free(tmp->value);
	tmp->value = 0;
	free(tmp);
	tmp = 0;
}

static int		check_keys(char **keys, int i)
{
	if (!key_isallowed(keys[i]))
	{
		printf("minishell: unset: `%s': not a valid identifier\n",
				keys[i]);
		g_data.return_value = 1;
		return (i + 1);
	}
	return (i);
}

void			ft_unset(t_cmd *curr)
{
	t_env	*curr_env;
	int		i;

	g_data.return_value = 0;
	i = 1;
	while (curr->argv[i])
	{
		i = check_keys(curr->argv, i);
		if (curr->argv[i] == 0)
			break ;
		curr_env = g_data.env_head;
		while (curr_env->next)
		{
			if (!ft_strcmp(curr_env->next->key, curr->argv[i]))
			{
				remove_env(curr_env);
				break ;
			}
			curr_env = curr_env->next;
		}
		i++;
	}
}
