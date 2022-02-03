#include "ft_pipex.h"


int	main(int argc, char **argv, char **env)
{
	int		tofork;
	int		fd[2];
	int		pipefd[2];

	//utiliser access, wait et perror et ./pipex here_doc end "grep -o salut" wc outfile
	//  < existepas  wc | wc  > outfile    -> 0 0 0 dans outfile (pas 0 touseul)


	//mettre des ft_putstr 
//	argc = argc + 0;

//bien tout close
//mettre une struct
//metre fonction de freetab
//piger l'use de dup2 etc...
//update .h
//secure malloc et le reste

	if (argc != 5)
		return(printf("Error: Wrong number of arguments\n"));

	fd[0] = open(argv[1], O_RDONLY);  // fermer partout ->pipe de infile
	if (pipe(pipefd) == -1)
		printf("\nError in the pipe");
	if(fd[0] < 0)
	{
		printf("Aucun fichier ou dossier de ce type: %s\n", argv[1]);
		fd[1] = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		write(fd[1], "0\n", 2);
		close(fd[1]);
	//	close(fd[0]);
		return (0);
	}
	fd[1] = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644); // -> pipe outfile
	if(fd[1] < 0)
	{
		printf("Error when opening this file : %s\n", argv[argc - 1]);
		close(fd[0]);
		return (0);
	}




	tofork = fork();
	if(tofork < 0)
	{
		printf("Error int the Pipe process\n");
		close(fd[0]);
		close(fd[1]);
		return (0);
	}


	if (tofork == 0)
	{
		execpro(argv[2], env, fd[0], 0, pipefd);
	}
	else
	{
		waitpid(tofork, NULL, 0);
		execpro(argv[3], env, fd[1], 1, pipefd);
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}
//utiliser perrorr
// ./pipex infile "grep -o salut" "wc -l" outfile
// < infile  grep -o salut | wc -l  > outfile