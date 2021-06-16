/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:39:24 by toh               #+#    #+#             */
/*   Updated: 2021/06/16 16:51:32 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void		ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

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

char		*ft_strjoin_free_s1(char **s1, char *s2)
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

int			ft_strchr_index(const char *s, int c)
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

size_t		ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t		ft_strlcpy(char *dest, const char *src, size_t destsize)
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

char		*ft_strtrim(char *str)
{
	int		begin;
	int		end;
	char	*result;

	if (!str)
		return (NULL);
	begin = 0;
	while (str[begin] && is_space(str[begin]))
		begin++;
	end = ft_strlen(str + begin);
	if (end)
		while (str[begin + end - 1] && is_space(str[begin + end - 1]))
			end--;
	result = malloc(sizeof(char) * (end + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *)(str + begin), end + 1);
	return (result);
}

char		*ft_strdup(const char *s1)
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

char		*ft_strldup(const char *s1, int n)
{
	int		str_len;
	char	*str;

	str_len = ft_strlen(s1);
	if (n > str_len + 1)
		return (0);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == 0)
		return (0);
	ft_strlcpy(str, s1, n);
	str[n] = 0;
	return (str);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

static int		count_arr(char const *s, char c)
{
	int		cnt;
	int		i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	cnt = 0;
	while (s[i])
	{
		cnt++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (cnt);
}

static void		free_str(char **result, int i)
{
	i--;
	while (i >= 0)
	{
		free(result[i]);
		result[i] = 0;
		i--;
	}
}

static char		**split_str(char **result, int arrcnt, char const *s, char c)
{
	int		i;
	int		word_cnt;
	char	*begin;

	i = 0;
	while (i < arrcnt)
	{
		while (*s == c)
			s++;
		begin = (char *)s;
		word_cnt = 0;
		while (*s && *s != c)
		{
			word_cnt++;
			s++;
		}
		result[i] = ft_strldup(begin, word_cnt + 1);
		if (result[i] == 0)
		{
			free_str(result, i);
			return (0);
		}
		i++;
	}
	return (result);
}

char			**ft_split(char const *s, char c)
{
	int		arr_cnt;
	char	**result;
	char	**tmp;

	if (s == 0)
		return (0);
	arr_cnt = count_arr(s, c);
	result = (char **)malloc(sizeof(char *) * (arr_cnt + 1));
	if (result == 0)
		return (0);
	result[arr_cnt] = 0;
	tmp = split_str(result, arr_cnt, s, c);
	if (tmp == 0)
	{
		free(result);
		result = 0;
	}
	return (result);
}

int		get_len(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*nbr;
	long	ln;

	ln = n;
	len = get_len(ln);
	nbr = (char *)malloc(sizeof(char) * (len + 1));
	if (!nbr)
		return (NULL);
	nbr[len--] = '\0';
	if (ln == 0)
		nbr[len] = '0';
	if (ln < 0)
	{
		nbr[0] = '-';
		ln *= -1;
	}
	while (ln > 0)
	{
		nbr[len] = (ln % 10) + '0';
		ln /= 10;
		len--;
	}
	return (nbr);
}
