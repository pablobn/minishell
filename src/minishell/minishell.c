#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void) argc;
	(void) argv;
	(void) envp;
	line = "";
	while (line)
	{
		printf("minishell$ ");
		line = readline(line);
	}
	return (0);
}