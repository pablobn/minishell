#include "minishell.h"

char	*ft_get_previous_path(char *pwd)
{
	char	*path;
	int		i;

	i = ft_strlen(pwd) - 1;
	path = ft_strdup("/");
	while (pwd[i] != '/')
		i--;
	if (i != 0)
		path = ft_substr(pwd, 0, i);
	return (path);
}

char	*ft_parse_absolute_rute(char *str)
{
	char	*path;
	char	*temp;
	char	**new;

	new = ft_split(str, '/');
	path = ft_strdup("/");
	temp = ft_strdup("");
	while (*new)
	{
		if (ft_strncmp(*new, ".", ft_strlen(*new)))
		{
			if (ft_strncmp(*new, "..", ft_strlen(*new)) == 0)
				path = ft_get_previous_path(path);
			else
			{
				if (path[ft_strlen(path) - 1] != '/')
					temp = ft_strjoin("/", *new);
				else
					temp = *new;
				path = ft_strjoin(path, temp);
			}
		}
		new++;
	}
	return (ft_free_matrix(new), free(temp), path);
}

char	*ft_parse_cd(char *str, t_env *env)
{
	char	*path;
	char	*temp;
	char	*pwd;
	char	*new;

	path = ft_strdup(str);
	pwd = ft_strdup("");
	temp = ft_strdup("");
	if (str[0] != '/')
	{
		pwd = ft_get_env_key(env, "PWD");
		new = ft_strtrim(str, "/");
		if (pwd[ft_strlen(pwd) - 1] != '/')
			temp = ft_strjoin("/", new);
		path = ft_strjoin(pwd, temp);
		path = ft_parse_absolute_rute(path);
		free(new);
		free(temp);
		free(pwd);
	}
	path = ft_parse_absolute_rute(path);
	return (path);
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
	{
		if (ft_strncmp(list->flags[1], "~", ft_strlen(list->flags[1])) == 0)
			path = ft_get_env_key(env, "HOME");
		else
			path = ft_parse_cd(list->flags[1], env);
	}
	return (path);
}

int	ft_cd(t_command *list, t_ms *ms)
{
	char	*pwd;
	char	*old;
	char	*path;

	path = ft_path_cd(list, ms->env);
	if (!path)
		return (ft_putstr_fd("HOME not set\n", 2), 1);
	if (chdir(path) >= 0)
	{
		pwd = ft_strjoin("PWD=", path);
		old = ft_strjoin("OLDPWD=", ft_get_env_key(ms->env, "PWD"));
		if (ft_unset(ms, "PWD"))
			return (1);
		if (ft_unset(ms, "OLDPWD"))
			return (1);
		if (ft_export(ms, pwd))
			return (1);
		if (ft_export(ms, old))
			return (1);
	}
	else
	{
		perror(list->flags[1]);
		return (1);
	}
	return (0);
}
