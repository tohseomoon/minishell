/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:06:15 by toh               #+#    #+#             */
/*   Updated: 2021/06/30 13:08:43 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int							exit_print_return_msg(t_cmd *curr, int *exit_flag)
{
	int					num;

	num = creat_return_value(curr->argv[1]);
	*exit_flag = 1;
	if (num == 256)
	{
		printf("minishell: exit: %s: numeric argument required\n",
				curr->argv[1]);
		num = 255;
	}
	else if (num != 256 && curr->argc > 2)
	{
		printf("minishell: exit: too many arguments\n");
		num = 1;
		*exit_flag = 0;
	}
	return (num);
}
