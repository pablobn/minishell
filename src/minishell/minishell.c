#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	**cmd;
	char		*line;

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
		ft_parser(&cmd);
		free(line);
		line = "";
	}
	return (0);
}
