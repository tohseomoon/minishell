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

	result = -1;
	if (command == 0 || (command[0] == '~' && command[1] == 0))
		path = ft_strdup(find_env_value("HOME"));
	else if (command[0] == '-' && command[1] == 0)
	{
		path = ft_strdup(find_env_value("OLDPWD"));
		if (path != 0)
			printf("%s\n", path);
		else
			result = -2;
	}
	else
		path = ft_strdup(command);
	if (path != 0)
	{
		result = chdir(path);
		free(path);
	}
	path = 0;
	return (result);
}

static void	add_env(char *key, char *value)
{
	t_env	*tmp;
	t_env	*curr;

	curr = g_data.env_head->next;
	while (curr->next)
		curr = curr->next;
	tmp = (t_env *)malloc(sizeof(t_env));
	if (tmp == 0)
		printf("Error_allocate\n");
	curr->next = tmp;
	curr->key = ft_strdup(key);
	curr->value = ft_strdup(value);
	curr->next = 0;
}

static void		update_pwd(char *key, char *new_value)
{
	t_env	*curr;
	int		flag;

	flag = 0;
	curr = g_data.env_head->next;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
		{
			free(curr->value);
			curr->value = ft_strdup(new_value);
			flag = 1;
			break ;
		}
		curr = curr->next;
	}
	if (flag == 0)
		add_env(key, new_value);
}

void	ft_cd(t_cmd *curr)
{
	char	*buf;

	buf = 0;
	int		result;

	result = change_directory(curr->argv[1]);
	g_data.return_value = 1;
	if (result == 0)
	{
		buf = getcwd(buf, 0);
		update_pwd("OLDPWD", find_env_value("PWD"));
		update_pwd("PWD", buf);
		free(buf);
		g_data.return_value = 0;
	}
	else if (result == -1)
		printf("minishell: cd: HOME not set\n");
	else if (result == -2)
		printf("minishell: cd: OLDPWD not set\n");
	else
		printf("minishell: %s: %s\n", curr->argv[1], strerror(errno));
}