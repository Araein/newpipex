#include <unistd.h>
#include <stdio.h>

int
main(int argc, char *argv[], char *env[])
{
  if (argc > 1)
    if (execve(argv[1], argv + 1, env) == -1)
	    perror("execve");
	return 0;
}
