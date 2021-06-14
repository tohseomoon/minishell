#include "minishell.h"

void	export(t_data *data, t_cmd *curr)
{
	if (curr->argc == 1)
		print_sort_env(data);
}