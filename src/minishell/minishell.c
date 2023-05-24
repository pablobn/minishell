#include "minishell.h"

//atexit(ft_leaks);
t_ms	*g_ms;

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	g_ms = ft_calloc(1, sizeof(t_ms));
	g_ms->list = ft_calloc(1, sizeof(t_command));
	g_ms->list->in_f = 42;
	while (42)
	{
		ft_prompt(g_ms->list);
		if (!g_ms->list->line)
			return (0);
		if (ft_parser(g_ms->list))
			return (-1);
		printf("Line:%s\n", g_ms->list->line);
		printf("Out:%d\n", g_ms->list->out);
		printf("Out_f:%d\n", g_ms->list->out_f);
		close(g_ms->list->out);
		//ft_pipex(g_ms);
	}
	return (0);
}
