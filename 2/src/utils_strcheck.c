/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strcheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 21:15:53 by toh               #+#    #+#             */
/*   Updated: 2021/06/21 21:18:17 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char		*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (unsigned char)c)
	{
		if (s[i] == 0)
			return (0);
		i++;
	}
	return ((char *)(s + i));
}

int			ft_isalpha(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (1);
	return (0);
}

int			ft_isalnum(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')
	|| ('0' <= c && c <= '9'))
		return (1);
	return (0);
}
