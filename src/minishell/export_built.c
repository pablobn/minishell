#include "minishell.h"

void	ft_print_env(t_env *env)
{
	char	*str;

	while (env)
	{
		str = env->key;
		if (env->value)
		{
			str = ft_strjoin(str, "=");
			str = ft_strjoin(str, env->value);
		}
		printf("declare -x %s\n", str);
		env = env->next;
	}
	free(str);
}

int	ft_export(t_ms *ms, char *new)
{
	char	**split;
	char	*second;

	if (!new)
		ft_print_env(ms->exp);
	else
	{
		if (!ft_strrchr(new, '='))
			return (ft_insert_last_env(&ms->exp, ft_strdup(new), NULL), 0);
		split = ft_split(new, '=');
		if (!split)
			return (perror(new), 1);
		if (split[1])
			second = ft_strdup(split[1]);
		else
			second = ft_strdup("");
		if (!second)
		{
			perror("Memory allocation failed");
			ft_free_matrix(split);
			return (1);
		}
		ft_insert_last_env(&ms->exp, ft_strdup(split[0]), second);
		ft_insert_last_env(&ms->env, ft_strdup(split[0]), second);
		ft_free_matrix(split);
	}
	return (0);
}
