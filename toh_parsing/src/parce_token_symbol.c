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

int			handle_quotes_error(int quote)
{
	if (quote == S_QUOTE)
		printf("minishell: single quotes not properly closed\n");
	else if (quote == D_QUOTE)
		printf("minishell: double quotes not properly closed\n");
	else if (quote == B_QUOTE)
		printf("minishell: back quotes not properly closed\n");
	return (-1);
}

int		single_quote_str(t_token_util *utils, char quote, char **quote_str)
{
	while (*(utils->str) != quote)
	{
		if (*(utils->str) == 0)
			return (handle_quotes_error(quote));
		(utils->str)++;
		(utils->cnt)++;
	}
	*quote_str = ft_strldup(utils->str - utils->cnt, utils->cnt + 1);
	utils->cnt = 0;
	return (0);
}

int		double_quote_str(t_token_util *utils, char quote, char **quote_str)
{
	while (*(utils->str) != quote)
	{
		if (*(utils->str) == '$')
		{
			env_str(utils);
			(utils->str)--;
			(utils->cnt)--;
		}
		if (*(utils->str) == 0)
			return (handle_quotes_error(quote));
		(utils->str)++;
		(utils->cnt)++;
	}
	*quote_str = ft_strldup(utils->str - utils->cnt, utils->cnt + 1);
	utils->cnt = 0;
	return (0);
}

int		quote_str(t_token_util *utils, char quote)
{
	char	*quote_str;
	
	quote_str = 0;
	make_tmp_str(utils);
	(utils->str)++;
	if (quote == S_QUOTE || quote == B_QUOTE)
	{
		if (single_quote_str(utils, quote, &quote_str) == -1)
			return (-1);
	}
	else if (quote == D_QUOTE)
	{
		if (double_quote_str(utils, quote, &quote_str) == -1)
			return (-1);
	}
	join_tmp_str(utils, quote_str);
	return (0);
}