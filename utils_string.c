/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:39:24 by toh               #+#    #+#             */
/*   Updated: 2021/06/04 14:32:45 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_free_s1(char **s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	char	*result;

	if (*s1 == 0 || s2 == 0)
	{
		free(*s1);
		*s1 = 0;
		return (0);
	}
	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == 0)
	{
		free(*s1);
		*s1 = 0;
		return (0);
	}
	ft_strlcpy(result, *s1, s1_len + 1);
	ft_strlcpy(result + s1_len, s2, s2_len + 1);
	free(*s1);
	*s1 = 0;
	return (result);
}

int		ft_strchr_index(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (unsigned char)c)
	{
		if (s[i] == 0)
			return (0);
		i++;
	}
	i++;
	return (i);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	cnt;

	if (dest == 0 || src == 0)
		return (0);
	cnt = 0;
	while (cnt + 1 < destsize && src[cnt] != 0)
	{
		dest[cnt] = src[cnt];
		cnt++;
	}
	if (destsize != 0)
		dest[cnt] = 0;
	while (src[cnt])
		cnt++;
	return (cnt);
}

char	*ft_strdup(const char *s1)
{
	int		str_len;
	char	*str;

	str_len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str == 0)
		return (0);
	ft_strlcpy(str, s1, str_len + 1);
	return (str);
}
