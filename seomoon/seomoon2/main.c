/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 14:17:24 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/12 16:25:27 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		exit_minishell(void)
{
	//free_structs();
	exit(0);
}

void		setup(char **envp)
{
	t_env	env_head;

	parse_env(&env_head, envp);
	//signal 처리	
}

void		read_command(char **command, t_env *env_head)
{
	if (get_next_line(STDIN, command) == -1)
		return (-1);
	return (0);
}

char		*find_env_value(t_env *env_head, char *key)
{

}

int			replace_env(t_cmd *cmd, char *command, int j)
{
	int		i;
	int		len;
	char	*key;

	while (command[j] && !is_space(command[j])
			&& command[j] != D_QUOTE)
		len++;
	key = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
		env_key[i++] = command[j++];
	key[i] = '\0';
	cmd->args[index] = find_env_value(env_head, key);
	return (len);
}

int			replace_cmd_out(t_cmd *cmd, char *command, int j)
{
	int		i;
	int		len;
	char	*cmd_in;
	
	while (command[j] && !is_space(command[j])
			&& command[j] != D_QUOTE)
		len++;
	cmd_in = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
		cmd_in[i++] = command[j++];
	cmd_in[i] = '\0';
	cmd->args[index] = execute_cmd_out(cmd_in);
	return (len);
}

int			push_arg(t_cmd *cmd, char *command, int *i, int seperator)
{
	int		j;
	int		len;

	len = 0;
	while (command[len] && command[len] != seperator)
		len++;
	cmd->args[*i] = malloc(sizeof(char) * (len + 1));
	if (cmd->args[*i] == 0)
		return (0);
	j = 0;
	escape = 0;
	while (command[j] && command[j] != seperator)
	{
		if (seperator == D_QUOTE)
		{
			if (command[j] == ESCAPE)
				j++;
			else if (command[j] == '$')
			{
				j += replace_env(cmd, command, ++j);
				break ;
			}
			else if (command[j] == '`')
			{
				j+= replace_cmd_out(cmd, command, ++j);
				if (command[j] != '`')
					exit_shell();
			}
		}
		cmd->args[i][j] = *command;
		j++;
		command++;
	}
	if ((seperator == S_QUOTE || seperator == D_QUOTE) &&
			*command != seperator)
		exit_shell();
	args[i][j] = '\0';
	return (j);
}

void		parse_command(t_cmd *cmd_head, t_env *env_head, char *command)
{
	int		count;
	t_cmd	cmd;
	int		i;

	command = ft_strtrim(command); //is_space 추가하기
	count = count_words(command); //|나 NULL나올 때까지 count하기, is_space 추가하기
	cmd = cmd_head->next;
	cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd->args)
		exit_shell(); //에러 처리 함수 작성하기
	i = 0;
	while (*command)
	{
		if (is_command_end(*command))
			break ;
		if (*command == S_QUOTE)
		{
			command++;
			command += push_arg(cmd->args, command, &i, S_QUOTE);
		}
		else if (*command == D_QUOTE)
		{
			command++;
			command += push_arg(cmd->args, command, &i, D_QUOTE);
		}
		else if (is_space(*command))
			command++;
		else
			command += push_arg(cmd->args, command, &i, SPACE);
	}
	cmd->args[i] = NULL;
}

int			main(int argc, char **argv, char **envp)
{
	char	*command;

	setup();
	while (1)
	{
		//init();
		show_prompt();
		if (read_command(&command, &env_head) == -1)
			break ;
		parse_command(&cmd_head, &env_head, command);
		//execute_command();
	}
	return (0);
}
