#include "minishell.h"

char	*ft_get_env_key(t_env *env, char *str)
{
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(env->key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}


static int	ft_count_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}	
	return (i);
}

char	**ft_get_envp(t_env *env)
{
	char	**envp;
	int		i;

	envp = ft_calloc(ft_count_env(env) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = ft_strdup(env->key);
		envp[i] = ft_strjoin(envp[i], "=");
		envp[i] = ft_strjoin(envp[i], env->value);
		env = env->next;
		i++;
	}
	return (envp);
}

void	ft_insert_env(t_env **env, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = *env;
	*env = new;
}

int	ft_init_env(t_ms *ms, char **envp)
{
	char		**split;

	ms->env = NULL;
	ms->exp = NULL;
	while (*envp)
	{
		split = ft_split(*envp, '=');
		if (!split)
			return (1);
		ft_insert_env(&ms->env, ft_strdup(split[0]), ft_strdup(split[1]));
		ft_insert_env(&ms->exp, ft_strdup(split[0]), ft_strdup(split[1]));
		envp++;
		ft_free_matrix(split);
	}
	return (0);
}
