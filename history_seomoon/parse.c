/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:25:32 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/15 00:03:40 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void		exit_shell(char *message) //temporary
{
	printf("%s\n", message);
	exit(1);
}

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

int			is_command_end(char c)
{
	if (c == '\0' || c == '|')
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
	begin = 0;
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
	int		count;

	i = 0;
	count = 0;
	while (str[i] && !is_command_end(str[i]))
	{
		if (!is_seperator(str[i]) &&
				(is_seperator(str[i + 1]) || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

//parse_symbol.c
char		*find_env_value(t_env *env_head, char *key)
{
	t_env	*curr;

	curr = env_head->next;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	exit_shell("find_env_value(): cannot find matching value. ");
	return (NULL);
}

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
		exit_shell("replace_env(): fail to allocate. ");
	i = 0;
	while (i < len)
	{
		key[i] = command[i];
		i++;
	}
	key[i] = '\0';
	// 메모리 누수 가능성 있음
	curr->argv[curr->index] = find_env_value(env_head, key);
	return (len + 1);
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
		exit_shell("Back quote not closed. ");
	cmd = malloc(sizeof(char) * (len + 1));
	if (!cmd)
		exit_shell("replace_back_quote(): fail to allocate. ");
	i = 0;
	while (i < len)
		cmd[i++] = *(command++);
	cmd[i] = '\0';
	curr->argv[curr->index] = cmd; // execute_cmd(cmd);
	return (len + 2);
}

/*
int			replace_path_home(t_cmd *curr, t_env *env_head)
{
	curr->argv[curr->index] = find_env_value(env_head, "HOME");
	return (ft_strlen(curr->argv[curr->index]));
}
*/

int			is_symbol(char c)
{
	if (c == '$' || c == '`')
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
		i += replace_back_quote(curr, command);
	curr->index++;
	return (i);
}

int			push_arg(t_cmd *curr, char *command)
{
	int		i;
	int		len;

	len = 0;
	while (command[len] && !is_seperator(command[len]))
		len++;
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (!curr->argv[curr->index])
		exit_shell("push_arg(): Fail to allocate. ");
	i = 0;
	while (*command && !is_seperator(*command))
	{
		curr->argv[curr->index][i] = *command;
		i++;
		command++;
	}
	curr->argv[curr->index][i] = '\0';
	curr->index++;
	return (i);
}

int			push_arg_quote(t_cmd *curr, char *command, char quote)
{
	int		i;
	int		len;

	len = 0;
	while (command[len] && command[len] != quote)
		len++;
	curr->argv[curr->index] = malloc(sizeof(char) * (len + 1));
	if (!curr->argv[curr->index])
		exit_shell("push_arg_quote(): Fail to allocate. ");
	i = 0;
	while (*command && *command != quote)
	{
		curr->argv[curr->index][i] = *command;
		i++;
		command++;
	}
	curr->argv[curr->index][i] = '\0';
	curr->index++;
	return (i);
}

//parse_quote.c
int			handle_single_quote(t_cmd *curr, char *command)
{
	int		j;

	command++;
	j = 0;
	while (command[j] && command[j] != S_QUOTE)
		j += push_arg_quote(curr, command, S_QUOTE);
	if (command[j] != S_QUOTE)
		exit_shell("Single quote not closed. ");
	return (j + 2);
}

int			handle_double_quote(t_cmd *curr, char *command, t_env *env_head)
{
	int		i;

	command++;
	i = 0;
	while (command[i] && command[i] != D_QUOTE)
	{
		if (command[i] == ESCAPE)
		{
			i++;
			i += push_arg_quote(curr, command + i, D_QUOTE);
		}
		else if (is_symbol(command[i]))
			i += handle_symbol(curr, command + i, env_head);
		else
			i += push_arg_quote(curr, command + i, D_QUOTE);
	}
	if (command[i] != D_QUOTE)
		exit_shell("Double quote not closed. ");
	return (i + 2);
}

int			split_command(t_cmd *curr, char *command, t_env *env_head)
{
	int		i;

	i = 0;
	curr->index = 0;
	while (command[i] && !is_command_end(command[i]))
	{
		if (command[i] == S_QUOTE)
			i += handle_single_quote(curr, command + i);
		else if (command[i] == D_QUOTE)
			i += handle_double_quote(curr, command + i, env_head);
		else if (is_symbol(command[i]))
			i += handle_symbol(curr, command + i, env_head);
		else
			i += push_arg(curr, command + i);
		while (command[i] && is_space(command[i]))
			i++;
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
		i = split_command(curr, command, env_head);
		if (command[i] == '|')
		{
			curr->next = malloc(sizeof(t_cmd));
			curr = curr->next;
			i++;
		}
	}
	curr->next = NULL;
}

int			read_command(char **command, t_env *env_head)
{
	if (get_next_line(STDIN, command) == -1)
		return (-1);
	return (0);
}

void		show_prompt(void)
{
	ft_putstr_fd("[minishell]$ ", STDOUT);
}

void		print_command(t_cmd *cmd_head)
{
	int		i;
	t_cmd	*curr;

	i = 0;
	curr = cmd_head->next;
	while (curr)
	{
		i = 0;
		while (i < curr->argc)
		{
			printf("argv[%d]: %s\n", i, curr->argv[i]);
			i++;
		}
		curr = curr->next;
	}
}

/*
int			main(int argc, char **argv, char **envp)
{
	char	*command;
	t_env	env_head;
	t_cmd	cmd_head;

	parse_env(&env_head, envp);
	while (1)
	{
		show_prompt();
		if (read_command(&command, &env_head) == -1)
			exit_shell("Fail to read command line. ");
		parse_command(&cmd_head, command, &env_head);
		free(command);
		print_command(&cmd_head);
	}
	return (0);
}
*/

int			main(int argc, char **argv, char **envp)
{
	char		*command;
	t_cmd		cmd_head;
	t_env		env_head;

	parse_env(&env_head, envp);
	while (1)
	{
		command = readline("[minishell]$ ");
		if (!command)
			break ;
		if (ft_strcmp(command, "exit") == 0)
		{
			free(command);
			break ;
		}
		add_history(command);
		parse_command(&cmd_head, command, &env_head);
		free(command);
		print_command(&cmd_head);
	}
}
