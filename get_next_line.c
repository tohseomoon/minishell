/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:08:13 by toh               #+#    #+#             */
/*   Updated: 2021/06/04 14:33:09 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	first_read_buf(int fd, char *buf, char *backup)
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

static int	read_buf(int fd, char *buf, char **tmp)
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

static int	get_str_line(int fd, char *buf, char **tmp, char **line)
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
	static char	*backup[20];
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
