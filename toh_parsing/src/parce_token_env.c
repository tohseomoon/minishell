#include "minishell.h"

char		*change_env_str(char *str)
{
	t_env	*curr;
	char	*value;

	value = 0;
	curr = g_data.env_head->next;
	while (curr)
	{
		if (!ft_strcmp(curr->key, str))
		{
			value = ft_strdup(curr->value);
			return (value);
		}
		curr = curr->next;
	}
	return (value);
}

static void	make_env_value_str(t_token_util *utils)
{
	char	*value;
	char	*key;
	
	key = 0;
	value = 0;
	while (*(utils->str) && *(utils->str) != ' ' && *(utils->str) != '$' && *(utils->str) != '/' && !is_quotes(*(utils->str)))
	{
		(utils->str)++;
		(utils->cnt)++;
	}
	key = ft_strldup(utils->str - utils->cnt, utils->cnt + 1);
	value = change_env_str(key);
	free(key);
	key = 0;
	if (value == 0)
		value = ft_strdup("");
	join_tmp_str(utils, value);
}

void		env_str(t_token_util *utils)
{
	make_tmp_str(utils);
	(utils->str)++;
	if (*(utils->str) == ' ' || *(utils->str) == 0 || *(utils->str) == '|' || *(utils->str) == ';' || is_quotes(*(utils->str)))
		join_tmp_str(utils, ft_strdup("$"));
	else if (*(utils->str) == '$')
	{
		join_tmp_str(utils, ft_itoa(getpid()));
		utils->str++;
	}
	else if (*(utils->str) == '?')
	{
		join_tmp_str(utils, ft_itoa(g_data.return_value));
		utils->str++;
	}
	else
		make_env_value_str(utils);
	utils->cnt = 0;
}