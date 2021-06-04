/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 18:05:13 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/04 18:59:43 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef "MINISHELL_H"
# define "MINISHELL_H"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFFER_SIZE 1024
# define STDIN 0
# define STDOUT 1

typedef struct      s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}                   t_env;


char	            *ft_strldup(const char *s1, int n);

int                 parse_env(t_env *env_head, char **env);
void                print_env(t_env *env_head);

char	            *ft_strjoin_free_s1(char **s1, char *s2);
int		            ft_strchr_index(const char *s, int c);

size_t	            ft_strlen(const char *s);
size_t	            ft_strlcpy(char *dest, const char *src, size_t destsize);
char	            *ft_strdup(const char *s1);

int			        get_next_line(int fd, char **line)

#endif
