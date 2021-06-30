/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 12:55:52 by toh               #+#    #+#             */
/*   Updated: 2021/06/30 13:35:12 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int					ft_is_exit_num(char *str)
{
	int					i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void						run_exit(int flag, int num)
{
	if (flag == 1)
	{
		free_all();
		exit(num);
	}
	else
		g_data.return_value = num;
}

void						ft_exit(t_cmd *curr, int flag)
{
	int					num;

	if (curr->type == 1)
		return ;
	num = g_data.return_value;
	if (curr->prev == 0 || curr->prev->type == 0)
		printf("exit\n");
	if (curr->argc == 1)
		flag = 1;
	else if (ft_is_exit_num(curr->argv[1]))
		num = exit_print_return_msg(curr, &flag);
	else
	{
		num = 255;
		flag = 1;
		printf("minishell: exit: %s: numeric argument required\n",
				curr->argv[1]);
	}
	if (curr->prev != 0 && curr->prev->type == 1)
		flag = 0;
	run_exit(flag, num);
}
