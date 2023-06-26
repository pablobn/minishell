#include "minishell.h"

t_ms	*g_ms;

static void	ft_exit(t_ms *ms)
{
	int	i;

	i = -1;
	while (ms->list[++i] && ms->list[i]->flags)
	{
		if (!ft_strncmp(ms->list[i]->flags[0], "exit", 4))
		{
			if (g_ms->list[i]->flags[1])
			{	
				ms->status = ft_atoi(ms->list[i]->flags[1]);
				ft_free_list(ms->list);
				rl_clear_history();
				free_env(g_ms->env);
				free_env(g_ms->exp);
				if (g_ms->line)
					free(g_ms->line);
				exit(ms->status);
			}
			ft_free_list(ms->list);
			ft_free_ms(ms);
			rl_clear_history();
			exit(255);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	//atexit(ft_leaks);
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
		ft_exit(g_ms);
		if (g_ms->list[0])
			ft_execute_line(g_ms);
		ft_free_list(g_ms->list);
		g_ms->pid = 0;
	}
	return (ft_free_ms(g_ms), rl_clear_history(), (void)argv, 0);
}
