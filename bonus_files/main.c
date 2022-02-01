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
		write (1, "heredoc> ", 9);
		//tester sur mac (pipe heredoc>  ?)


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
	int		tofork;
	int		fd[2];
	int		pipefd[2];

	//utiliser access, wait et perror et ./pipex here_doc end "grep -o salut" wc outfile
	
	//HERE DOC NE REMOVE PAS LE CONTENU DE OUTFILE IL MET A LA SUITE
	//here_doc tourne dans le vide 
	//boucle infinie ./pipex indf "grep a1" "wc -w" out | cat out 
	//boucle infinie aussie quand outfile existe pas --> la creer dans ce cas la
	//< infile grep a1 | wc -w > outfile   -> boucle
	//< inrt grep a1 | wc -w > outfut   --> crée quand meme outfut

	//lorsque infile existe pas -> 0 est mit dans outfile ??
	
	// v./pipex infile "wc" "wc" outfile (bug quand infile existe pas);
	//./pipex in "wc" "wc" outfile  -> lorsque outfile existe pas -> ecrit directement dans al console au lieu de le creer
	//here_doc crée pas le dossier si existe pas -> envoit le resultat

	argc = argc + 0;
	if (pipe(pipefd) == -1)
		printf("\nError in the pipe");
	fd[0] = open(argv[1], O_RDONLY);  // fermer partout

	if (argc > 1 && ft_strcmp(argv[1], "here_doc") == 0)
	{
		if(argc != 6)
			return(printf("Error: Wrong number of arguments\n"));
		setuphere(argv, fd);
		resetargv(argv);
		fd[1] = open(argv[argc - 1], O_WRONLY | O_APPEND);
	}
	else if (argc != 5)
		return(printf("Error: Wrong number of arguments\n"));
	else if(fd[0] == -1)
	{
		printf("Aucun fichier ou dossier de ce type: %s\n", argv[1]);

		//ajouter zsh : aucun fichier ou dossier de ce type: %s\n
		fd[1] = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		write(fd[1], "0\n", 2);
		close(fd[1]);
		close(fd[0]);
		return (0);
	}
	else
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

//, 0000644
//./pipex infile "grep -o salut" wc outfile