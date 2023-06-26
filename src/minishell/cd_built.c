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
	{
		free(path);
		path = ft_substr(pwd, 0, i);
	}
	return (free(pwd), path);
}

char	*ft_parse_absolute_rute(char *str, int i)
{
	char	*path;
	char	*temp;
	char	**new;

	new = ft_split_pipex(str, '/');
	path = ft_strdup("/");
	i = -1;
	while (new[++i])
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
					temp = ft_strdup(new[i]);
				path = ft_strjoin_free(path, temp);
				free(temp);
			}
		}
	}
	return (ft_free_matrix(new), path);
}

char	*ft_parse_cd(char *str)
{
	char	*path;
	char	*temp;
	char	*pwd;
	char	*new;

	path = ft_strdup(str);
	if (str[0] != '/')
	{
		temp = ft_strdup("");
		pwd = getcwd(NULL, 0);
		new = ft_strtrim(str, "/");
		if (pwd[ft_strlen(pwd) - 1] != '/')
		{
			free(temp);
			temp = ft_strjoin("/", new);
		}
		free(path);
		path = ft_strjoin(pwd, temp);
		free(temp);
		temp = ft_parse_absolute_rute(path, -1);
		free(path);
		path = temp;
		free(new);
		free(pwd);
	}
	temp = ft_parse_absolute_rute(path, -1);
	free(path);
	path = temp;
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
			path = ft_parse_cd(list->flags[1]);
	}
	return (path);
}

int	ft_cd(t_command *list, t_ms *ms)
{
	char	*pwd;
	char	*old;
	char	*path;
	char	*actual_path;

	path = ft_path_cd(list, ms->env);
	if (!path)
		return (ft_putstr_fd("HOME not set\n", 2), 1);
	if (chdir(path) >= 0)
	{
		actual_path = getcwd(NULL, 0);
		pwd = ft_strjoin("PWD=", path);
		old = ft_strjoin("OLDPWD=", actual_path);
		if (ft_export(ms, pwd))
			return (free(pwd), free(path), free(old), free(actual_path), 1);
		if (ft_export(ms, old))
			return (free(pwd), free(path), free(old), free(actual_path), 1);
		free(pwd);
		free(path);
		free(old);
		free(actual_path);
	}
	else
	{
		perror(list->flags[1]);
		return (free(path), 1);
	}
	return (0);
}
