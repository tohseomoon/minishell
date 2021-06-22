/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:15:53 by toh               #+#    #+#             */
/*   Updated: 2021/06/15 14:32:08 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*find_directory(t_cmd *curr)
{
	DIR				*dp;
	struct dirent	*entry;
	char			*directory;
	int				i;

	i = 0;
	directory = 0;
	while (g_data.path[i])
	{
		dp = opendir(g_data.path[i]);
		if (dp == 0)
			return (0);
		while ((entry = readdir(dp)) != 0)
		{
			if (!ft_strcmp(entry->d_name, curr->argv[0]))
				directory = ft_strdup(g_data.path[i]);
		}
		closedir(dp);
		i++;
	}
	return (directory);
}

int				find_cmd_path(t_cmd *curr)
{
	char			*directory;

	directory = find_directory(curr);
	if (directory == 0)
		return (0);
	directory = ft_strjoin_free_s1(&directory, "/");
	directory = ft_strjoin_free_s1(&directory, curr->argv[0]);
	free(curr->argv[0]);
	curr->argv[0] = directory;
	return (1);
}

int				find_cmd_absolute_path(t_cmd *curr)
{
	struct stat		buf;
	int				ret;

	ret = stat(curr->argv[0], &buf);
	if (ret == -1)
	{
		printf("bash: %s: No such file or directory\n", curr->argv[0]);
		return (0);
	}
	else
	{
		if (S_ISDIR(buf.st_mode))
		{
			printf("bash: %s: is a directory\n", curr->argv[0]);
			return (0);
		}
	}
	return (1);
}
