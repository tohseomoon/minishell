/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:25:09 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/10 16:42:44 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include<stdio.h>

int		is_seperator(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

int		is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int		count_words(char *str, char sep)
{
	int	i;
	int	count;
	char	quote;
	int	len;

	i = 0;
	count = 0;
	len = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				len++;
				i++;
			}
		}
		if (!is_seperator(str[i], sep) &&
				(is_seperator(str[i + 1], sep) || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int		push_str(char **split_strs, char *str, char sep, int i)
{
	int	j;
	int	len;

	len = 0;
	while (!is_seperator(str[len], sep) && str[len])
		len++;
	split_strs[i] = malloc((len + 1) * sizeof(char));
	if (split_strs[i] == 0)
		return (0);
	j = 0;
	while (!is_seperator(*str, sep) && *str)
	{
		split_strs[i][j] = *str;
		j++;
		str++;
	}
	split_strs[i][j] = '\0';
	return (j);
}

char		**ft_split(char *str, char sep)
{
	char	**split_strs;
	int	i;
	int	j;
	int	count;
	char	quote;

	count = count_words(str, sep);
	split_strs = malloc(sizeof(char *) * (count + 1));
	if (!split_strs)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (is_quote(*str))
		{
			quote = *str;
			str++;
			j = push_str(split_strs, str, quote, i);
			str += (j + 1);
			i++;
		}
		else if (is_seperator(*str, sep))
			str++;
		else
		{
			j = push_str(split_strs, str, sep, i);
			str += j;
			i++;
		}

	}
	split_strs[i] = NULL;
	return (split_strs);
}

void		parse_input(t_cmd *cmd_head, char *input)
{
	int		i;
	char	**split_strs;

	split_strs = ft_split(input, ' ');
	//각 문자열이 싱글쿼트로 감싸진 문자열인지 더블쿼트로 감싸진 문자열인지 구분이 필요함
	//싱글쿼터인 경우 전부 문자열로 인식
	//더블쿼터인 경우 $, \, `를 메타문자로 인식해 따로 처리해줘야 함
	//빈 문자열은 토큰이 만들어질 수 없음 ("", '' -> 무시하고 넘어가야함)
	while (split_strs[i])
	{
		//escape 문자 처리 (escape 뒤의 quote, escape 등은 문자로 인식)
		//$환경변수 문자열로 치환하기
		//백쿼터(`)로 감싸진 문자열은 명령어로 처리
		//파이프/ NULL 단위로 잘라서 cmd 구조체->argv 배열에 저장
		//NULL인 경우 next = NULL, NULL이 아닌 경우 next = 다음 cmd구조체 포인터
	}
}

/*
int		main()
{
	//t_cmd	cmd_head;
	char	*input;
	char	**split_strs;
	int	i;

	input = "ls        -la > a         >> b | grep \"          a\" ; pwd";
	//parse_input(&cmd_head, input);
	split_strs = ft_split(input, ' ');
	i = 0;
	while (split_strs[i])
	{
		printf("split_strs[%d]: %s\n", i, split_strs[i]);
		i++;
	}
	printf("%s\n", input);
	printf("%d\n", i);
}
*/
