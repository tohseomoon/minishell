CC = gcc

CFLAGS = -Wextra -Werror -Wall

NAME = minishell

SRCS =  src/execute.c \
		src/find_cmd_path.c \
		src/free_all.c \
		src/ft_cd.c \
		src/ft_echo.c \
		src/ft_env.c \
		src/ft_exit.c \
		src/ft_export.c \
		src/ft_export_fork.c \
		src/ft_export_fork_utils.c \
		src/ft_export_utils.c \
		src/ft_pwd.c \
		src/ft_unset.c \
		src/heredoc.c \
		src/main.c \
		src/parse.c \
		src/parse_check.c \
		src/parse_env.c \
		src/parse_error.c \
		src/parse_path.c \
		src/parse_quote.c \
		src/parse_symbol.c \
		src/redirection.c \
		src/redirection_utils.c \
		src/shell_builtin_fork.c \
		src/shell_builtin_fun.c \
		src/utils.c \
		src/signal.c

OBJS = $(SRCS:.c=.o)

HEADER = src/minishell.h

READLINE = -lreadline

RM = rm -f

all : $(NAME)

$(NAME): $(OBJS) $(HEADER)
		 $(CC) $(CFLAGS) $(READLINE) -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re