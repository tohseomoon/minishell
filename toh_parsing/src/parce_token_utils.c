#include "minishell.h"

int			is_quotes(char c)
{
	if (c == S_QUOTE || c == D_QUOTE || c == B_QUOTE)
		return (1);
	return (0);
}

int			is_symbols(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

int			is_pass_char(char c)
{
	if (is_quotes(c) || is_symbols(c) || c == ' ' || c == '$')
		return (1);
	return (0);
}

t_token	*new_token(char *str, int flag)
{
	t_token *tmp;
	t_token *curr;
	
	curr = g_data.token_head;

	while (curr->next)
		curr = curr->next;
	tmp = malloc(sizeof(t_token));
	if (tmp == 0)
		exit_shell();
	ft_memset(tmp, 0, sizeof(t_token));
	if (!ft_strcmp(str, "~"))
		tmp->str = ft_strdup(g_data.home);
	else
		tmp->str = ft_strdup(str);
	tmp->flag = flag;
	tmp->next = 0;
	tmp->prev = curr;
	curr->next = tmp;
	if (tmp->prev == g_data.token_head)
		tmp->prev = 0;
	return (tmp);
}