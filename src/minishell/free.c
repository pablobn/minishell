#include "minishell.h"

t_env	*free_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
	return (NULL);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (matrix)
	{
		while (matrix[++i])
		{
			free(matrix[i]);
			matrix[i] = NULL;
		}
		free(matrix);
	}
}

void	ft_free_ms(t_ms *g_ms)
{
	free_env(g_ms->env);
	free_env(g_ms->exp);
	if (g_ms->line)
		free(g_ms->line);
	if (g_ms->list)
		free(g_ms->list);
	free(g_ms);
}

void	ft_free_list(t_command	**list)
{
	int	i;

	i = 0;
	if (list)
	{
		while (list[i])
		{
			ft_free_matrix(list[i]->flags);
			free(list[i]->cmd);
			free(list[i]->line);
			i++;
		}
		free(list[i]);
	}
}
