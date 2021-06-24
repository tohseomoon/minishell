/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:00:32 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/23 11:22:28 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_seperator(char c)
{
	if (c == S_QUOTE || c == D_QUOTE)
		return (1);
	else if (is_space(c))
		return (1);
	return (0);
}

int			is_command_end(char c)
{
	if (c == '\0' || c == '|' || c == ';')
		return (1);
	return (0);
}

int			is_symbol(char c)
{
	if (c == '$' || c == '`')
		return (1);
	return (0);
}

int			is_operator(char c)
{
	if (c == S_QUOTE || c == D_QUOTE || is_symbol(c) || c == '~')
		return (1);
	return (0);
}
