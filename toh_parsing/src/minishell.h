/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toh <toh@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:28:55 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/30 13:49:59 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <term.h>
# include <curses.h>

# define S_QUOTE '\''
# define D_QUOTE '\"'
# define B_QUOTE '`'
# define ESCAPE  '\\'
# define COL	0
# define ROW	1
# define BUFFER_SIZE 1024
# define ARROW_UP 4283163
# define ARROW_DOWN 4348699
# define BACKSPACE 127
# define CTRL_D	4

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				equal;
	struct s_env	*next;
}					t_env;

typedef struct		s_token
{
	char			*str;
	int				flag;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct		s_token_util
{
	char			*str;
	char			*cmd;
	char			*tmp;
	int				cnt;
}					t_token_util;

typedef struct		s_cmd
{
	char			**argv;
	int				argc;
	int				index;
	int				pipe[2];
	int				heredoc_pipe[2];
	int				heredoc;
	int				type;
	int				fd_in;
	int				fd_out;
	int				continuous;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct			s_term
{
	struct termios		new_term;
	struct termios		save_term;
	char				*cm;
	char				*ce;
}						t_term;

typedef struct		s_pos
{
	int				col;
	int				row;
}					t_pos;

typedef struct		s_hist
{
	char			*command;
	int				flag;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_data
{
	char			*command;
	struct s_cmd	*cmd_head;
	struct s_env	*env_head;
	struct s_token	*token_head;
	char			**path;
	char			**env;
	char			*home;
	int				return_value;
	int				running;
	t_pos			curr;
	t_pos			start;
	t_pos			max;
	t_hist			*h_head;
	int				h_flag;
	t_term			term;
}					t_data;

t_data				g_data;

void				check_pipe(t_cmd *curr);
void				execute_command(char **envp);

int					find_cmd_path(t_cmd *curr);
int					find_cmd_absolute_path(t_cmd *curr);

void				free_token(void);
void				free_cmd_list(void);
void				free_all(void);
void				free_path(void);

void				ft_cd(t_cmd *curr);

void				ft_echo(t_cmd *curr);

void				ft_env(t_cmd *cmd);

int					exit_print_return_msg(t_cmd *curr, int *exit_flag);

void				ft_exit(t_cmd *curr, int flag);

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

int					check_redirection_token_error(t_token *token);
int					check_token_error(t_token *token);

int					parce_cmd(void);

char				*change_env_str(char *str);
void				quote_env_str(t_token_util *utils);
void				env_str(t_token_util *utils);

void				make_tmp_str(t_token_util *utils);
void				join_tmp_str(t_token_util *utils, char *str);
void				check_join_cmd(t_token_util *utils);
void				nomal_str(t_token_util *utils);

int					quote_str(t_token_util *utils, char quote);

void				symbol_str(t_token_util *utils, char symbol);

t_token				*new_token(char *str, int flag);
int					is_pass_char(char c);
int					is_symbols(char c);
int					is_quotes(char c);

int					parce_token(void);

int					parse_env(char **env);
char				*find_key(char *str);
char				*find_value(char *str);

char				**parse_path(void);

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
int					ft_putchar(int c);

char				*ft_strjoin_free_s1(char **s1, char *s2);
int					ft_strchr_index(const char *s, int c);
char				**ft_split(char const *s, char c);

void				init_term(t_term *term);
int					main_term(t_data *g);

int					get_next_line(int fd, char **line);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
void				init_cursor(t_data *g);
void				set_cursor(int *col, int *row);
t_hist				*push_front_history(char *command, t_hist *old_head, int flag);
void				handle_keycode(t_data *g, int keycode);
void				press_up(t_data *g);
void				press_down(t_data *g);
void				save_history(t_data *g);
void				reset_history(t_data *g);


//임시임시
void	print_cmd(void);
void	print_token(void);

#endif
