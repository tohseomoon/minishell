/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_token_nomal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:42:56 by toh               #+#    #+#             */
/*   Updated: 2021/06/30 13:42:57 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		join_tmp_str(t_token_util *utils, char *str)
{
	if (utils->tmp == 0)
	{
		utils->tmp = str;
		str = 0;
	}
	else
	{
		utils->tmp = ft_strjoin_free_s1(&(utils->tmp), str);
		free(str);
		str = 0;
	}
}

void		check_join_cmd(t_token_util *utils)
{
	if (utils->cmd != 0)
	{
		utils->cmd = ft_strjoin_free_s1(&(utils->cmd), utils->tmp);
		free(utils->tmp);
		utils->tmp = 0;
	}
	else
	{
		utils->cmd = utils->tmp;
		utils->tmp = 0;
	}
	utils->cnt = 0;
}

void		make_tmp_str(t_token_util *utils)
{
	char	*nomal;

	nomal = 0;
	if (utils->cnt != 0)
		nomal = ft_strldup(utils->str - utils->cnt, utils->cnt + 1);
	if (utils->tmp != 0 && nomal != 0)
	{
		utils->tmp = ft_strjoin_free_s1(&(utils->tmp), nomal);
		free(nomal);
		nomal = 0;
	}
	else if (nomal != 0)
		utils->tmp = nomal;
	utils->cnt = 0;
}

void		nomal_str(t_token_util *utils)
{
	make_tmp_str(utils);
	check_join_cmd(utils);
	if (utils->cmd != 0)
	{
		new_token(utils->cmd, 1);
		free(utils->cmd);
		utils->cmd = 0;
	}
}
