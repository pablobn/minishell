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
		if (!g_cmd.command)
			return (0);
		ft_pipex();
	}
	return (0);
}
