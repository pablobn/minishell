#include "minishell.h"

char	*ft_get_env_key(t_env *env, char *str)
{
	size_t	size;

	size = ft_strlen(env->key);
	if (ft_strlen(str) > size)
		size = ft_strlen(str);
	while (env)
	{
		if (!ft_strncmp(env->key, str, size))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
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

int	ft_env_is_repeated(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	size_t	size;

	tmp = *env;
	while (tmp)
	{
		size = ft_strlen((*env)->key);
		if (ft_strlen(key) > size)
			size = ft_strlen(key);
		if (ft_strncmp(tmp->key, key, size) == 0)
		{
			tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_insert_env(t_env **env, char *key, char *value)
{
	t_env	*new;

	if (ft_env_is_repeated(env, key, value))
		return ;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = *env;
	*env = new;
}

int	ft_init_env(t_ms *ms, char **envp)
{
	char		**split;
	int			i;

	ms->env = NULL;
	ms->exp = NULL;
	i = ft_size_matrix(envp) - 1;
	while (i >= 0)
	{
		split = ft_split(envp[i], '=');
		if (!split)
			return (1);
		ft_insert_env(&ms->env, split[0], split[1]);
		ft_insert_env(&ms->exp, split[0], split[1]);
		i--;
		ft_free_matrix(split);
	}
	return (0);
}
