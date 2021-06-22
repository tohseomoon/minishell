/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:16:32 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/22 15:36:34 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			count_words(char *str)
{
	int				i;
	int				count;

	i = 0;
	while (is_space(str[i]))
		i++;
	count = 0;
	while (str[i] && !is_command_end(str[i]))
	{
		if (!is_space(str[i]) &&
				(is_space(str[i + 1]) || is_command_end(str[i + 1])))
			count++;
		i++;
	}
	return (count);
}

int				init_argv(t_cmd *curr, char *command, int i)
{
	curr->argc = count_words(command + i);
	curr->argv = malloc(sizeof(char *) * (curr->argc + 1));
	if (!curr->argv)
		exit_shell();
	curr->index = 0;
	return (curr->argc);
}

void				add_new_cmd(t_cmd *curr)
{
	t_cmd			*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_shell();
	ft_memset(new, 0, sizeof(t_cmd));
	new->prev = curr;
	new->fd_out = 1;
	curr->next = new;
}

t_cmd				*init_cmd(void)
{
	t_cmd			*curr;

	g_data.cmd_head->next = malloc(sizeof(t_cmd));
	if (!g_data.cmd_head->next)
		exit_shell();
	curr = g_data.cmd_head->next;
	ft_memset(curr, 0, sizeof(t_cmd));
	curr->fd_out = 1;
	return (curr);
}
