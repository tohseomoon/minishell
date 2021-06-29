#include "minishell.h"

void		symbol_str(t_token_util *utils, char symbol)
{
	int		flag;

	flag = 1;
	nomal_str(utils);
	while (*(utils->str) == symbol)
	{
		(utils->str)++;
		(utils->cnt)++;
	}
	utils->cmd = ft_strldup(utils->str - utils->cnt, utils->cnt + 1);
	if (utils->cmd[0] == '|' || utils->cmd[0] == ';')
		flag = 2;
	new_token(utils->cmd, flag);
	free(utils->cmd);
	utils->cmd = 0;
	utils->cnt = 0;
}
