#include "pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



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




////////////////////////////////////////

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

void	getpath(char **pro, char *goodline)
{
	int	i;
	char	**paths;
	char	*tempostring;

	i = -1;
	
	paths = NULL;
	tempostring = NULL;
//	printf("\nSETUP\nPro = %s\nline = %s\n\n", pro[0], goodline);
	
	paths = ft_split(goodline, ':');
	
//	printf("\ntest : %s\n", paths[8]);

	while (paths[++i])
	{
		tempostring = paths[i];
		paths[i] = ft_strjoin(tempostring, "/");
		free(tempostring);
		tempostring = NULL;
		tempostring = paths[i];
		paths[i] = ft_strjoin(tempostring, pro[0]);
		free(tempostring);
		tempostring = NULL;
		printf("\n Pour paths[%d] = %s\n",i, paths[i]);
	}
	printf("COUCOU");
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}

	return ;
//	return (paths);
}

int	main(int argc, char **argv, char **env)
{
	
	char	**pro;
	int i;

	i = 0;
	
//	pro = ft_split(argv[1], ' ');


///	while (pro[i])
//		i++;
	//printf("PRO = %s\n", ar
	
	getpath(ft_split(argv[1], ' '), getmyline(env)); 

/*	while (pro[i])
	{
		free(pro[i]);
		i++;
	}*/

//system("leaks a.out");

	return 0;
}
/*
void	pipex(t_pipex *p, **env)
{
	char	*goodline;

	goodline = getline(env);


	p->paths = getpath(p.firstpro, goodline);


//	p->path = getpath(p.secondpro, goodline);

}*/
