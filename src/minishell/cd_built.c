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
	int		i;
	char	*temp;
	char	**new;

	new = ft_split(str, '/');
	path = ft_strdup("/");
	temp = ft_strdup("");
	i = 0;
	while (new[i])
	{
		if (ft_strncmp(new[i], ".", ft_strlen(new[i])))
		{
			if (ft_strncmp(new[i], "..", ft_strlen(new[i])) == 0)
				path = ft_get_previous_path(path);
			else
			{
				if (path[ft_strlen(path) - 1] != '/')
					temp = ft_strjoin("/", new[i]);
				else
					temp = new[i];
				path = ft_strjoin_free(path, temp);
			}
		}
		i++;
	}
	return (ft_free_matrix(new), path);
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
		if (ft_export(ms, pwd))
			return (1);
		if (ft_export(ms, old))
			return (1);
		free(pwd);
		free(path);
		free(old);
	}
	else
	{
		perror(list->flags[1]);
		return (1);
	}
	return (0);
}
