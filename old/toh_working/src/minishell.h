/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:28:55 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/20 15:59:16 by toh              ###   ########.fr       */
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
# include <stdio.h> //check

# define STDIN	0
# define STDOUT	1
# define END 0
# define PIPE 1

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

//execute.c
void				check_pipe(t_cmd *curr);
void				execute_command(char **envp);

//find_cmd_path.c
int					find_cmd_path(t_cmd *curr);
int					find_cmd_absolute_path(t_cmd *curr);

//free_all.c
void				free_cmd_list(void);
void				free_env(void);
void				free_path(void);

//ft_cd.c
void				ft_cd(t_cmd *curr);

//ft_echo.c
void				ft_echo(t_cmd *curr);

//ft_env.c
void				ft_env(void);

//ft_exit.c
void				ft_exit(t_cmd *curr);

//ft_export_fork_utils.c
char				**arr_env_string(void);
void				print_sort_env(void);

//ft_export_fork.c
void				ft_export_fork(void);

//ft_export_utils.c
int					key_isallowed(char *str);
int					add_path(t_env *curr, char *str);
void				creat_add_env(t_cmd *curr, t_env *tmp, int i);

//ft_export.c
void				ft_export(t_cmd *curr);

//ft_pwd.c
void				ft_pwd(void);

//ft_unset.c
void				ft_unset(t_cmd *curr);

//heredoc.c
void				heredoc(t_cmd *curr, int i, int fd);
void				heredoc_cmd(t_cmd *curr, int i);

//perse_check.c
int					is_space(char c);
int					is_seperator(char c);
int					is_command_end(char c);
int					is_symbol(char c);

//perse_env.c
int					parse_env(char **env);
char				*find_key(char *str);
char				*find_value(char *str);

//parse_error.c
int					handle_syntax_error(char *message);
int					handle_parse_error(int quote);
int					check_redirection_error(char **argv);
int					check_pipe_error(char *command, int i);
int					check_command_error(char **argv, char *command, int i);






void				exit_shell(void);
int					parse_command(char *command);
int					handle_single_quote(t_cmd *curr, char *command);
int					handle_double_quote(t_cmd *curr, char *command);
int					handle_symbol(t_cmd *curr, char *command);

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
char				*ft_itoa(int n);
int					parse_env(char **envp);
char				**parse_path(void);

int		            redirection_open_file(t_cmd *curr);

void				free_data();

void				print_cmd();
void				builtin_cmd_fork(t_cmd *curr);
void				builtin_cmd(t_cmd *curr);
int					check_shell_builtin_fork(t_cmd *curr);
int					check_shell_builtin(t_cmd *curr);

char				**arr_new_env_string(void);
char				*ft_strchr(const char *s, int c);

int					ft_isalpha(int c);
int					ft_isalnum(int c);

int					check_command_error(char **argv, char *command, int i);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				del_redirections(t_cmd *curr);
void				handler(int signo);


#endif
