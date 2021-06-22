/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 12:55:52 by toh               #+#    #+#             */
/*   Updated: 2021/06/17 15:35:01 by toh              ###   ########.fr       */
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

static unsigned long long	creat_ull_number(char *str, int *minus)
{
	unsigned long long	num;
	int					i;

	i = 0;
	num = 0;
	*minus = 0;
	if (str[0] == '+')
		i++;
	else if (str[0] == '-')
	{
		i++;
		*minus = 1;
	}
	while (str[i])
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num);
}

static int					creat_return_value(char *str)
{
	unsigned long long	num;
	int					minus;
	int					cnt;

	cnt = 0;
	while (str[cnt])
		cnt++;
	if (cnt > 21)
		return (256);
	num = creat_ull_number(str, &minus);
	if (num > 9223372036854775807 && minus == 0)
		return (256);
	else if (num - 1 > 9223372036854775807 && minus == 1)
		return (256);
	num %= 256;
	if (minus == 1 && num != 0)
		num = 256 - num;
	return (num);
}

static int					exit_print_return_msg(t_cmd *curr, int *exit_flag)
{
	int					num;

	num = creat_return_value(curr->argv[1]);
	printf("exit\n");
	if (num == 256)
	{
		printf("bash: exit: %s: numeric argument required\n", curr->argv[1]);
		num = 255;
	}
	else if (num != 256 && curr->argc > 2)
	{
		printf("bash: exit: too many arguments\n");
		num = 1;
		*exit_flag = 0;
	}
	return (num);
}

void						ft_exit(t_cmd *curr)
{
	int					num;
	int					exit_flag;

	exit_flag = 1;
	if (curr->argc == 1)
	{
		printf("exit\n");
		num = 0;
	}
	else if (ft_is_exit_num(curr->argv[1]))
		num = exit_print_return_msg(curr, &exit_flag);
	else
	{
		num = 255;
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n", curr->argv[1]);
	}
	if (curr->prev == 0 && exit_flag == 1)
		exit(num);
	else
		g_data.return_value = num;
}
