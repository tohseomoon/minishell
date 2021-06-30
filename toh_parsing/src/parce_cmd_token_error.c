/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd_token_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:43:56 by toh               #+#    #+#             */
/*   Updated: 2021/06/30 13:43:57 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_token_error_msg(char *str)
{
	g_data.return_value = 258;
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	return (0);
}

static int		check_next_token_error(char *str, int flag)
{
	int			len;

	len = ft_strlen(str);
	if (str[0] == '>' && len > 1 && flag == 1)
		return (check_token_error_msg(">>"));
	else if (str[0] == '>' && len == 1 && flag == 1)
		return (check_token_error_msg(">"));
	else if (str[0] == '<' && len > 1 && flag == 1)
		return (check_token_error_msg("<<"));
	else if (str[0] == '<' && len == 1 && flag == 1)
		return (check_token_error_msg("<"));
	else if (str[0] == '|' && len > 1)
		return (check_token_error_msg("||"));
	else if (str[0] == '|' && len == 1)
		return (check_token_error_msg("|"));
	else if (str[0] == ';' && len > 1)
		return (check_token_error_msg(";;"));
	else if (str[0] == ';' && len == 1)
		return (check_token_error_msg(";"));
	return (1);
}

int				check_redirection_token_error(t_token *token)
{
	int			len;

	len = ft_strlen(token->str);
	if (token->str[0] == '>' && len > 3)
		return (check_token_error_msg(">>"));
	else if (token->str[0] == '>' && len > 2)
		return (check_token_error_msg(">"));
	else if (token->str[0] == '<' && len > 3)
		return (check_token_error_msg("<<"));
	else if (token->str[0] == '<' && len > 2)
		return (check_token_error_msg("<"));
	else if (token->next == 0)
		return (check_token_error_msg("newline"));
	if (!check_next_token_error(token->next->str, 1))
		return (0);
	return (1);
}

int				check_prev_token_error(t_token *token, int len)
{
	if (token->str[0] == '|' && len == 1 && token->prev == 0)
		return (check_token_error_msg("|"));
	else if (token->str[0] == '|' && len > 1 && token->prev == 0)
		return (check_token_error_msg("||"));
	else if (token->str[0] == ';' && len == 1 && token->prev == 0)
		return (check_token_error_msg(";"));
	else if (token->str[0] == ';' && len > 1 && token->prev == 0)
		return (check_token_error_msg(";;"));
	return (1);
}

int				check_token_error(t_token *token)
{
	int			len;

	len = ft_strlen(token->str);
	if (token->prev == 0)
		return (check_prev_token_error(token, len));
	else if (token->str[0] == '|' && len > 2)
		return (check_token_error_msg("||"));
	else if (token->str[0] == '|' && len > 1)
		return (check_token_error_msg("|"));
	else if (token->str[0] == ';' && len > 1)
		return (check_token_error_msg(";;"));
	else if (token->str[0] == '|' && len == 1 && token->next == 0)
		return (check_token_error_msg("|"));
	else if (token->str[0] == '|' && len > 2 && token->next == 0)
		return (check_token_error_msg("||"));
	else if (token->str[0] == ';' && len == 1 && token->next == 0)
		return (1);
	if (!check_next_token_error(token->next->str, 0))
		return (0);
	return (1);
}
