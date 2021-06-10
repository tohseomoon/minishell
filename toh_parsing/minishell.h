/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 18:05:13 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/10 17:55:17 by toh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>

# define BUFFER_SIZE 1024
# define STDIN 0
# define STDOUT 1
# define END 0
# define PIPE 1

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
    struct s_cmd    *next;
    struct s_cmd    *prev;
}                   t_cmd;

typedef struct      s_data
{
    struct s_cmd    *cmd_head;
    struct s_env    *env_head;
    char            **path;
    int             return_value;
}                   t_data;

//utils_string.c
char                *ft_strldup(const char *s1, int n);
char                *ft_strjoin_free_s1(char **s1, char *s2);
int                 ft_strchr_index(const char *s, int c);
size_t              ft_strlen(const char *s);
size_t              ft_strlcpy(char *dest, const char *src, size_t destsize);
char                *ft_strdup(const char *s1);
int                 get_next_line(int fd, char **line);
void                ft_putchar_fd(char c, int fd);
void                ft_putstr_fd(char *s, int fd);
int                 ft_strcmp(char *s1, char *s2);
void                ft_putchar_fd(char c, int fd);
void                ft_putstr_fd(char *s, int fd);
int                 ft_strcmp(char *s1, char *s2);
void	            *ft_memset(void *b, int c, size_t len);
char			    **ft_split(char const *s, char c);

//perse_env.c
int                 parse_env(t_env *env_head, char **envp);
char	            **parse_path(t_data *data);

void	            check_pipe(t_cmd *curr);

//redirection.c
int		            redirection_open_file(t_cmd *curr);

//shell_builtin_fun.c
int		check_shell_builtin(t_cmd *curr);
void	builtin_cmd(t_data *data, t_cmd *curr);

//find_cmd_path.c
int		find_cmd_path(t_data *data, t_cmd *curr);
int		find_cmd_absolute_path(t_data *data, t_cmd *curr);

//구현 함수들
void			    echo(t_data *data, t_cmd *curr);

//setting.c 일단 가동하기 위한 함수 (나중에 삭제 예정)
void    print_env(t_env *env_head);
void	free_data(t_data *data);
void	print_cmd(t_data *data);
void	setting_cmd(t_data *data);

#endif
