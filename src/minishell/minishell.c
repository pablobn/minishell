#include "minishell.h"

t_ms	*g_ms;

int	main(int argc, char **argv, char **envp)
{
	int	i;

	(void) argc;
	(void) argv;
	// atexit(ft_leaks);
	g_ms = ft_calloc(1, sizeof(t_ms));
	ft_init_env(g_ms, envp);
	while (42)
	{
		ft_prompt(g_ms);
		if (!g_ms->line)
			break ;
		i = -1;
		while (g_ms->list && g_ms->list[++i])
			ft_parser(g_ms->list[i]);
		i = -1;
		while (g_ms->list && g_ms->list[++i]->flags)
			if (!ft_strncmp(g_ms->list[i]->flags[0], "exit", 4))
				return (ft_atoi(g_ms->list[i]->flags[1]));
		if (g_ms->list[0])
			ft_execute_line(g_ms);
		ft_free_list(g_ms->list);
	}
	ft_free_ms(g_ms);
	clear_history();
	return (0);
}
