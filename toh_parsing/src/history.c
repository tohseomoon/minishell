/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 04:48:23 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/23 06:57:52 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		remove_history(t_hist *h_head)
{
	if (h_head->prev)
		h_head->prev->next = h_head->next;
	if (h_head->next)
		h_head->next->prev = h_head->prev;
	free(h_head->command);
	free(h_head);
	h_head = 0;
}

void		reset_history(t_data *g)
{
	t_hist	*tmp;

	if (g->h_head == 0)
		return ;
	while (g->h_head->prev) //head를 list 맨 앞으로 이동시키기
		g->h_head = g->h_head->prev;
	tmp = g->h_head->next;
	if (g->h_head->flag == 0) //flag == 0일 때는 history free
	{
		remove_history(g->h_head);
		g->h_head = tmp;
	}
	g->h_flag = 0; //h_flag ?
}

t_hist	*push_front_history(char *command, t_hist *old_head, int flag)
{
	t_hist	*new;

	new = malloc(sizeof(t_hist));
	if (!new)
		exit_shell();
	new->command = ft_strdup(command);
	new->prev = NULL;
	new->next = old_head;
	new->flag = flag;
	if (old_head == NULL)
		old_head->prev = new;
	return (new);
}

void		save_history(t_data *g)
{
	reset_history(g);
	if (!g->command)
		return ;
	if (g->h_head)
		g->h_head = push_front_history(g->command, g->h_head, 1);
	else
		g->h_head = push_front_history(g->command, NULL, 1);
}
