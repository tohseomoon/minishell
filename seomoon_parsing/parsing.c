/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:25:09 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/05 19:00:13 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

# define DOUBLE_QUATER 2
# define SINGLE_QUATER 1

int		is_seperator(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

char		is_quater(char c)
{
	if (c == '\"')
		return (DOUBLE_QUATER);
	else if (c == '\'')
		return (SINGLE_QUATER);
	return (0);
}

int		skip_string_arg(char *str, int *i, char quater)
{

}

int		count_words(char *str, char sep)
{
	int	i;
	int	count;
	int	flag;
	int	quater;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		if (quater = is_quater(str[i]))
		{
			skip_string_arg(str, &i, quater);
			count++;
		}
		i++;
	}
}

char		**ft_split(char *str, char sep)
{
	char	**split_strs;
	int	i;
	int	j;
	int	count;

	count = count_words(str, sep);
}

int		parse_input(t_cmd *cmd_head, char *input)
{
	/*
	1. input(입력된 커맨드라인)을 스페이스 기준으로 쪼개기
	2. 이 때, 따옴표 안의 스페이스는 문자열로 처리함
	3. 쪼갠 인자들을 2차원 배열(문자열 포인터 배열)에 저장하기
	*/
	int	i;

	i = 0;
	while (input[i])
	{
		
	}
}

int		main()
{
	t_cmd	cmd_head;
	char	*input;

	input = "ls        -la > a         >> b | grep \"          a\" ; pwd";
	parse_input(&cmd_head, input);
}