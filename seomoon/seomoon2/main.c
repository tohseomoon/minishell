
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
	while (*command)
	{
		if (is_single_quote(*command))
		{
			command++;
		}
		else if (is_double_quote(*command))
		{
			command++;

		}
		else if (is_space(*command))
			command++;
		else
		{

		}
	}
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
