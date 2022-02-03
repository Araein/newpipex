#ifndef FT_PIPEX_H
# define FT_PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

typedef struct	s_pipex
{
	char	*firstfile;
	char	*secondfile;
	char	**firstpro;
	char	**secondpro;
	char	*path;
}				t_pipex;

char	*getmyline(char **env);
char	*getpath(char *pro, char *goodline);
void	execpro(char *argv, char **env, int fd, int dup, int pipefd[2]);
int		main(int argc, char **argv, char **env);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_putstr_fd(char const *s, int fd);
void	ft_putchar_fd(char c, int fd);


#endif
