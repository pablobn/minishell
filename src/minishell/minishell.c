#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void) argc;
	(void) argv;
	(void) envp;
	//atexit(ft_leaks);
	line = "";
	while (line)
	{
		printf("minishell$ ");
		line = readline(line);
		if (!line)
			return (0);
		free(line);
		line = "";
	}
	return (0);
}
