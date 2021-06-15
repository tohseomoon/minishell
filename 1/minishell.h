/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:28:55 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/15 15:13:31 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h> //check

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
	int				new_env;
	int				equal;
	struct s_env	*next;
}					t_env;

typedef struct		s_cmd
{
	char			**argv;
	int				argc;
	int				index;
	int				pipe[2];
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_data
{
	struct s_cmd	*cmd_head;
	struct s_env	*env_head;
	char			**path;
	char			**old_env;
	char			**new_env;
	int				return_value;
	int				running;
}					t_data;

t_data				g_data;

void				exit_shell(char *message);
void				parse_command(char *command);
int					handle_single_quote(t_cmd *curr, char *command);
int					handle_double_quote(t_cmd *curr, char *command);
int					handle_symbol(t_cmd *curr, char *command);
int					is_space(char c);
int					is_seperator(char c);
int					is_command_end(char c);
int					is_symbol(char c);
int					parse_env(char **env);
void				print_env(void);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dest, const char *src, size_t destsize);
char				*ft_strdup(const char *s1);
char				*ft_strldup(const char *s1, int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strjoin_free_s1(char **s1, char *s2);
int					ft_strchr_index(const char *s, int c);
char				*ft_strtrim(char *str);
void				*ft_memset(void *b, int c, size_t len);
char				**ft_split(char const *s, char c);
int					parse_env(char **envp);
char				**parse_path(void);

#endif
