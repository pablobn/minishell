#include "minishell.h"

char	*ft_path_cd(t_command *list, t_env *env)
{
	char	*path;
	char	*before;
	char	*pwd;
	int		i;

	i = 0;
	while (list->flags[i])
		i++;
	if (i == 1)
		path = ft_get_env_key(env, "HOME");
	else
	{
		if (list->flags[1][0] != '/')
		{
			pwd = ft_get_env_key(env, "PWD");
			before = list->flags[1];
			if (pwd[ft_strlen(pwd) - 1] != '/')
				before = ft_strjoin("/", list->flags[1]);
			path = ft_strjoin(pwd, before);
		}
		else
			path = list->flags[1];
	}
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

int	ft_cd(t_command *list, t_env *env)
{
	char	*pwd;
	char	*old;
	char	*path;

	path = ft_path_cd(list, env);
	if (ft_strncmp(list->flags[1], "..", 2) == 0)
		path = ft_get_previous_path(ft_get_env_key(env, "PWD"));
	printf("%s\n", path);
	if (chdir(path) >= 0)
	{
		pwd = ft_strjoin("PWD=", path);
		old = ft_strjoin("OLDPWD=", ft_get_env_key(env, "PWD"));
		if (ft_unset_env(env, "PWD"))
			return (1);
		if (ft_unset_env(env, "OLDPWD"))
			return (1);
		if (!ft_export(env, pwd))
			return (1);
		if (!ft_export(env, old))
			return (1);
	}
	else
	{
		perror(list->flags[1]);
		return (1);
	}
	return (0);
}
