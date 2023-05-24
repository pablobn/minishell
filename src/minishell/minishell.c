#include "minishell.h"

//atexit(ft_leaks);
extern t_ms	*g_ms;

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	g_ms = ft_calloc(1, sizeof(t_command));
	while (42)
	{
		ft_prompt(g_ms->list);
		if (!g_ms->list->command)
			return (0);
		if (ft_parser(g_ms->list))
			return (-1);
		printf("Command:%s\n", g_ms->list->command);
		printf("Out:%d\n", g_ms->list->out);
		printf("Out_f:%d\n", g_ms->list->out_f);
		ft_pipex();
	}
	return (0);
}
