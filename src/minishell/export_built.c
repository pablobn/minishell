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

	if (!new)
		ft_print_env(ms->exp);
	else
	{
		if (!ft_strrchr(new, '='))
			return (ft_insert_env(&ms->exp, ft_strdup(new), NULL), 0);
		split = ft_split(new, '=');
		if (!split)
			return (perror(new), 1);
		ft_insert_env(&ms->exp, split[0], split[1]);
		ft_insert_env(&ms->env, split[0], split[1]);
		ft_free_matrix(split);
	}
	return (0);
}
