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
	ft_init_env(g_ms, envp);
	while (42)
	{
		ft_prompt(g_ms->list);
		if (!g_ms->list->line)
			return (0);
		if (ft_parser(g_ms))
			return (-1);
		//printf("Line:%s\n", g_ms->list->line);
		// printf("Command_f:%s\n", g_ms->list->cmd);
		// printf("Out:%d\n", g_ms->list->out);
		// printf("Out_f:%d\n", g_ms->list->out_f);
		// printf("In:%d\n", g_ms->list->in);
		// printf("In_f:%d\n", g_ms->list->in_f);
		ft_execute_line(g_ms);
		//frees
		if (g_ms->list->out)
		{
			close(g_ms->list->out);
			g_ms->list->out = 0;
		}
		if (g_ms->list->in)
		{
			close(g_ms->list->in);
			g_ms->list->in = 0;
		}
		if (g_ms->list->cmd)
		{
			free(g_ms->list->cmd);
			g_ms->list->cmd = NULL;
		}
	}
	return (0);
}
