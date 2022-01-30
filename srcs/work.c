#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int	main(void)
{
	int fd[2];
	int pid1;
	int pid2;

	char* argv[] = { "ping", "-c", "5","google.com"};
	char* envp[] = { "some", "environment", NULL };
	
	char* argv2[] = {"grep",  "rtt"};
	char* envp2[] = { "some", "environment", NULL };
	
	printf("wsh");
	
	if(pipe(fd) == 1)
		return (1);
	pid1 = fork();
	if(pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
	/*process for the first program*/
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("sh", argv, envp);
	}

	waitpid(pid1, NULL, 0);

	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("sh", argv2, envp2);
	}

	close(fd[1]);
	close(fd[0]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}


/*
 *	execv execute le programme dont le path est mit en premier argument
 *	avec les arguments envoyés par argv? dans le second argument (tableau de strings)
 *	le troisieme argument est l'environnement et jsp ce que c'est.
 *
 *	du coup il faut recup le 1er programme et ses flags (ici cat argv [1] sans les '"') 
 *	puis le run avec les arguments (mafile = argv[0])
 *	puis recup le resultat avec un process different du premier (fork)
 *
 *	puis refaire la meme chose mais avec comme argument l'output du premier.
 *	le 2eme programme et ses flags (argv[2] sans les '"')
 *	et output dans la file de retour -> argv[3].
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * */












































