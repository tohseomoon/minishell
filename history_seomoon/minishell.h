/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:28:55 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/13 12:56:41 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include<stdio.h>

# define STDIN	0
# define STDOUT	1
# define BUFFER_SIZE 1024

# define S_QUOTE '\''
# define D_QUOTE '\"'
# define ESCAPE  '\\'

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_cmd
{
	char			**argv;
	int				argc;
	int				index;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_data
{
	struct s_cmd	*cmd_head;
	struct s_env	*env_head;
}					t_data;


// env
int                 parse_env(t_env *env_head, char **env);
void                print_env(t_env *env_head);

// get_next_line, utils
size_t              ft_strlen(const char *s);
size_t              ft_strlcpy(char *dest, const char *src, size_t destsize);
char                *ft_strdup(const char *s1);
char                *ft_strldup(const char *s1, int n);
void                ft_putchar_fd(char c, int fd);
void                ft_putstr_fd(char *s, int fd);
int                 ft_strcmp(char *s1, char *s2);
char                *ft_strjoin_free_s1(char **s1, char *s2);
int                 ft_strchr_index(const char *s, int c);
int                 get_next_line(int fd, char **line);

#endif
