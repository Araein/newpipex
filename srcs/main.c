#include "ft_pipex.h"


int	main(int argc, char **argv, char **env)
{
	int		tofork;
	int		fd[2];
	int		pipefd[2];

	//utiliser access, wait et perror et ./pipex here_doc end "grep -o salut" wc outfile
	//  < existepas  wc | wc  > outfile    -> 0 0 0 dans outfile (pas 0 touseul)

	argc = argc + 0;
	if (pipe(pipefd) == -1)
		printf("\nError in the pipe");
	fd[0] = open(argv[1], O_RDONLY);  // fermer partout
	if (argc != 5)
		return(printf("Error: Wrong number of arguments\n"));
	if(fd[0] == -1)
	{
		printf("Aucun fichier ou dossier de ce type: %s\n", argv[1]);
		//ajouter zsh : aucun fichier ou dossier de ce type: %s\n
		fd[1] = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		write(fd[1], "0\n", 2);
		close(fd[1]);
		close(fd[0]);
		return (0);
	} else
		fd[1] = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	fd[0] = open(argv[1], O_RDONLY);
	tofork = fork();
	if (tofork == 0)
		execpro(argv[2], env, fd[0], 0, pipefd);
	else
		execpro(argv[3], env, fd[1], 1, pipefd);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

//./pipex infile "grep -o salut" "wc -l" outfile
//< infile  grep -o salut | wc -l  > outfile