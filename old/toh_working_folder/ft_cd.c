#include "minishell.h"

static char		*find_env_value(char *key)
{
	t_env	*curr;
	
	curr = g_data.env_head->next;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
			return (curr->value);
		curr = curr->next;
	}
	return (0);
}

static int		change_directory(char *command)
{
	char	*path;
	int		result;

	if (command == 0 || (command[0] == '~' && command[1] == 0))
		path = ft_strdup(find_env_value("HOME"));
	else if (command[0] == '-' && command[1] == 0)
	{
		path = ft_strdup(find_env_value("OLDPWD"));
		printf("%s\n", path);
	}
	else
		path = ft_strdup(command);
	result = chdir(path);
	free(path);
	path = 0;
	return (result);
}

static void		update_pwd(char *key, char *new_value)
{
	t_env	*curr;

	curr = g_data.env_head->next;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
		{
			free(curr->value);
			curr->value = ft_strdup(new_value);
			break ;
		}
		curr = curr->next;
	}
}

void	ft_cd(t_cmd *curr)
{
	char	*buf;

	buf = 0;
	if (change_directory(curr->argv[1]) == 0)
	{
		buf = getcwd(buf, 0);
		update_pwd("OLDPWD", find_env_value("PWD"));
		update_pwd("PWD", buf);
		free(buf);
		g_data.return_value = 0;
	}
	else
	{
		printf("bash: cd: %s: No such file or directory\n", curr->argv[1]);
		g_data.return_value = 1;
	}
}