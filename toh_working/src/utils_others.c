/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 21:15:58 by toh               #+#    #+#             */
/*   Updated: 2021/06/23 11:19:29 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		*ft_memset(void *b, int c, size_t len)
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

int			get_len(long n)
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

char		*ft_itoa(int n)
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

char		*ft_strtrim(char *str)
{
	int		begin;
	int		end;
	char	*result;

	if (!str)
		return (NULL);
	begin = 0;
	while (str[begin] && is_space(str[begin]))
		begin++;
	end = ft_strlen(str + begin);
	if (end)
		while (str[begin + end - 1] && is_space(str[begin + end - 1]))
			end--;
	result = malloc(sizeof(char) * (end + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *)(str + begin), end + 1);
	return (result);
}

void	print_cmd(void)
{
	t_cmd 	*curr;
	int		i;
	
	curr = g_data.cmd_head->next;
	while (curr)
	{
		i = 0;
		printf("==============================\n");
		printf("argc : %d\n", curr->argc);
		while (curr->argv[i])
		{
			printf("[argv[%d] : %s]\n", i, curr->argv[i]);
			i++;
		}
		printf("index : %d\n", curr->index);
		printf("pipe[0] : %d\n", curr->pipe[0]);
		printf("pipe[1] : %d\n", curr->pipe[1]);
		printf("h_pipe[0] : %d\n", curr->heredoc_pipe[0]);
		printf("h_pipe[1] : %d\n", curr->heredoc_pipe[1]);
		printf("h_flag : %d\n", curr->heredoc);
		printf("type : %d\n", curr->type);
		printf("fd_in : %d\n", curr->fd_in);
		printf("fd_out : %d\n", curr->fd_out);
		printf("==============================\n");
		curr = curr->next;
	}
}