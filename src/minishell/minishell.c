#include "minishell.h"

//atexit(ft_leaks);
extern t_ms *g_ms;

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	g_ms = ft_calloc(1, sizeof(t_command));
	while (42)
	{
		ft_prompt();
		if (!g_ms->list->command)
			return (0);
		ft_pipex();
	}
	return (0);
}
