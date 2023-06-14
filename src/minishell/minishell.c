#include "minishell.h"

t_ms	*g_ms;

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	int	i;

	atexit(ft_leaks);
	g_ms = ft_calloc(1, sizeof(t_ms));
	ft_init_env(g_ms, envp);
	while (42)
	{
		g_ms = ft_prompt(g_ms);
		i = 0;
		// while (&g_ms->list[++i])
		// {
			// printf("HOla%s\n", g_ms->list[i].line);
			// if (!&g_ms->list[i])
			// 	return (0);
			// //tendre que comprobar esto en otro sitio
			// if (!ft_strncmp(g_ms->list[i].line, "exit", 4))
			// {
			// 	//printf("$?:(%d)\n", ft_atoi(&g_ms->list->line[4]));
			// 	return (ft_atoi(&g_ms->list[i].line[4]));
			// }
			while (g_ms->list[i].next)
			{
				printf("Holasdasda\n");
				g_ms->list[i] = *ft_parser(&g_ms->list[i]);
				i++;
			}
			i = 0;
			// printf("Line:%s\n", g_ms->list->line);
			// printf("Command_f:%s\n", g_ms->list->cmd);
			// printf("Flags:%s\n", g_ms->list->flags[1]);
			// printf("Out:%d\n", g_ms->list->out);
			// printf("Out_f:%d\n", g_ms->list->out_f);
			// printf("In:%d\n", g_ms->list->in);
			// printf("In_f:%d\n", g_ms->list->in_f);
			if (g_ms->list)
			{
				ft_execute_line(g_ms);
			}
			printf("hola\n");
			//frees
			// if (&g_ms->list[i] && g_ms->list[i].out)
			// {
			// 	close(g_ms->list[i].out);
			// 	g_ms->list[i].out = 0;
			// }
			// if (&g_ms->list[i] && g_ms->list[i].in)
			// {
			// 	close(g_ms->list[i].in);
			// 	g_ms->list[i].in = 0;
			// }
			// if (&g_ms->list[i] && g_ms->list[i].cmd)
			// {
			// 	free(g_ms->list[i].cmd);
			// 	g_ms->list[i].cmd = NULL;
			// }
			//ft_free_matrix(g_ms->list[i].flags);
		// }
	}
	// g_ms->env = free_env(g_ms->env);
	// g_ms->exp = free_env(g_ms->exp);
	return (0);
}
