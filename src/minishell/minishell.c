#include "minishell.h"

//atexit(ft_leaks);

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	while (42)
	{
		ft_prompt();
		if (!g_cmd.line)
			return (0);
		if (ft_parser())
			return (-1);
		printf("Command:%s\n", g_cmd.command);
		ft_pipex();
	}
	return (0);
}
