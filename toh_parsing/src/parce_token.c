/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:41:05 by toh               #+#    #+#             */
/*   Updated: 2021/06/30 13:47:25 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			init_token_utils(t_token_util *utils)
{
	utils->str = g_data.command;
	utils->cmd = 0;
	utils->cnt = 0;
	utils->tmp = 0;
}

static int			free_return(t_token_util *utils)
{
	if (utils->cmd != 0)
		free(utils->cmd);
	if (utils->tmp != 0)
		free(utils->tmp);
	free(g_data.command);
	return (-1);
}

static int			check_token(t_token_util *utils, int result, int *flag)
{
	if (is_quotes(*(utils->str)))
		result = quote_str(utils, *(utils->str));
	else if (*(utils->str) == ' ')
		nomal_str(utils);
	else if (is_symbols(*(utils->str)))
	{
		symbol_str(utils, *(utils->str));
		utils->str--;
	}
	else if (*(utils->str) == '$' && ft_strncmp(utils->str, "$PATH:", 6) != 0)
	{
		env_str(utils);
		*flag = 1;
	}
	else if (ft_strncmp(utils->str, "$PATH:", 6) == 0)
		utils->cnt++;
	if (result == -1)
		return (-1);
	return (0);
}

int					parce_token(void)
{
	t_token_util	utils;
	int				flag;

	if (g_data.command == 0)
		return (-1);
	flag = 0;
	init_token_utils(&utils);
	while (*(utils.str))
	{
		if (check_token(&utils, 0, &flag) == -1)
			return (free_return(&utils));
		if (*(utils.str) == 0)
			break ;
		if (!is_pass_char(*(utils.str)) && flag != 1)
			utils.cnt++;
		if (flag != 1)
			(utils.str)++;
		flag = 0;
	}
	nomal_str(&utils);
	free(g_data.command);
	if (g_data.token_head->next == 0)
	return (-1);
	return (0);
}
