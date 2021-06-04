# define STDIN		0
# define STDOUT		1
#include "get_next_line.h"
#include <stdio.h>

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

void	exit_minishell(void)
{
	exit(0);
}

void	show_prompt(void)
{
	ft_putstr_fd("minishell$ ", STDOUT);
}

int	get_input(char **input)
{
	int	result;

	result = get_next_line(STDIN, input);
	if (ft_strcmp(*input, "exit") == 0)
	{
		free(*input);
		printf("exit\n");
		exit_minishell();
		return (0);
	}
	free(*input);
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	char 	*input;
	int	result;

	result = 1;
	while (result)
	{
		show_prompt();
		result = get_input(&input);
	}
}
