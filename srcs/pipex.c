#include "ft_pipex.h"
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int		numstring(char const *s1, char c)
{
	int	num;
	int	rep;

	num = 0;
	rep = 0;
	if (*s1 == '\0')
		return (0);
	while (*s1 != '\0')
	{
		if (*s1 == c)
			rep = 0;
		else if (rep == 0)
		{
			rep = 1;
			num++;
		}
		s1++;
	}
	return (num);
}

static int		sl(char const *s2, char c, int i)
{
	int	lenght;

	lenght = 0;
	while (s2[i] != c && s2[i])
	{
		lenght++;
		i++;
	}
	return (lenght);
}

static char		**affect(char const *s, char **dst, char c, int p)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] && j < p)
	{
		k = 0;
		while (s[i] == c)
			i++;
		if (!(dst[j] = (char *)malloc(sizeof(char) * (sl(s, c, i) + 1))))
			return (NULL);
		while (s[i] != '\0' && s[i] != c)
			dst[j][k++] = s[i++];
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = NULL;
	return (dst);
}

char			**ft_split(char const *s, char c)
{
	char	**dst;
	int		p;

	if (s == NULL)
		return (NULL);
	p = numstring(s, c);
	if (!(dst = (char **)malloc(sizeof(char *) * (p + 1))))
		return (NULL);
	return (affect(s, dst, c, p));
}
*//*
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	l;
	size_t	p;

	l = ft_strlen(s1);
	p = ft_strlen(s2);
	i = 0;
	j = 0;
	if (!(dest = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)))))
		return (NULL);
	while (i < l)
	{
		dest[i] = s1[i];
		i++;
	}
	while (j < p)
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
*/

char	*getmyline(char **env)
{
	int i;
	int j;
	char *goodline;

	j = 0;
	i = 0;
	goodline = "PATH=";
	while (env[i])
	{
		while (env[i][j] == goodline[j] && j < 5)
			j++;
		if (j == 5)
			return (env[i] + 5);
		else
		{
			j = 0;
			i++;
		}
	}
	return (NULL);
}
char	**getpath(char *pro, char *goodline)
{
	int	i;
	char	**paths;
	char	*tempostring;
	//int j;

	i = -1;
	paths = NULL;
	tempostring = NULL;
	paths = ft_split(goodline, ':');
	while (paths[++i])
	{
		tempostring = paths[i];
		paths[i] = ft_strjoin(tempostring, "/");
		free(tempostring);
		tempostring = NULL;
		tempostring = paths[i];
		paths[i] = ft_strjoin(tempostring, pro);
		free(tempostring);
		tempostring = NULL;
	}
	return (paths);
}

void	execpro(char *argv, char **env, int fd, int dup, int pipefd[2])
{
	int	i;
	char	**pro;
	char	**paths;
	int	j;

	if (dup == 0)
		j = 1;
	else
		j = 0;
	i = 0;
	pro = ft_split(argv, ' ');
	paths = getpath(pro[0], getmyline(env));
	close (pipefd[dup]);
	dup2(pipefd[j], j);
	dup2(fd, dup);
	close(fd);
	while (paths[i])
	{
		execve(paths[i], pro, env);
		i++;
	}
	i = 0;
	while (pro[i])
	{
		free(pro[i]);
		i++;
	}
	free(pro);
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
/*
int	main(int argc, char **argv, char **env)
{
	char	**paths;
	char	**pro;
	int	fd[2];
	int	tofork;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		printf("\nerror in the pipe");

	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[4], O_WRONLY);
	tofork = fork();
	if (tofork == 0)
		execpro(argv[2], env, fd[0], 0, pipefd);
	else
		execpro(argv[3], env, fd[1], 1, pipefd);

	return (0);
}
*/
