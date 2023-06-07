#include "minishell.h"

int	ft_export(t_env *env, char *new)
{
	int		i;
	char	**split;

	if (!ft_strrchr(new, '='))
		return (1);
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

int	ft_built_in(t_command *list, t_env *env)
{
	if (ft_strncmp(list->flags[0], "cd", 2) == 0)
		return (ft_cd(list, env));
	if (ft_strncmp(list->flags[0], "export", 6) == 0)
		return (ft_export(env, list->flags[1]), 1);
	if (ft_strncmp(list->flags[0], "unset", 5) == 0)
		return (ft_unset_env(env, list->flags[1]), 1);
	return (0);
}

int	ft_check_built_in(t_command *list)
{
	if (ft_strncmp(list->flags[0], "cd", 2) == 0)
		return (1);
	if (ft_strncmp(list->flags[0], "export", 6) == 0)
		return (1);
	if (ft_strncmp(list->flags[0], "unset", 5) == 0)
		return (1);
	return (0);
}
