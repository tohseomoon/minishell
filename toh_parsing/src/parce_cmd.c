#include "minishell.h"

static void				add_new_cmd(t_cmd *curr)
{
	t_cmd			*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_shell();
	ft_memset(new, 0, sizeof(t_cmd));
	new->prev = curr;
	new->fd_out = 1;
	if (new->prev == g_data.cmd_head)
		new->prev = 0;
	curr->next = new;
}

static	void		allocate_argv(t_token *t_curr, t_cmd *c_curr)
{
	t_token		*start;
	
	start = t_curr;
	c_curr->argc = 0;
	while (start)
	{
		if (start->flag == 2)
			break ;
		c_curr->argc++;
		start = start->next;
	}
	c_curr->argv = (char**)malloc(sizeof(char *) * (c_curr->argc + 1));
	if (c_curr->argv == 0)
		exit_shell();
	c_curr->argv[c_curr->argc] = 0;
}

static int		add_command_argv(t_token **t_curr, t_cmd *c_curr)
{
	int			i;

	i = 0;
	while (i < c_curr->argc)
	{
		if ((*t_curr)->str[0] == '>' || (*t_curr)->str[0] == '<')
		{
			if (!check_redirection_token_error(*t_curr))
			{
				c_curr->argv[i] = 0;
				return (-1);
			}
		}
		c_curr->argv[i] = ft_strdup((*t_curr)->str);
		if (c_curr->argv[i] == 0)
			exit_shell();
		i++;
		*t_curr = (*t_curr)->next;
	}
	return (0);
}

static int		check_cmd(t_token *t_curr, t_cmd *c_curr)
{
	while (t_curr)
	{
		add_new_cmd(c_curr);
		c_curr = c_curr->next;
		allocate_argv(t_curr, c_curr);
		if (add_command_argv(&t_curr, c_curr) == -1)
			return (-1);
		if (t_curr == 0)
			break ;
		if (t_curr->flag == 2)
		{
			if (!check_token_error(t_curr))
				return (-1);
			if (t_curr->str[0] == '|')
				c_curr->type = 1;
			t_curr = t_curr->next;
		}
	}
	return (0);
}

int		parce_cmd(void)
{
	t_token		*t_curr;
	t_cmd		*c_curr;
	int			i;

	c_curr = g_data.cmd_head;
	t_curr = g_data.token_head->next;
	if (check_cmd(t_curr, c_curr) == -1)
		return (-1);	
	free_token();
	return (0);
}