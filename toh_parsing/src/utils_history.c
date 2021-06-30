/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:55:22 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/30 13:59:43 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}

int			ft_putchar(int c)
{
	return (write(1, &c, 1));
}

char		*add_char_to_str(char *str, char c)
{
	int		i;
	char	*result;

	if (!str)
	{
		result = malloc(sizeof(char) * 2);
		result[0] = c;
		result[1] = '\0';
	}
	else
	{
		result = malloc(sizeof(char) * (ft_strlen(str) + 2));
		if (!result)
			return (NULL);
		i = 0;
		while (str[i])
		{
			result[i] = str[i];
			i++;
		}
		result[i++] = c;
		result[i] = '\0';
		free(str);
	}
	return (result);
}

char		*remove_last_char(char *str)
{
	int		i;
	int		len;
	char	*result;

	if (!str || ft_strlen(str) == 0)
		return (NULL);
	len = ft_strlen(str);
	if (!(result = malloc(sizeof(char) * (len + 1))))
		exit_shell();
	i = 0;
	while (i < len - 1)
	{
		result[i] = str[i];
		i++;
	}
	result[len - 1] = '\0';
	free(str);
	return (result);
}
