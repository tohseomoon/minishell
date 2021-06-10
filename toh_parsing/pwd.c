#include "minishell.h"

void	pwd(t_data *data, t_cmd *curr)
{
	char	*buf;
	
	buf = 0;
	buf = getcwd(buf, 0);
	write(1, buf, sizeof(buf));
	write(1, "\n", 1);
	data->return_value = 0;
}