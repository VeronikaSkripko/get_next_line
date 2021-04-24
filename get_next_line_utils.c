#include "get_next_line.h"

char	*ft_strdup(const char *str)
{
    int i;
    char *copy;

    i = 0;
    if (!(copy = malloc(ft_strlen(str) + 1)))
        return(NULL);
    while (str[i] != '\0')
    {
        copy[i] = str[i];
        i++;
    }
    copy[i] = '\0';
    return (copy);
}
char *ft_strcpy(char *dest, char *src)
{
    int i;

    i = 0;
    while(src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int	ft_strlen(const char *str)
{
    int	i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}
char	*ft_strchr(const char *str, char ch)
{
    char	*s;
    int     i;

    s = (char *)str;
    i = 0;
    while(s[i] != '\0')
    {
        if(s[i] == ch)
            //указатель на строчку, включая ch в ней
            return ((char *)s + i);
        i++;
    }
    if(s[i] == ch)
        return ((char *)s + i);
    return (0);
}

char	*join_parts(char *line, char *buf)
{
    int		i;
    int		g;
    char	*newline;

    i = 0;
    g = 0;
    if(line == NULL || buf == NULL)
        return (NULL);
    if (!(newline = ((char *)malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buf)) + 1))))
        return (NULL);
    while (line[i] != '\0')
        newline[g++] = line[i++];
    free(line);
    i = 0;
    while ((buf[i] != '\0'))
        newline[g++] = buf[i++];
    newline[g] = '\0';
    return (newline);
}

