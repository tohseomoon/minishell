#include "minishell.h"
int		count_env(t_env *curr)
{
	int		cnt;

	curr = curr->next;
	cnt = 0;
	while (curr)
	{
		curr = curr->next;
		cnt++;
	}
	return (cnt);
}

char	*join_env_string(t_env *curr)
{
	char	*str;
	char	equal[3];
	char	quates[2];

	equal[0] = '=';
	equal[1] = '\"';
	equal[2] = 0;
	quates[0] = '\"';
	quates[1] = 0;
	str = ft_strdup(curr->key);
	if (str == 0)
		return (0);
	str = ft_strjoin_free_s1(&str, equal);
	if (str == 0)
		return (0);
	str = ft_strjoin_free_s1(&str, curr->value);
	if (str == 0)
		return (0);
	str = ft_strjoin_free_s1(&str, quates);
	if (str == 0)
		return (0);
	return (str);
}

void	sort_env_arr(char **env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**arr_env_string(t_data *data)
{
	char	**env;
	t_env	*curr;
	int		cnt;
	int		i;

	cnt = count_env(data->env_head);
	env = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (env == 0)
		return (0);
	env[cnt] = 0;
	i = 0;
	curr = data->env_head->next;
	while (i < cnt)
	{
		env[i] = join_env_string(curr);
		curr = curr->next;
		i++;
	}
	sort_env_arr(env);
	return (env);
}

void	print_sort_env(t_data *data)
{
	int		i;

	if (data->old_env == 0)
	{
		printf("Invalid environment variable\n");
		return ;
	}
	i = 0;
	while (data->old_env[i])
	{
		printf("declare -x %s\n", data->old_env[i]);
		i++;
	}
}