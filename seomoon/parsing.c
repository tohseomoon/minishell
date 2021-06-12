/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:25:09 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/12 12:12:01 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include<stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char	*ptr_s;

	ptr_s = (char *)s;
	while (1)
	{
		if (*ptr_s == c)
			return (ptr_s);
		if (*ptr_s == '\0')
			break ;
		ptr_s++;
	}
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		begin;
	int		end;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	while (s1[begin] && ft_strchr(set, s1[begin]))
		begin++;
	end = ft_strlen(s1 + begin);
	if (end)
		while (s1[begin + end - 1] && ft_strchr(set, s1[begin + end - 1]))
			end--;
	str = (char *)malloc(sizeof(char) * (end + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)(s1 + begin), end + 1);
	return (str);
}


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

	count = count_words(str, sep);
	split_strs = malloc(sizeof(char *) * (count + 1));
	if (!split_strs)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			str += push_str(split_strs, str, '\'', i);
			if (*str == '\'')
				str++;
			else //에러처리해주기
				exit(1); //return (NULL);
			i++;
		}
		else if (*str == '\"')
		{
			str++;
			str += push_str(split_strs, str, '\"', i);
			if (*str == '\"')
				str++;
			else
				exit(1);
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

char		*replace_env(char *str, t_env *env_head)
{
	t_env	*curr;

	curr = env_head->next;
	while (curr)
	{
		if (ft_strcmp(curr->key, str + 1) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

void		parse_input(t_cmd *cmd_head, t_env *env_head, char *input)
{
	int		i;
	char	**split_strs;

	input = ft_strtrim(input, " ");
	split_strs = ft_split(input, ' ');
	//각 문자열이 싱글쿼트로 감싸진 문자열인지 더블쿼트로 감싸진 문자열인지 구분이 필요함
	//싱글쿼트인 경우 전부 문자열로 인식
	//더블쿼트인 경우 $, \, `를 메타문자로 인식해 따로 처리해줘야 함
	//빈 문자열은 토큰이 만들어질 수 없음 ("", '' -> 무시하고 넘어가야함)
	
	//escape 문자 처리 (escape 뒤의 quote, escape 등은 문자로 인식)
	//$환경변수 문자열로 치환하기
	//백쿼터(`)로 감싸진 문자열은 명령어로 처리
	//파이프/ NULL 단위로 잘라서 cmd 구조체->argv 배열에 저장
	//NULL인 경우 next = NULL, NULL이 아닌 경우 next = 다음 cmd구조체 포인터
	i = 0;
	while (split_strs[i])
	{
		if (split_strs[i][0] == '$')
		{
			split_strs[i] = replace_env(split_strs[i], env_head);
			if (split_strs[i] == NULL)
				exit(1); //에러 처리 추가하기
		}
		printf("%s\n", split_strs[i]);
		i++;
	}
}

/*
int		main(int argc, char **argv)
{
	//t_cmd	cmd_head;
	char	*input;
	char	**split_strs;
	int	i;

	if (argc != 2)
		return (0);
	//parse_input(&cmd_head, input);
	split_strs = ft_split(argv[1], ' ');
	i = 0;
	while (split_strs[i])
	{
		printf("split_strs[%d]: %s\n", i, split_strs[i]);
		i++;
	}
	printf("%s\n", argv[1]);
	printf("%d\n", i);
}
*/

