#include "minishell.h"

int	ft_export(t_env *env, t_command *list)
{
	int		i;
	char	**split;
	char	*new;
	int		j;

	j = 0;
	while (list->flags[j])
		j++;
	if (j > 1)
		new = list->flags[1];
	else
	{
		
		return (0);
	}
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
		return (ft_export(env, list), 1);
	if (ft_strncmp(list->flags[0], "unset", 5) == 0)
		return (ft_unset_env(env, list->flags[0]), 1);
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