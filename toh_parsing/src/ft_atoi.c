/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:56:23 by toh               #+#    #+#             */
/*   Updated: 2021/06/29 10:37:38 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		check_over_range(unsigned long long num, int sign)
{
	unsigned long long	max;

	max = 9223372036854775807;
	if (num > max && sign == -1)
		return (0);
	if (num >= max && sign == 1)
		return (-1);
	return (num * sign);
}

static int		ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	int					i;
	unsigned long long	sign;
	unsigned long long	num;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	num = 0;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (check_over_range(num, sign));
}
