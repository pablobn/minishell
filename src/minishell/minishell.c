#include "minishell.h"

t_ms	*g_ms;

int	main(int argc, char **argv, char **envp)
{
	int	i;

	(void) argc;
	(void) argv;
	int	i;

	atexit(ft_leaks);
	g_ms = ft_calloc(1, sizeof(t_ms));
	g_ms->env2 = ft_init_env2(g_ms->env2, envp);
	while (42)
	{
		g_ms->list = ft_prompt(g_ms);
		if (!g_ms->line)
			break ;
		// if (!ft_strncmp(g_ms->list->line, "exit", 4))
		// {
		// 	//printf("$?:(%d)\n", ft_atoi(&g_ms->list->line[4]));
		// 	return (ft_atoi(&g_ms->list->line[4]));
		// }
		i = 0;
		while (g_ms->list[i])
		{
			g_ms->list[i] = ft_parser(g_ms->list[i]);
			i++;
		}
		if (g_ms->list[0])
		{
			printf("Line:%s\n", g_ms->list[0]->line);
			printf("Command_f:%s\n", g_ms->list[0]->cmd);
			printf("Flags:%s\n", g_ms->list[0]->flags[0]);
			printf("Out:%d\n", g_ms->list[0]->out);
			printf("Out_f:%d\n", g_ms->list[0]->out_f);
			printf("In:%d\n", g_ms->list[0]->in);
			printf("In_f:%d\n", g_ms->list[0]->in_f);
		}
		// if (g_ms->list[0]->cmd)
		// 	ft_execute_line(g_ms);
		// //frees
		// if (g_ms->list->out)
		// {
		// 	close(g_ms->list->out);
		// 	g_ms->list->out = 0;
		// }
		// if (g_ms->list->in)
		// {
		// 	close(g_ms->list->in);
		// 	g_ms->list->in = 0;
		// }
		// if (g_ms->list->cmd)
		// {
		// 	free(g_ms->list->cmd);
		// 	g_ms->list->cmd = NULL;
		// }
		// ft_free_matrix(g_ms->list->flags);
	}
	int k;
	k = 0;
	while (g_ms->env2[k])
	{
		free(g_ms->env2[k]->key);
		free(g_ms->env2[k]->value);
		free(g_ms->env2[k]);
		k++;
	}
	free(g_ms->env2);
	
	k = 0;
	if (g_ms->line)
		free(g_ms->line);
	if (g_ms->list)
		while (g_ms->list[k])
		{
			ft_free_matrix(g_ms->list[k]->flags);
			free(g_ms->list[i]->cmd);
			free(g_ms->list[i]->line);
			k++;
		}
	free(g_ms->list);
	free(g_ms);	
	return (0);
}
