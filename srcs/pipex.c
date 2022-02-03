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
char	*getpath(char *pro, char *goodline)
{
	char	**paths;
	char	*tmp;
	char	*result;
	char	**tempo;

	paths = ft_split(goodline, ':');
	tempo = paths;
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		result = ft_strjoin(tmp, pro);
		free(tmp);
		if (access(result, F_OK) == 0)
			return (result);
		free(result);
		paths++;
	}		
	int i = 0;
	while (tempo[i])
		{
			free(tempo[i]);
			i++;
		}
	free(tempo);
	return (NULL);
}

void	execpro(char *argv, char **env, int fd, int dup, int pipefd[2])
{
	int	i;
	char	**pro;
	char	*paths;
	int	j;

	if (dup == 0)
		j = 1;
	else
		j = 0;
	i = 0;
	pro = ft_split(argv, ' ');
	paths = getpath(pro[0], getmyline(env));

	if (!paths)
	{
		printf("command not found: %s\n", pro[0]);  //ajjouter zsh:   ?
		while (pro[i])
		{
			free(pro[i]);
			i++;
		}
		free(pro);
		free(paths);
		return ;
	}
	close (pipefd[dup]);
	dup2(pipefd[j], j);
	dup2(fd, dup);
	close(fd);
	execve(paths, pro, env); // env = ENV  // pro = commandeafaire // 

	i = 0;
	while (pro[i])
	{
		free(pro[i]);
		i++;
	}
	free(pro);
	i = 0;

	free(paths);
}