#include "minishell.h"

char	*ft_get_env_key(t_env *env, char *str)
{
	int	i;

	i = 0;
	while (env[i].key)
	{
		if (ft_strncmp(env[i].key, str, ft_strlen(str)) == 0)
			return (env[i].value);
		i++;
	}
	return (NULL);
}

static int	ft_count_env(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].key)
		i++;
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
	while (env[i].key)
	{
		envp[i] = ft_calloc(ft_strlen(env[i].key) + 1, sizeof(char *));
		envp[i] = env[i].key;
		envp[i] = ft_strjoin(envp[i], "=");
		envp[i] = ft_strjoin(envp[i], env[i].value);
		i++;
	}
	return (envp);
}

int	ft_unset_env(t_env *env, char *str)
{
	int	i;

	i = 0;
	while (env[i].key && ft_strncmp(env[i].key, str, ft_strlen(str)) != 0)
		i++;
	if (!env[i].key)
		return (ft_putstr_fd("Error eliminando variable de entorno", 2), 1);
	while (env[i + 1].key)
	{
		env[i].key = env[i + 1].key;
		env[i].value = env[i + 1].value;
		i++;
	}
	env[i].key = NULL;
	env[i].value = NULL;
	return (0);
}

int	ft_init_env(t_ms *ms, char **envp)
{
	int	i;
	int	total;

	total = 0;
	while (envp[total])
		total++;
	ms->env = ft_calloc(sizeof(t_env), total + 1);
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
	ms->env[i].key = NULL;
	return (0);
}
