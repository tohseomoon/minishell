#include "minishell.h"

static int			handle_quotes_error(int quote)
{
	if (quote == S_QUOTE)
		printf("minishell: single quotes not properly closed\n");
	else if (quote == D_QUOTE)
		printf("minishell: double quotes not properly closed\n");
	else if (quote == B_QUOTE)
		printf("minishell: back quotes not properly closed\n");
	else if (quote == ESCAPE)
		printf("minishell: escape not properly closed\n");
	return (-1);
}

static int		single_quote_str(t_token_util *utils, char quote, char **quote_str)
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

static char	*del_escape(t_token_util *utils)
{
	char	*str;
	char	*cut_str;
	int		i;
	int		j;
	
	str = ft_strldup(utils->str - utils->cnt, utils->cnt + 1);
	cut_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (cut_str == 0)
		exit_shell();
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\\' || str[i + 1] == '\"' || str[i + 1] == '$'))
			i++;
		cut_str[j] = str[i];
		i++;
		j++;
	}
	cut_str[j] = 0;
	free(str);
	return (cut_str);
}

static int		double_quote_str(t_token_util *utils, char quote, char **quote_str)
{
	while (*(utils->str) != quote)
	{
		if (*(utils->str) == '\\' && *((utils->str) + 1) == quote && *((utils->str) + 2) == 0)
			return (handle_quotes_error(ESCAPE));
		else if (*(utils->str) == '\\' && (*((utils->str) + 1) == '\\' || *((utils->str) + 1) == '\"' || *((utils->str) + 1) == '$'))
		{
			(utils->str) += 1;
			(utils->cnt) += 1;
		}
		if (*(utils->str) == '$' && *((utils->str) - 1) != '\\')
		{
			quote_env_str(utils);
			(utils->str)--;
			(utils->cnt)--;
		}
		if (*(utils->str) == 0)
			return (handle_quotes_error(quote));
		(utils->str)++;
		(utils->cnt)++;
	}
	*quote_str = del_escape(utils);
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