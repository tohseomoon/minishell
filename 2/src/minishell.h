/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:28:55 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/22 15:45:34 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <stdio.h>

# define S_QUOTE '\''
# define D_QUOTE '\"'
# define B_QUOTE '`'
# define ESCAPE  '\\'

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				equal;
	struct s_env	*next;
}					t_env;

typedef struct		s_cmd
{
	char			**argv;
	int				argc;
	int				index;
	int				pipe[2];
	int				heredoc_pipe[2];
	int				heredoc;
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
	char			**env;
	int				return_value;
	int				running;
}					t_data;

t_data				g_data;

void				check_pipe(t_cmd *curr);
void				execute_command(char **envp);

int					find_cmd_path(t_cmd *curr);
int					find_cmd_absolute_path(t_cmd *curr);

void				free_cmd_list(void);
void				free_all(void);
void				free_path(void);

void				ft_cd(t_cmd *curr);

void				ft_echo(t_cmd *curr);

void				ft_env(void);

void				ft_exit(t_cmd *curr);

char				**arr_env_string(void);
void				print_sort_env(void);

void				ft_export_fork(void);

int					key_isallowed(char *str);
int					add_path(t_env *curr, char *str);
void				creat_add_env(t_cmd *curr, t_env *tmp, int i);

void				ft_export(t_cmd *curr);

void				ft_pwd(void);

void				ft_unset(t_cmd *curr);

void				heredoc(t_cmd *curr, int i, int fd);
void				heredoc_cmd(t_cmd *curr, int i);

void				exit_shell(void);

int					is_space(char c);
int					is_seperator(char c);
int					is_command_end(char c);
int					is_symbol(char c);
int					is_operator(char c);
int					is_letter(char c);
int					get_command_len(char *command);
int					init_argv(t_cmd *curr, char *command, int i);
void				add_new_cmd(t_cmd *curr);
t_cmd				*init_cmd(void);

int					parse_env(char **env);
char				*find_key(char *str);
char				*find_value(char *str);

int					handle_syntax_error(char *filename);
int					handle_parse_error(int quote);
int					check_redirection_error(char **argv);
int					check_pipe_error(char *command, int i);
int					check_command_error(char **argv, char *command, int i);

char				**parse_path(void);

int					check_remain_charactor_after_quote(t_cmd *curr,
		char *command);
int					handle_escape(t_cmd *curr, char *command, int quote);
int					handle_single_quote(t_cmd *curr, char *command);
int					handle_double_quote(t_cmd *curr, char *command);
int					handle_quote(t_cmd *curr, char *command, int i);
int					check_remain_character(t_cmd *curr, char *command);

int					handle_symbol(t_cmd *curr, char *command);

int					push_arg(t_cmd *curr, char *command);
int					parse_command(char *command, t_cmd *curr);

void				del_redirections(t_cmd *curr);

int					redirection_open_file(t_cmd *curr);

int					check_shell_builtin_fork(t_cmd *curr);
void				builtin_cmd_fork(t_cmd *curr);

int					check_shell_builtin(t_cmd *curr);
void				builtin_cmd(t_cmd *curr);

void				handler(int signo);

size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dest, const char *src, size_t destsize);
char				*ft_strdup(const char *s1);
char				*ft_strldup(const char *s1, int n);

int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);

void				*ft_memset(void *b, int c, size_t len);
char				*ft_itoa(int n);
char				*ft_strtrim(char *str);

char				*ft_strjoin_free_s1(char **s1, char *s2);
int					ft_strchr_index(const char *s, int c);
char				**ft_split(char const *s, char c);

#endif
