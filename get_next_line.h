#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif

int	        get_next_line(int fd, char **line);
char        *check_newstr(char **newstr, char **line);
int	        ft_strlen(const char *str);
char	    *ft_strchr(const char *str, char symbol);
char	    *join_parts(char *line, char *buf);
char	    *ft_strdup(const char *str);
char        *ft_strcpy(char *dest, char *src);

#endif
