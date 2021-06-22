#include "minishell.h"

char		*ft_strjoin_free_s1(char **s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	char	*result;

	if (*s1 == 0 || s2 == 0)
	{
		free(*s1);
		*s1 = 0;
		return (0);
	}
	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == 0)
	{
		free(*s1);
		*s1 = 0;
		return (0);
	}
	ft_strlcpy(result, *s1, s1_len + 1);
	ft_strlcpy(result + s1_len, s2, s2_len + 1);
	free(*s1);
	*s1 = 0;
	return (result);
}

static int		count_arr(char const *s, char c)
{
	int		cnt;
	int		i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	cnt = 0;
	while (s[i])
	{
		cnt++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (cnt);
}

static void		free_str(char **result, int i)
{
	i--;
	while (i >= 0)
	{
		free(result[i]);
		result[i] = 0;
		i--;
	}
}

static char		**split_str(char **result, int arrcnt, char const *s, char c)
{
	int		i;
	int		word_cnt;
	char	*begin;

	i = 0;
	while (i < arrcnt)
	{
		while (*s == c)
			s++;
		begin = (char *)s;
		word_cnt = 0;
		while (*s && *s != c)
		{
			word_cnt++;
			s++;
		}
		result[i] = ft_strldup(begin, word_cnt + 1);
		if (result[i] == 0)
		{
			free_str(result, i);
			return (0);
		}
		i++;
	}
	return (result);
}

char			**ft_split(char const *s, char c)
{
	int		arr_cnt;
	char	**result;
	char	**tmp;

	if (s == 0)
		return (0);
	arr_cnt = count_arr(s, c);
	result = (char **)malloc(sizeof(char *) * (arr_cnt + 1));
	if (result == 0)
		return (0);
	result[arr_cnt] = 0;
	tmp = split_str(result, arr_cnt, s, c);
	if (tmp == 0)
	{
		free(result);
		result = 0;
	}
	return (result);
}