#include "minishell.h"

void		remove_env(char *str, t_env *curr)
{
	t_env	*tmp;

	tmp = curr->next;
	curr->next = curr->next->next;
	free(tmp->key);
	tmp->key = 0;
	free(tmp->value);
	tmp->value = 0;
	free(tmp);
	tmp = 0;
}

void		ft_unset(t_cmd *curr)
{
	t_env	*curr_env;
	int		i;

	curr_env = g_data.env_head;
	i = 1;
	while (curr->argv[i])
	{
		while (curr_env->next)
		{
			if (!ft_strcmp(curr_env->next->key, curr->argv[i]))
				remove_env(curr->argv[i], curr_env);
			curr_env = curr_env->next;
		}
		i++;
	}
}