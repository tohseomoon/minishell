/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 18:05:13 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/04 20:03:24 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 1024
# define STDIN 0
# define STDOUT 1
# define LEFT_REDIR 5
# define RIGHT_REDIR 6
# define DOUBLE_REDIR 7
# define PIPE 8

typedef struct      s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}                   t_env;

typedef struct      s_cmd      
{
    char            **argv;
    int             argc;
    int             pipe[2];
    int             fd_in;
    int             fd_out;
    int             type;
    struct s_cmd    *next;
}                   t_cmd;


char	            *ft_strldup(const char *s1, int n);

int                 parse_env(t_env *env_head, char **env);
void                print_env(t_env *env_head);

char	            *ft_strjoin_free_s1(char **s1, char *s2);
int		            ft_strchr_index(const char *s, int c);

size_t	            ft_strlen(const char *s);
size_t	            ft_strlcpy(char *dest, const char *src, size_t destsize);
char	            *ft_strdup(const char *s1);

int			        get_next_line(int fd, char **line);

void	            ft_putchar_fd(char c, int fd);
void	            ft_putstr_fd(char *s, int fd);
int		            ft_strcmp(char *s1, char *s2);

void	            ft_putchar_fd(char c, int fd);
void	            ft_putstr_fd(char *s, int fd);
int		            ft_strcmp(char *s1, char *s2);

#endif
