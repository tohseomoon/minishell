/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 12:55:20 by toh               #+#    #+#             */
/*   Updated: 2021/06/20 16:16:37 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(void)
{
	t_env	*curr;

	curr = g_data.env_head->next;
	while (curr)
	{
		if (curr->equal == 1)
			printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}
