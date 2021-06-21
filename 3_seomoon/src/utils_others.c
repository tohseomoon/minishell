#include "minishell.h"

void		ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void		ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

int		get_len(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*nbr;
	long	ln;

	ln = n;
	len = get_len(ln);
	nbr = (char *)malloc(sizeof(char) * (len + 1));
	if (!nbr)
		return (NULL);
	nbr[len--] = '\0';
	if (ln == 0)
		nbr[len] = '0';
	if (ln < 0)
	{
		nbr[0] = '-';
		ln *= -1;
	}
	while (ln > 0)
	{
		nbr[len] = (ln % 10) + '0';
		ln /= 10;
		len--;
	}
	return (nbr);
}