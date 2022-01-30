#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
*/

void	setuphere(char **argv, int fd[2])
{
	char	content;
	int	j;
	int	i;
	int	arglen;

	arglen = ft_strlen(argv[2]);
	fd[1] = open(argv[1], O_WRONLY | O_APPEND); 
	j = 5;
	while (j != arglen)
	{
		write( 1, "here_doc > ", 12);
		i = 0;
		while (content != '\n')
		{
			read(0, &content, 1);
			j = 0;
			while (i < arglen && content == argv[2][j])
			{
				read(0, &content, 1);
				j++;
				i++;
			}
			if (j > 0 && !(i == arglen && content == '\n'))
				write(fd[1], argv[2], j);
			if (content != '\n')
				write(fd[1], &content, 1);
			i++;
		}
		if (j != arglen)
			write(fd[1], &content, 1);
		content = 't';
	}
	close(fd[1]);
	//fd[0] = open(argv[1], O_RDONLY);
}
