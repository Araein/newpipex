#include "ft_pipex.h"

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