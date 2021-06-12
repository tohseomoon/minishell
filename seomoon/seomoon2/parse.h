/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seomoon <seomoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 20:28:55 by seomoon           #+#    #+#             */
/*   Updated: 2021/06/12 21:36:25 by seomoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <unistd.h>
# include <stdlib.h>

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


int			ft_strlen(char *str);
int		ft_strlcpy(char *dest, char *src, int destsize);
char		*ft_strdup(char *s1);
char	*ft_strldup(char *s1, int n);
int					get_next_line(int fd, char **line);

#endif
