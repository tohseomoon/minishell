#include "minishell.h"

static char			*find_path(void)
{
	t_env	*curr;
	char	*path;

	path = 0;
	curr = g_data.env_head->next;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "PATH"))
			path = ft_strdup(curr->value);
		curr = curr->next;
	}
	return (path);
}

char				**parse_path(void)
{
	char	*path;
	char	**split_path;

	path = find_path();
	split_path = ft_split(path, ':');
	if (path != 0)
		free(path);
	return (split_path);
}