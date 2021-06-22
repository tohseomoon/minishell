#include "minishell.h"

size_t		ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t		ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	cnt;

	if (dest == 0 || src == 0)
		return (0);
	cnt = 0;
	while (cnt + 1 < destsize && src[cnt] != 0)
	{
		dest[cnt] = src[cnt];
		cnt++;
	}
	if (destsize != 0)
		dest[cnt] = 0;
	while (src[cnt])
		cnt++;
	return (cnt);
}

char		*ft_strdup(const char *s1)
{
	int		str_len;
	char	*str;

	if (s1 == 0)
		return (0);
	str_len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str == 0)
		return (0);
	ft_strlcpy(str, s1, str_len + 1);
	return (str);
}

char		*ft_strldup(const char *s1, int n)
{
	int		str_len;
	char	*str;

	str_len = ft_strlen(s1);
	if (n > str_len + 1)
		return (0);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == 0)
		return (0);
	ft_strlcpy(str, s1, n);
	str[n] = 0;
	return (str);
}