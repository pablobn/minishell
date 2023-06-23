#include "minishell.h"

t_ms	*g_ms;

int	main(int argc, char **argv, char **envp)
{
	g_ms = ft_calloc(1, sizeof(t_ms));
	ft_init_env(g_ms, envp);
	while (42)
	{
		ft_prompt(g_ms);
		if (!g_ms->line)
			break ;
		argc = -1;
		while (g_ms->list && g_ms->list[++argc])
			ft_parser(g_ms->list[argc]);
		argc = -1;
		while (g_ms->list[++argc] && g_ms->list[argc]->flags)
		{
			if (!ft_strncmp(g_ms->list[argc]->flags[0], "exit", 4))
			{
				if (g_ms->list[argc]->flags[1])
					return (ft_atoi(g_ms->list[argc]->flags[1]));
				else if (g_ms->list[argc]->flags[2])
					break ;
				return (255);
			}
		}
		if (g_ms->list[0])
			ft_execute_line(g_ms);
		ft_free_list(g_ms->list);
		g_ms->pid = 0;
	}
	return (ft_free_ms(g_ms), rl_clear_history(), (void)argv, 0);
}
