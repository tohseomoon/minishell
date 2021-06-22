/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 18:05:13 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/15 14:34:15 by toh              ###   ########.fr       */
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
    int             new;
    int             equal;
    struct s_env    *next;
}                   t_env;

typedef struct      s_cmd      
{
    char            **argv;
    int             argc;
    int             pipe[2];
    int             heredoc_pipe[2];//임시
    int             heredoc; //임시
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
    char            **old_env;
    char            **new_env;
    int             return_value;
    int             runnig;
}                   t_data;

t_data		g_data;

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
char	            **parse_path();

void	            check_pipe(t_cmd *curr);

//redirection.c
int		            redirection_open_file(t_cmd *curr);

//shell_builtin_fun.c
int		check_shell_builtin(t_cmd *curr);
void	builtin_cmd(t_cmd *curr);
int		check_shell_builtin_fork(t_cmd *curr);
void	builtin_cmd_fork(t_cmd *curr);

//find_cmd_path.c
int		find_cmd_path(t_cmd *curr);
int		find_cmd_absolute_path(t_cmd *curr);

//구현 함수들
void			    echo(t_cmd *curr);
void	ft_exit(t_cmd *curr);
void	env();

//export_utils.c
char	**arr_env_string();
void	print_sort_env();

//setting.c 일단 가동하기 위한 함수 (나중에 삭제 예정)
void    print_env(t_env *env_head);
void	free_data();
void	print_cmd();
void	setting_cmd();

void	heredoc(t_cmd *curr, int i, int fd);
void    heredoc_cmd(t_cmd *curr, int i);

#endif
