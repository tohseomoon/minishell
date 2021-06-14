#include "minishell.h"

static void		print_echo_argv(t_cmd *curr, int n_flag)
{
	int		i;

	if (n_flag == 1)
		i = 2;
	else
		i = 1;
	while (curr->argv[i])
	{
		write(1, curr->argv[i], ft_strlen(curr->argv[i]));
		if (curr->argv[i + 1] != 0)
			write(1, " ", 1);
		i++;
	}
}

void			echo(t_data *data, t_cmd *curr)
{
	int		n_flag;
	int		i;

	n_flag = 0;
	if (curr->argc == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	if (curr->argv[1][0] == '-' && curr->argv[1][1] == 'n')
	{
		n_flag = 1;
		i = 1;
		while (curr->argv[1][++i])
		{
			if (curr->argv[1][i] != 'n')
				n_flag = 0;
		}	
	}
	print_echo_argv(curr, n_flag);
	if (n_flag == 0)
		write(1, "\n", 1);
	data->return_value = 0;
}