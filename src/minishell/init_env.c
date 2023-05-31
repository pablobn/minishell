#include "minishell.h"

char 	*ft_get_env_key(t_env *env, char *str)
{
	int	i;

	i = 0;
	while (&env[i])
	{
		if (env[i].key == str)
			return (env[i].value);
	}

	return (NULL);
}

int	ft_init_env(t_ms *ms, char **envp)
{
	int	i;
	int	total;

	total = -1;
	while (envp[++total])
		;
	ms->env = malloc(sizeof(t_env) * total);
	if (!ms->env)
		return (-1);
	i = -1;
	while (envp[++i])
	{
		total = -1;
		while (envp[i][++total] != '=')
			;
		ms->env[i].key = ft_substr(envp[i], 0, total);
		ms->env[i].value = ft_substr(envp[i], total + 1, ft_strlen(envp[i]));
	}
	// i = -1;
	// while (envp[++i])
	// {
	// 	printf("ms->env[%d].key:(%s)\n", i, ms->env[i].key);
	// 	printf("ms->env[%d].value:(%s)\n\n", i, ms->env[i].value);
	// }
	return (0);
}
