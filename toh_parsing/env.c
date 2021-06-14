#include "minishell.h"

void	env(t_data *data)
{
	t_env	*curr;

	curr = data->env_head->next;
	while (curr)
	{
		if (curr->equal == 1)
			printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}