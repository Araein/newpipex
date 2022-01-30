#include "ft_pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	resetargv(char **argv)
{
	int		i;

	i = 2;
	while (i < 5)
	{
		argv[i] = argv[i + 1];
		i++;
	}
}

void	setuphere(char **argv, int fd[2])
{
	char	content;
	int		j;
	int		i;
	int		arglen;

	arglen = ft_strlen(argv[2]);
	fd[1] = open(argv[1], O_WRONLY | O_TRUNC);
	j = 5;
	while (j != arglen)
	{
		write (1, "pipe heredoc> ", 14);
		i = 0;
		while (content != '\n')
		{
			read (0, &content, 1);
			j = 0;
			while (i < arglen && content == argv[2][j])
			{
				read (0, &content, 1);
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
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	int		tofork;
	int		pipefd[2];

	//VERIFIER SI IL FAUT CREER FICHIER SI IL EXISTE PAS
	//utiliser access, wait et perror et 
	//verifier ce au'il faut print a chaque fois heredoc?here_doc?
	//segfault si ./pipex here_doc -> verifier le bon nombre d'arguments 
	argc = argc + 0;
	if (pipe(pipefd) == -1)
		printf("\nerror in the pipe");
	fd[0] = open(argv[1], O_RDONLY);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		setuphere(argv, fd);
		resetargv(argv);
		fd[1] = open(argv[4], O_WRONLY | O_APPEND);
	}
	else
		fd[1] = open(argv[4], O_WRONLY | O_TRUNC);
	fd[0] = open(argv[1], O_RDONLY);
	tofork = fork();
	if (tofork == 0)
		execpro(argv[2], env, fd[0], 0, pipefd);
	else
		execpro(argv[3], env, fd[1], 1, pipefd);
	return (0);
}
