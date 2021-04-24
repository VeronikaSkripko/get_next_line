#include "get_next_line.h"
#include <stdio.h>

char *check_newstr(char **newstr, char **line)
{
    char *a;

    a = NULL;
    if(*newstr)
    {
        if((a = ft_strchr(*newstr, '\n')) != 0)
        {
            *a++ = '\0';
            *line = ft_strdup(*newstr);
            //если в *a после /0 что-то есть
            //то мы копируем это в newstr
            if(*a)
                ft_strcpy(*newstr, a);
            else
            {
                free(*newstr);
                *newstr = NULL;
            }
        }
        else
        {
            *line = ft_strdup(*newstr);
            free(*newstr);
            *newstr = NULL;
        }
    }
    else
    {
        //инициализация *line, просто кладем туда /0
    	*line = ft_strdup("");
    }
    return (a);
    //возвращаем а, но если оно все еще указывает на часть текста после /n, то в цикл в gnl не заходим
    // и очищаем buf, но текст остался в newstr и со следующей итерацией мы его прочтем
}

int	get_next_line(int fd, char **line)
{
    static char *newstr;
    char	*buf;
    char    *after_n;
    ssize_t		num;

    //проверка на существование адреса указателя, то есть **line
    if (!line || BUFFER_SIZE <= 0 )
        return (-1);
	//read запускать на чтение 0 символов, чтобы проверить работает ли он
    if(!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) || read(fd, buf, 0) < 0 || fd < 0 )
    	return (-1);
    after_n = check_newstr(&newstr, line);
    //заходим в цикл только если в after_n ничего не хранится
    // если хранится, то перезаписывать содержимое не можем
    while((after_n == NULL) && ((num = read(fd, buf, BUFFER_SIZE)) != 0))
    {
        buf[num] = '\0';
        if((after_n = ft_strchr(buf, '\n')) != 0)
        {
            //в buf хранится строчка до \n, а в after_n строчка после \n
        	*after_n++ = '\0';
        	//если после \n что-то есть, то переносим это в newstr
            if(*after_n && !(newstr = ft_strdup(after_n)))
                return (-1);
        }
        //переносим все содержимое buf в line (т.е либо полноценно пришедшую
        // строку, либо то, что хранилось до \n)
        if(!(*line = join_parts(*line, buf)))
            return (-1);
    }
    free(buf);
    return (after_n ? 1 : 0);
}

/*
# include <fcntl.h>
int main()
{
	char *line;
	int fd, res;
	res = 1;
	if ((fd = open("test.txt", O_RDONLY)) == -1) {
		perror("open failed on file file.dat");
		exit(1);
	}
	while (res == 1) {
		res = get_next_line(fd, &line);
		if (res) //true (1) line has been read
		{
			free(line);
			printf("%s\n", line);
		}
		else //false (0) end of file, end of while loop
			printf("%s", line);
	}
	free(line);
	while (1)
		;
}
//gcc -D BUFFER_SIZE=10 -Wall -Wextra -Werror get_next_line.c
// get_next_line_utils.c get_next_line.h
// run a.out
// cntr + z (stop running endless loop)
// leaks a.out
*/
