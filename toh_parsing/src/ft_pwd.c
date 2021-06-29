/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:46:23 by toh               #+#    #+#             */
/*   Updated: 2021/06/28 17:06:38 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*buf;

	buf = 0;
	buf = getcwd(buf, 0);
	if (buf == 0)
		printf("getcwd: cannot access parent directories: No such file or directory\n");
	else
		printf("%s\n", buf);
	free(buf);
	g_data.return_value = 0;
}
