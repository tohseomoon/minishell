/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:25:32 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/12 20:13:45 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//parse_utils.c

int			is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int			is_seperator(char c)
{
	if (c == S_QUOTE || c == D_QUOTE)
		return (1);
	else if (is_space(c))
		return (1);
	return (0);
}

char		*ft_strtrim(char *str)
{
	int		begin;
	int		end;
	char	*result;

	if (!str)
		return (NULL);
	while (str[begin] && is_space(str[begin]))
		begin++;
	end = ft_strlen(str + begin);
	if (end)
		while (str[begin + end - 1] && is_space(str[begin + end -1]))
			end--;
	result = malloc(sizeof(char) * (end + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *)(str + begin), end + 1);
	return (result);
}

int			count_words(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!is_seperator(str[i]) &&
				(is_seperator(str[i + 1]) || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

//parse_symbol.c
int			replace_env(t_cmd *curr, char *command, t_env *env_head)
{
	int		i;
	int		len;
	char	*key;

	command++;
	len = 0;
	while (command[len] && !is_space(command[len]) &&
			command[len] != D_QUOTE)
		len++;
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		exit_shell();
	i = 0;
	while (i < len)
		key[i++] = *(command++);
	key[i] = '\0';
	curr->argv[curr->index] = find_env_value(env_head, key);
	return (len);
}

int			replace_back_quote(t_cmd *curr, char *command)
{
	int		i;
	int		len;
	char	*cmd;

	command++;
	len = 0;
	while (command[len] && command[len] != '`')
		len++;
	if (command[len] != '`')
		exit_shell();
	cmd = malloc(sizeof(char) * (len + 1));
	if (!cmd)
		exit_shell();
	i = 0;
	while (i < len)
		cmd[i++] = *(command++);
	cmd[i] = '\0';
	curr->argv[curr->index] = execute_cmd(cmd);
	return (len);
}

int			replace_path_home(t_cmd *curr, t_env *env_head)
{
	curr->argv[curr->index] = find_env_value(env_head, "HOME");
	return (ft_strlen(curr->argv[curr->index]));
}

int			is_symbol(char c)
{
	if (c == '$' || c == '`' || c == '~')
		return (1);
	return (0);
}

int			handle_symbol(t_cmd *curr, char *command, t_env *env_head)
{
	int		i;

	i = 0;
	if (command[i] == '$')
		i += replace_env(curr, command, env_head);
	else if (command[i] == '`')
		i += replace_cmd_out(curr, command);
	else if (command[i] == '~')
		i += replace_path_home(curr, env_head);
	return (i);
}

//parse_quote.c
int			handle_single_quote(t_cmd *curr, char *command)
{
	int		len;
	int		j;

	command++;
	len = 0;
	while (command[len] && command[len] != S_QUOTE)
		len++;
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (curr->argv[curr->index] == 0)
		return (-1);
	j = 0;
	while (*command && *command != S_QUOTE)
	{
		curr->argv[curr->index][j] = *command;
		j++;
		command++;
	}
	if (*command != S_QUOTE)
		exit_shell();
	curr->argv[curr->index][j] = '\0';
	curr->index++;
	return (j);
}

int			handle_doulbe_quote(t_cmd *curr, char *command, t_env *env_head)
{
	int		j;
	int		len;

	command++;
	len = 0;
	while (command[len] && command[len] != D_QUOTE)
		len++;
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (curr->argv[curr->index] == 0)
		return (-1);
	j = 0;
	while (*command && *command != D_QUOTE)
	{
		if (*command == ESCAPE)
			command++;
		else if (is_symbol(*command))
			command += handle_symbol(curr, command, env_head);
		curr->argv[curr->index][j] = *command;
		j++;
		command++;
	}
	if (*command != D_QUOTE)
		exit_shell();
	curr->argv[curr->index][j] = '\0';
	curr->index++;
	return (j);
}

int			split_command(t_cmd *curr, char *command, t_env *env_head)
{
	curr->index = 0;
	while (!is_command_end(*command))
	{
		if (is_single_quote(*command))
			command += handle_single_quote(curr, command);
		else if (is_double_quote(*command))
			command += handle_double_quote(curr, command, env_head);
		else
		{
			if (is_symbol(*command))
			{
				command += handle_symbol(curr, command, env_head);
				curr->index++;
			}
			else
				command += push_arg(curr, command); //curr->index++;
		}
	}
	curr->argv[curr->index] = NULL;
	return (i);
}

void		parse_command(t_cmd *cmd_head, char *command, t_env *env_head)
{
	int		i;
	t_cmd	*curr;

	cmd_head->next = malloc(sizeof(t_cmd));
	curr = cmd_head->next;
	i = 0;
	while (command[i] != '\0')
	{
		command = ft_strtrim(command + i);
		curr->argc = count_words(command);
		curr->argv = malloc(sizeof(char *) * (curr->argc + 1));
		i += split_command(curr, command, env_head);
		if (command[i] == '|')
		{
			curr->next = malloc(sizeof(t_cmd));
			curr = curr->next;
		}
		else if (command[i] == '\0')
			curr->next = NULL;
	}
}
