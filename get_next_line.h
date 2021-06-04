#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFFER_SIZE 1024

char	*ft_strjoin_free_s1(char **s1, char *s2);
int		ft_strchr_index(const char *s, int c);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
char	*ft_strdup(const char *s1);

int		get_next_line(int fd, char **line);

#endif