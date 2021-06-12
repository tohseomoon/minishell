/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:08:13 by toh               #+#    #+#             */
/*   Updated: 2021/06/12 21:35:35 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_strlen( char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_strlcpy(char *dest,  char *src, int destsize)
{
	int	cnt;

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

int		ft_strchr_index( char *s, int c)
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

char	*ft_strdup( char *s1)
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

char	*ft_strldup( char *s1, int n)
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

 int	first_read_buf(int fd, char *buf, char *backup)
{
	int			byte;

	byte = read(fd, buf, BUFFER_SIZE);
	buf[byte] = 0;
	if (byte < 0)
	{
		free(backup);
		return (-1);
	}
	return (byte);
}

 int	read_buf(int fd, char *buf, char **tmp)
{
	int			byte;

	byte = read(fd, buf, BUFFER_SIZE);
	if (byte < 0)
	{
		free(*tmp);
		*tmp = 0;
		return (-1);
	}
	return (byte);
}

 int	get_str_line(int fd, char *buf, char **tmp, char **line)
{
	int			i;
	int			byte;

	byte = 1;
	i = ft_strchr_index(*tmp, '\n');
	while (!i && byte)
	{
		byte = read_buf(fd, buf, tmp);
		if (byte < 0)
			return (-1);
		buf[byte] = 0;
		*tmp = ft_strjoin_free_s1(tmp, buf);
		if (*tmp == 0)
			return (-1);
		i = ft_strchr_index(*tmp, '\n');
	}
	if (i != 0)
		(*tmp)[i - 1] = 0;
	*line = ft_strdup(*tmp);
	if (byte != 0 || i != 0)
		return (i);
	free(*tmp);
	*tmp = 0;
	return (0);
}

int			get_next_line(int fd, char **line)
{
	 char	*backup[20];
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	int			result;

	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (backup[fd] == 0)
		backup[fd] = ft_strdup("");
	result = first_read_buf(fd, buf, backup[fd]);
	if (result < 0)
		return (-1);
	tmp = ft_strjoin_free_s1(&(backup[fd]), buf);
	if (tmp == 0)
		return (-1);
	result = get_str_line(fd, buf, &tmp, line);
	if (result > 0)
	{
		backup[fd] = ft_strdup(tmp + result);
		free(tmp);
		return (1);
	}
	if (result == -1 || *line == 0)
		return (-1);
	return (0);
}
