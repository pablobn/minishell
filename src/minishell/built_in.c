#include "minishell.h"

int	ft_export(t_env *env, char *new)
{
	int		i;
	char	**split;

	if (!ft_strrchr(new, '='))
	{
		return (1);
	}
	split = ft_split(new, '=');
	if (!split)
		return (perror(new), 0);
	i = 0;
	while (env[i].key)
		i++;
	env[i].key = split[0];
	env[i].value = split[1];
	i++;
	env[i].key = NULL;
	return (1);
}

char	*ft_path_cd(t_command *list, t_env *env)
{
	char	*path;
	int		i;

	i = 0;
	while (list->flags[i])
		i++;
	if (i == 1)
		path = ft_get_env_key(env, "HOME");
	else
		path = list->flags[1];
	return (path);
}

char	*ft_get_previous_path(char *pwd)
{
	char	*path;
	int		i;

	if (ft_strncmp(path, "/", 1) == 0)
		return ("/");
	i = ft_strlen(pwd) - 1;
	while (pwd[i] != '/')
		i--;
	if (i == 0)
		path = ft_strdup("/");
	else
		path = ft_substr(pwd, 0, i);
	return (path);
}

void	ft_cd(t_command *list, t_env *env)
{
	char	*pwd;
	char	*old;
	char	*path;

	path = ft_path_cd(list, env);
	if (ft_strncmp(path, "..", 2) == 0)
		path = ft_get_previous_path(ft_get_env_key(env, "PWD"));
	if (chdir(path) >= 0)
	{
		pwd = ft_strjoin("PWD=", path);
		old = ft_strjoin("OLDPWD=", ft_get_env_key(env, "PWD"));
		if (ft_unset_env(env, "PWD"))
			exit(1);
		if (ft_unset_env(env, "OLDPWD"))
			exit(1);
		if (!ft_export(env, pwd))
			exit(1);
		if (!ft_export(env, old))
			exit(1);
	}
	else
	{
		perror(list->flags[1]);
		exit(1);
	}
}
